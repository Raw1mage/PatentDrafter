# HTML 匯出文件目錄

此目錄存放從 Markdown 文件匯出的 HTML 版本。

---

## 📁 目錄說明

### 用途

- ✅ 存放所有從 Markdown 匯出的 HTML 文件
- ✅ 便於在沒有 Markdown 編輯器的環境中查看文件
- ✅ 可以直接在瀏覽器中開啟，離線查看
- ✅ 保留完整的 Mermaid 圖表渲染

### 檔案來源

所有 HTML 文件都是從 `docs/` 目錄中的 Markdown 文件匯出：

```
docs/A0_system_idef0.md  →  docs/html/A0_system_idef0.html
docs/A1_*.md             →  docs/html/A1_*.html
...
```

---

## 🚀 快速匯出

### 單一文件匯出

1. 在 VS Code 中開啟 Markdown 文件
2. 按 `Ctrl+Shift+V` 開啟預覽
3. 在預覽視窗右鍵 → **HTML** → **HTML (offline)**
4. 將生成的 HTML 文件移動到此目錄

### 批量匯出

使用專案根目錄的匯出腳本：

**Windows (PowerShell)**：
```powershell
.\export_to_html.ps1
```

**Linux / macOS / Git Bash**：
```bash
bash export_to_html.sh
```

---

## 📄 匯出的文件

### IDEF0 架構文件

| HTML 文件 | 來源 Markdown | 說明 |
|-----------|--------------|------|
| README.html | README.md | 功能設計導覽 |
| A0_system_idef0.html | A0_system_idef0.md | 系統頂層架構 |
| A1_UI_Management_IDEF0.html | A1_UI_Management_IDEF0.md | 使用者介面管理 |
| A2_Document_Parsing_IDEF0.html | A2_Document_Parsing_IDEF0.md | 文件解析模組 |
| A3_Patent_Search_IDEF0.html | A3_Patent_Search_IDEF0.md | 專利檢索模組 |
| A4_Outline_Generation_IDEF0.html | A4_Outline_Generation_IDEF0.md | 大綱生成模組 |
| A5_Content_Writing_IDEF0.html | A5_Content_Writing_IDEF0.md | 內容撰寫模組 |
| A6_Diagram_Generation_IDEF0.html | A6_Diagram_Generation_IDEF0.md | 圖表生成模組 |
| A7_Document_Merging_IDEF0.html | A7_Document_Merging_IDEF0.md | 文件合併模組 |
| A8_Workflow_Control_IDEF0.html | A8_Workflow_Control_IDEF0.md | 工作流程控制 |

### 測試文件

| HTML 文件 | 說明 |
|-----------|------|
| TEST_EXPORT.html | HTML 匯出功能測試 |

---

## ✅ HTML 文件特性

### 優勢

- ✅ **離線可用**：不需要網路連線即可查看
- ✅ **完整渲染**：所有 Mermaid 圖表完整顯示
- ✅ **跨平台**：任何瀏覽器都可以開啟
- ✅ **格式保留**：保持原始 Markdown 的所有格式
- ✅ **可分享**：直接傳送 HTML 文件給他人查看

### 檔案特徵

- **檔案大小**：通常 100-500 KB（含嵌入的 CSS 和 JS）
- **Mermaid 支援**：完整的 JavaScript 渲染引擎
- **樣式**：GitHub Light 主題（預設）
- **語法高亮**：程式碼區塊有完整的語法高亮

---

## 🎨 自訂樣式

### 使用自訂 CSS

如果要自訂 HTML 的外觀，可以建立 `custom-style.css`：

**檔案位置**：`docs/html/custom-style.css`

**在 Markdown 中引用**：
```markdown
<link rel="stylesheet" href="html/custom-style.css">
```

### 範例自訂樣式

```css
/* 修改標題顏色 */
h1 {
    color: #1976D2;
    border-bottom: 3px solid #1976D2;
}

/* 修改 Mermaid 圖表背景 */
.mermaid {
    background-color: #F5F5F5;
    padding: 20px;
    border-radius: 8px;
}

/* 修改程式碼區塊樣式 */
pre {
    background-color: #F8F8F8;
    border: 1px solid #DDD;
}
```

---

## 🔧 維護建議

### 定期更新

當 Markdown 文件更新後，記得重新匯出 HTML：

```bash
# 檢查哪些 Markdown 文件更新了
git status docs/*.md

# 重新匯出更新的文件
# （使用 VS Code 手動匯出或執行批量腳本）

# 提交更新的 HTML
git add docs/html/
git commit -m "更新 HTML 匯出文件"
```

### 清理舊文件

如果 Markdown 文件被刪除或重新命名，記得清理對應的 HTML：

```bash
# 查看 HTML 目錄
ls -lh docs/html/

# 刪除不需要的 HTML
rm docs/html/舊檔名.html
```

---

## 📝 Git 配置

### .gitignore 設定

HTML 文件是從 Markdown 生成的，可以選擇：

**選項 A：不提交 HTML（推薦用於開發階段）**
```gitignore
# 不追蹤 HTML 匯出文件
docs/html/*.html
!docs/html/README.html
```

**選項 B：提交 HTML（推薦用於發布階段）**
```gitignore
# 追蹤所有 HTML 文件
# （不添加到 .gitignore）
```

### 本專案配置

目前配置：HTML 文件**不納入** Git 版本控制（除了 README.html）

原因：
- HTML 可以隨時從 Markdown 重新生成
- 減少 Git 倉庫大小
- 避免頻繁的 HTML 更新造成提交噪音

**如需分享 HTML 文件**：
- 使用 GitHub Releases 附加 ZIP 檔
- 或建立專門的 `gh-pages` 分支

---

## 🌐 線上預覽

### 使用 GitHub Pages

如果要在網頁上公開這些 HTML：

1. **啟用 GitHub Pages**：
   - 進入專案 Settings → Pages
   - Source 選擇 `main` 分支
   - 目錄選擇 `/docs`

2. **訪問 HTML**：
   ```
   https://[username].github.io/PatentWriterAgent/html/A0_system_idef0.html
   ```

### 使用本地伺服器

在專案根目錄啟動簡單的 HTTP 伺服器：

**Python**：
```bash
# Python 3
python -m http.server 8000

# 訪問
http://localhost:8000/docs/html/A0_system_idef0.html
```

**Node.js**：
```bash
# 安裝 http-server
npm install -g http-server

# 啟動
http-server -p 8000

# 訪問
http://localhost:8000/docs/html/A0_system_idef0.html
```

---

## 📚 相關文件

- [Markdown匯出HTML指南](../troubleshooting/Markdown匯出HTML指南.md) - 詳細的匯出操作說明
- [Mermaid_使用指南](../troubleshooting/Mermaid_使用指南.md) - Mermaid 語法參考
- [2025-10-30_Mermaid配置與擴充套件設定](../troubleshooting/2025-10-30_Mermaid配置與擴充套件設定.md) - 預覽環境配置

---

## ✉️ 問題回報

如果匯出的 HTML 有問題：

1. 查看 [Markdown匯出HTML指南 - 常見問題](../troubleshooting/Markdown匯出HTML指南.md#常見問題)
2. 檢查 Markdown Preview Enhanced 的設定
3. 在專案中提交 Issue

---

**目錄建立日期**：2025-10-30
**維護者**：專案團隊
**匯出工具**：Markdown Preview Enhanced v0.8.19
