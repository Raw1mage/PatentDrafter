# HTML 匯出快速開始

## ⚡ 3 步驟快速匯出

### 方法 1：單一文件匯出（推薦初次使用）

```
1. 開啟 Markdown 文件（如 docs/A0_system_idef0.md）
2. 按 Ctrl+Shift+V
3. 預覽視窗右鍵 → HTML → HTML (offline)
4. HTML 會生成在同一目錄，移動到 docs/html/
```

### 方法 2：批量匯出

**Windows (PowerShell)**：
```powershell
.\export_to_html.ps1
```

**Linux / macOS / Git Bash**：
```bash
bash export_to_html.sh
```

---

## 📚 完整文件

詳細說明請參考：
- [Markdown匯出HTML指南](docs/troubleshooting/Markdown匯出HTML指南.md) - 完整操作指南（15,234 字）
- [docs/html/README.md](docs/html/README.md) - HTML 目錄說明

---

## 🧪 測試匯出功能

1. 開啟測試文件：
   ```
   code docs/html/TEST_EXPORT.md
   ```

2. 按 `Ctrl+Shift+V` 開啟預覽

3. 確認所有元素（Mermaid 圖表、表格、程式碼）正確顯示

4. 右鍵 → HTML → HTML (offline)

5. 在瀏覽器中開啟生成的 HTML 文件確認

---

## ✅ 成功標準

匯出的 HTML 文件應該：
- ✅ 可以在瀏覽器中離線開啟
- ✅ 所有 Mermaid 圖表完整顯示
- ✅ 文字格式和樣式正確
- ✅ 檔案大小約 100-500 KB

---

## 🎯 匯出哪些文件？

建議匯出的文件：
```
docs/README.md                  → docs/html/README.html
docs/A0_system_idef0.md        → docs/html/A0_system_idef0.html
docs/A1_UI_Management_IDEF0.md → docs/html/A1_UI_Management_IDEF0.html
... (所有 A1-A8 文件)
```

---

**快速參考**：本文件提供最簡化的使用說明
**詳細文件**：[docs/troubleshooting/Markdown匯出HTML指南.md](docs/troubleshooting/Markdown匯出HTML指南.md)
