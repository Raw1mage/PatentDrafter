# Markdown 匯出 HTML 指南

**建立日期**：2025-10-30
**適用工具**：Markdown Preview Enhanced
**目標目錄**：`docs/html/`

---

## 📋 目錄

1. [快速開始](#快速開始)
2. [單一文件匯出](#單一文件匯出)
3. [批量匯出](#批量匯出)
4. [匯出設定](#匯出設定)
5. [自訂樣式](#自訂樣式)
6. [常見問題](#常見問題)

---

## 快速開始

### 方法 1：右鍵選單匯出（推薦）

1. **開啟 Markdown 文件**
2. **按 `Ctrl+Shift+V` 開啟預覽**
3. **在預覽視窗中右鍵**
4. **選擇「Chrome (Puppeteer)」→「HTML」**
5. HTML 文件會自動儲存到同一目錄

### 方法 2：命令面板匯出

1. **開啟 Markdown 文件**
2. **按 `Ctrl+Shift+P`**
3. **輸入「Markdown Preview Enhanced: HTML Export」**
4. **按 Enter**
5. HTML 文件會自動生成

### 方法 3：快捷鍵匯出（需設定）

設定快捷鍵後可以直接按鍵匯出：
```json
{
    "key": "ctrl+shift+e",
    "command": "markdown-preview-enhanced.customizeCSS",
    "when": "editorLangId == markdown"
}
```

---

## 單一文件匯出

### 基本匯出流程

#### 步驟 1：開啟預覽
```
開啟 Markdown 文件 → 按 Ctrl+Shift+V
```

#### 步驟 2：觸發匯出
**方式 A：右鍵選單**
```
預覽視窗右鍵 → HTML → HTML (offline)
```

**方式 B：命令面板**
```
Ctrl+Shift+P → "Markdown Preview Enhanced: HTML"
```

#### 步驟 3：移動到目標目錄
```bash
# 假設匯出的檔案在原目錄
mv docs/A0_system_idef0.html docs/html/

# 或使用 Windows 命令
move docs\A0_system_idef0.html docs\html\
```

---

### 匯出選項說明

Markdown Preview Enhanced 提供多種 HTML 匯出選項：

#### 1. HTML (offline)（推薦）
- **特點**：包含所有 CSS 和資源
- **優點**：可以離線查看，不需網路
- **檔案大小**：較大（約 200-500 KB）
- **Mermaid 支援**：✅ 完整支援

#### 2. HTML (CDN hosted)
- **特點**：從 CDN 載入資源
- **優點**：檔案較小
- **缺點**：需要網路連線
- **Mermaid 支援**：✅ 完整支援

#### 3. HTML (Image embedded)
- **特點**：將圖片轉為 base64 嵌入
- **優點**：單一檔案包含所有內容
- **檔案大小**：最大
- **Mermaid 支援**：⚠️ 圖表會轉為圖片

---

### 單一文件匯出範例

**匯出 IDEF0 架構文件**：

```bash
# 1. 在 VS Code 中開啟文件
code docs/A0_system_idef0.md

# 2. 按 Ctrl+Shift+V 開啟預覽
# 3. 右鍵 → HTML → HTML (offline)
# 4. 會在相同目錄生成 A0_system_idef0.html

# 5. 移動到 html 目錄
mv docs/A0_system_idef0.html docs/html/
```

---

## 批量匯出

### 使用批量匯出腳本

我為你建立了一個批量匯出腳本：`export_docs_to_html.sh`

#### 腳本內容

```bash
#!/bin/bash

# 批量匯出 Markdown 為 HTML
# 目標目錄：docs/html/

echo "🚀 開始批量匯出 Markdown 文件為 HTML..."
echo "==========================================="

# 設定來源和目標目錄
SOURCE_DIR="docs"
OUTPUT_DIR="docs/html"

# 確保輸出目錄存在
mkdir -p "$OUTPUT_DIR"

# 需要匯出的文件清單（IDEF0 架構文件）
FILES=(
    "$SOURCE_DIR/A0_system_idef0.md"
    "$SOURCE_DIR/A1_UI_Management_IDEF0.md"
    "$SOURCE_DIR/A2_Document_Parsing_IDEF0.md"
    "$SOURCE_DIR/A3_Patent_Search_IDEF0.md"
    "$SOURCE_DIR/A4_Outline_Generation_IDEF0.md"
    "$SOURCE_DIR/A5_Content_Writing_IDEF0.md"
    "$SOURCE_DIR/A6_Diagram_Generation_IDEF0.md"
    "$SOURCE_DIR/A7_Document_Merging_IDEF0.md"
    "$SOURCE_DIR/A8_Workflow_Control_IDEF0.md"
)

# 計數器
total=${#FILES[@]}
success=0
failed=0

echo "準備匯出 $total 個文件..."
echo ""

# 遍歷文件清單
for file in "${FILES[@]}"; do
    if [ -f "$file" ]; then
        filename=$(basename "$file" .md)
        echo "📄 處理: $filename.md"

        # 使用 VS Code CLI 開啟文件（會觸發 Markdown Preview Enhanced）
        code "$file"

        # 等待 VS Code 開啟
        sleep 2

        # 提示使用者手動匯出（因為 VS Code 沒有 CLI 匯出命令）
        echo "   ⏸️  請在 VS Code 中："
        echo "      1. 按 Ctrl+Shift+V 開啟預覽"
        echo "      2. 右鍵 → HTML → HTML (offline)"
        echo "      3. 完成後按 Enter 繼續..."
        read -p ""

        # 檢查是否生成了 HTML 文件
        html_file="$SOURCE_DIR/$filename.html"
        if [ -f "$html_file" ]; then
            # 移動到目標目錄
            mv "$html_file" "$OUTPUT_DIR/"
            echo "   ✅ 已匯出: $OUTPUT_DIR/$filename.html"
            ((success++))
        else
            echo "   ❌ 未找到匯出文件: $html_file"
            ((failed++))
        fi

        echo ""
    else
        echo "⚠️  文件不存在: $file"
        ((failed++))
        echo ""
    fi
done

echo "==========================================="
echo "📊 匯出完成！"
echo "   總計: $total 個文件"
echo "   成功: $success 個"
echo "   失敗: $failed 個"
echo ""
echo "HTML 文件位置: $OUTPUT_DIR/"
echo "==========================================="
```

#### 使用方法

```bash
# 賦予執行權限
chmod +x export_docs_to_html.sh

# 執行腳本
./export_docs_to_html.sh
```

---

### 半自動化批量匯出（推薦）

由於 Markdown Preview Enhanced 沒有提供 CLI 匯出命令，建議使用以下流程：

#### 步驟 1：準備文件清單
在 `docs/` 目錄中執行：
```bash
ls A*.md > files_to_export.txt
```

#### 步驟 2：逐個手動匯出
```bash
# 開啟文件
code docs/A0_system_idef0.md

# 在 VS Code 中：
# 1. Ctrl+Shift+V（開啟預覽）
# 2. 右鍵 → HTML → HTML (offline)
# 3. 關閉文件

# 移動生成的 HTML
mv docs/A0_system_idef0.html docs/html/

# 重複以上步驟處理其他文件...
```

#### 步驟 3：批量移動（可選）
如果所有 HTML 都生成在 `docs/` 中：
```bash
mv docs/*.html docs/html/
```

---

### PowerShell 批量匯出腳本（Windows）

```powershell
# export_to_html.ps1

$sourceDir = "docs"
$outputDir = "docs\html"

# 確保輸出目錄存在
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null

# 文件清單
$files = @(
    "A0_system_idef0.md",
    "A1_UI_Management_IDEF0.md",
    "A2_Document_Parsing_IDEF0.md",
    "A3_Patent_Search_IDEF0.md",
    "A4_Outline_Generation_IDEF0.md",
    "A5_Content_Writing_IDEF0.md",
    "A6_Diagram_Generation_IDEF0.md",
    "A7_Document_Merging_IDEF0.md",
    "A8_Workflow_Control_IDEF0.md"
)

Write-Host "🚀 開始匯出 Markdown 文件..." -ForegroundColor Green

foreach ($file in $files) {
    $mdPath = Join-Path $sourceDir $file
    $filename = [System.IO.Path]::GetFileNameWithoutExtension($file)
    $htmlPath = Join-Path $sourceDir "$filename.html"
    $targetPath = Join-Path $outputDir "$filename.html"

    Write-Host "`n📄 處理: $file" -ForegroundColor Cyan

    # 開啟 VS Code
    code $mdPath

    # 等待使用者匯出
    Write-Host "   請在 VS Code 中按 Ctrl+Shift+V，右鍵匯出 HTML" -ForegroundColor Yellow
    Write-Host "   完成後按 Enter 繼續..." -ForegroundColor Yellow
    Read-Host

    # 移動文件
    if (Test-Path $htmlPath) {
        Move-Item -Path $htmlPath -Destination $targetPath -Force
        Write-Host "   ✅ 已匯出: $targetPath" -ForegroundColor Green
    } else {
        Write-Host "   ❌ 未找到: $htmlPath" -ForegroundColor Red
    }
}

Write-Host "`n✅ 匯出完成！" -ForegroundColor Green
Write-Host "HTML 文件位置: $outputDir" -ForegroundColor Cyan
```

**使用方法**：
```powershell
# 執行腳本
.\export_to_html.ps1
```

---

## 匯出設定

### 配置 Markdown Preview Enhanced

在 VS Code 設定中配置匯出選項：

**檔案位置**：`settings.json`

```json
{
  // Markdown Preview Enhanced 匯出設定
  "markdown-preview-enhanced.HTML": {
    // 是否嵌入本地圖片（使用 base64）
    "embedLocalImages": false,

    // 是否嵌入 SVG（作為 <img>）
    "embedSVG": true,

    // 是否離線使用（嵌入所有 CSS 和 JS）
    "offline": true,

    // 是否包含預設樣式
    "useDefaultStyles": true
  },

  // 是否在匯出時自動開啟
  "markdown-preview-enhanced.automaticallyShowPreviewOfMarkdownBeingEdited": false,

  // Mermaid 主題（影響匯出的圖表樣式）
  "markdown-preview-enhanced.mermaidTheme": "default",

  // 程式碼區塊主題
  "markdown-preview-enhanced.codeBlockTheme": "github.css",

  // 預覽主題（影響匯出的整體樣式）
  "markdown-preview-enhanced.previewTheme": "github-light.css"
}
```

---

### 匯出前檢查清單

- [ ] Mermaid 圖表在預覽中正常顯示
- [ ] 所有圖片連結正確
- [ ] 目錄（TOC）正確生成
- [ ] 程式碼區塊格式正確
- [ ] 數學公式（如有）正確渲染

---

## 自訂樣式

### 使用自訂 CSS

#### 步驟 1：建立自訂 CSS 文件

**檔案位置**：`docs/html/custom-style.css`

```css
/* 自訂 HTML 匯出樣式 */

/* 整體容器 */
.markdown-preview-enhanced {
    max-width: 1200px;
    margin: 0 auto;
    padding: 20px;
    font-family: 'Segoe UI', -apple-system, BlinkMacSystemFont, sans-serif;
}

/* 標題樣式 */
h1 {
    color: #1976D2;
    border-bottom: 3px solid #1976D2;
    padding-bottom: 10px;
    margin-top: 40px;
}

h2 {
    color: #388E3C;
    border-bottom: 2px solid #C8E6C9;
    padding-bottom: 8px;
    margin-top: 30px;
}

h3 {
    color: #F57C00;
    margin-top: 25px;
}

/* Mermaid 圖表容器 */
.mermaid {
    text-align: center;
    margin: 30px 0;
    padding: 20px;
    background-color: #F5F5F5;
    border-radius: 8px;
    border: 1px solid #E0E0E0;
}

/* 程式碼區塊 */
pre {
    background-color: #F8F8F8;
    border: 1px solid #DDDDDD;
    border-radius: 5px;
    padding: 15px;
    overflow-x: auto;
}

code {
    background-color: #F0F0F0;
    padding: 2px 6px;
    border-radius: 3px;
    font-family: 'Consolas', 'Monaco', monospace;
}

/* 表格樣式 */
table {
    border-collapse: collapse;
    width: 100%;
    margin: 20px 0;
}

th {
    background-color: #E3F2FD;
    color: #1976D2;
    font-weight: bold;
    padding: 12px;
    text-align: left;
    border: 1px solid #BBDEFB;
}

td {
    padding: 10px;
    border: 1px solid #E0E0E0;
}

tr:nth-child(even) {
    background-color: #FAFAFA;
}

/* 連結樣式 */
a {
    color: #1976D2;
    text-decoration: none;
}

a:hover {
    text-decoration: underline;
}

/* 引用區塊 */
blockquote {
    border-left: 4px solid #1976D2;
    padding-left: 20px;
    margin: 20px 0;
    background-color: #F5F5F5;
    padding: 15px 20px;
    border-radius: 0 5px 5px 0;
}

/* 列表項目 */
ul, ol {
    line-height: 1.8;
}

/* 水平線 */
hr {
    border: none;
    border-top: 2px solid #E0E0E0;
    margin: 40px 0;
}

/* 頁尾 */
.page-footer {
    margin-top: 60px;
    padding-top: 20px;
    border-top: 1px solid #E0E0E0;
    text-align: center;
    color: #757575;
    font-size: 0.9em;
}

/* 打印樣式 */
@media print {
    .markdown-preview-enhanced {
        max-width: 100%;
    }

    .mermaid {
        page-break-inside: avoid;
    }

    h1, h2, h3 {
        page-break-after: avoid;
    }
}
```

#### 步驟 2：在 Markdown 中引用

在 Markdown 文件開頭添加：

```markdown
---
html:
  toc: true
  offline: true
  embed_local_images: false
export_on_save:
  html: true
---

<link rel="stylesheet" href="html/custom-style.css">

# 文件標題

您的內容...
```

---

### Front Matter 設定

在 Markdown 文件開頭使用 YAML Front Matter 控制匯出：

```yaml
---
html:
  # 是否嵌入本地圖片
  embed_local_images: false

  # 是否使用 CDN（false 表示離線）
  cdn: false

  # 自訂 CSS
  include_default_styles: true

  # 程式碼高亮主題
  highlight_style: github.css

# 自動匯出設定（儲存時自動匯出）
export_on_save:
  html: true

# 是否生成目錄
toc:
  depth_from: 1
  depth_to: 3
  ordered: false
---
```

---

## 常見問題

### Q1: Mermaid 圖表沒有正確顯示

**原因**：
- 離線模式下 Mermaid.js 未正確嵌入
- 瀏覽器 JavaScript 被禁用

**解決方案**：
1. 確保使用「HTML (offline)」匯出選項
2. 在預覽中確認圖表正確顯示後再匯出
3. 檢查匯出的 HTML 中是否包含 `<script>` 標籤

---

### Q2: 文件中的圖片無法顯示

**原因**：
- 圖片路徑是相對路徑
- HTML 文件移動後路徑失效

**解決方案**：

**方式 A**：使用絕對路徑
```markdown
![圖片](file:///D:/Users/yeats/GitHub/PatentWriterAgent/images/diagram.png)
```

**方式 B**：嵌入圖片（base64）
在 Front Matter 中設定：
```yaml
---
html:
  embed_local_images: true
---
```

**方式 C**：保持相對路徑結構
```
docs/
├── html/
│   ├── A0_system_idef0.html
│   └── images/           # 複製圖片到這裡
│       └── diagram.png
└── images/
    └── diagram.png
```

---

### Q3: 匯出的 HTML 檔案很大

**原因**：
- 使用了「HTML (offline)」選項
- 嵌入了大量圖片

**解決方案**：
- 使用「HTML (CDN hosted)」選項（需要網路）
- 不要嵌入圖片（`embed_local_images: false`）
- 壓縮圖片檔案大小

---

### Q4: 無法批量匯出

**原因**：
- Markdown Preview Enhanced 沒有提供 CLI 匯出命令

**解決方案**：
- 使用提供的半自動化腳本
- 或手動逐個匯出（推薦用於小量文件）

**替代方案**：
使用 Pandoc 批量轉換：
```bash
# 安裝 Pandoc
# https://pandoc.org/installing.html

# 批量轉換
for file in docs/A*.md; do
    filename=$(basename "$file" .md)
    pandoc "$file" -o "docs/html/$filename.html" \
        --standalone \
        --self-contained \
        --css=docs/html/custom-style.css
done
```

**注意**：Pandoc 不支援 Mermaid 圖表，需要先轉為圖片。

---

### Q5: 目錄（TOC）沒有生成

**解決方案**：

在 Markdown 文件中添加：
```markdown
<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=3 orderedList=false} -->
```

或在 Front Matter 中設定：
```yaml
---
toc:
  depth_from: 1
  depth_to: 3
  ordered: false
---
```

然後按 `Ctrl+Shift+P` → "Markdown Preview Enhanced: Create TOC"

---

## 附錄

### A. 目錄結構

```
PatentWriterAgent/
├── docs/
│   ├── html/                       # HTML 匯出目錄
│   │   ├── A0_system_idef0.html   # 匯出的 HTML 文件
│   │   ├── A1_UI_Management_IDEF0.html
│   │   ├── ...
│   │   ├── custom-style.css       # 自訂樣式
│   │   └── images/                # 圖片資源（可選）
│   │
│   ├── A0_system_idef0.md         # 原始 Markdown 文件
│   ├── A1_UI_Management_IDEF0.md
│   └── ...
│
└── export_to_html.sh              # 批量匯出腳本
```

---

### B. 匯出檢查清單

匯出後確認以下項目：

- [ ] HTML 文件可以在瀏覽器中正常開啟
- [ ] 所有 Mermaid 圖表正確顯示
- [ ] 標題層級和目錄正確
- [ ] 程式碼區塊格式正確
- [ ] 表格樣式正常
- [ ] 連結可以點擊（內部連結和外部連結）
- [ ] 圖片正常顯示
- [ ] 文件大小合理（< 1MB 為佳）

---

### C. 快速參考

**常用命令**：
```bash
# 單一匯出（在 VS Code 中）
Ctrl+Shift+V → 右鍵 → HTML (offline)

# 移動到目標目錄
mv docs/*.html docs/html/

# 批量匯出（使用腳本）
./export_to_html.sh

# 檢查匯出結果
ls -lh docs/html/
```

**匯出選項對比**：
| 選項 | 檔案大小 | 離線可用 | Mermaid 支援 | 推薦度 |
|------|---------|---------|-------------|--------|
| HTML (offline) | 大 | ✅ | ✅ | ⭐⭐⭐⭐⭐ |
| HTML (CDN) | 小 | ❌ | ✅ | ⭐⭐⭐ |
| HTML (Image) | 最大 | ✅ | ⚠️ | ⭐⭐ |

---

**文件建立時間**：2025-10-30
**最後更新時間**：2025-10-30
**適用版本**：Markdown Preview Enhanced v0.8.19+
