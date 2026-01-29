"""
    To create a virtual environment with python 
    python3 -m venv myenv 
    To activate it:
    source myenv/bin/activate
    You might have to install the library pdfminer.six
    pip install pdfminer.six
"""
from pathlib import Path
import json
import re
from pdfminer.high_level import extract_text


# Directory where the script is located
BASE_DIR = Path(__file__).parent #It looks for the current directory
json_path = BASE_DIR / "pathgotten.json"

print("Script dir:", BASE_DIR)
print("JSON path:", json_path.resolve())

with json_path.open("r", encoding="utf-8") as f:
    data = json.load(f)

print("PDF path from JSON:", data["pathgotten"])



# Folder given from the main UI by a json file
PDF_DIR = data["pathgotten"]

print(f"Usando PDF: {PDF_DIR}")

text = extract_text(PDF_DIR)

# --- Logic of extraction ---
lines = [ln.strip() for ln in text.splitlines() if ln.strip()]

label_block_idx = None
for i, ln in enumerate(lines):
    if ln.lower().startswith("subtotal"):
        window = "\n".join(lines[i:i+6]).lower()
        if "impuestos trasladados" in window and "impuestos retenidos" in window:
            label_block_idx = i
            break

if label_block_idx is None:
    raise RuntimeError("No se encontró el bloque con 'Subtotal / Impuestos trasladados / Impuestos retenidos'.")

money_pattern = re.compile(r'\$?\s*([0-9]{1,3}(?:,[0-9]{3})*(?:\.[0-9]{2})|[0-9]+(?:\.[0-9]{2}))')
candidate_amounts = []
for ln in lines[label_block_idx: label_block_idx + 40]:
    for m in money_pattern.finditer(ln):
        raw = m.group(1).replace(",", "")
        try:
            candidate_amounts.append(float(raw))
        except ValueError:
            pass

if len(candidate_amounts) < 3:
    raise RuntimeError(f"Se encontraron muy pocos importes: {candidate_amounts}")

impuestos_trasladados = candidate_amounts[1]
impuestos_retenidos = candidate_amounts[2]

data = {
    "Impuestos_trasladados": impuestos_trasladados,
    "Impuestos_retenidos": impuestos_retenidos
}

out_path = BASE_DIR / "data.json"
with out_path.open("w", encoding="utf-8") as json_file:
    json.dump(data, json_file, ensure_ascii=False, indent=2)

print("Archivo JSON escrito en:", out_path)
