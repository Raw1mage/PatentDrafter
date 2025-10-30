# Mermaid 閃爍問題 - 最終解決方案

## ✅ 問題已解決

**症狀**：Mermaid 圖表在 VS Code Markdown 預覽中「閃一下就消失」

**根本原因**：`bierner.markdown-mermaid@1.29.0` 擴充套件在整合預覽中的渲染引擎不穩定

**解決方案**：使用 `vstirbu.vscode-mermaid-preview@2.1.2` 的獨立預覽視窗

---

## 📌 標準操作流程

### 方法 1: 命令面板（每次手動）

1. 將游標放在 Mermaid 程式碼塊中
2. 按 `Ctrl+Shift+P`
3. 輸入 "mermaid preview"
4. 選擇 "Mermaid: Preview Diagram"
5. 在右側獨立視窗中查看圖表

### 方法 2: 設定快捷鍵（推薦）

#### 步驟 1: 開啟快捷鍵設定

- 按 `Ctrl+K Ctrl+S`
- 或 `File` → `Preferences` → `Keyboard Shortcuts`

#### 步驟 2: 搜尋並設定

1. 在搜尋框輸入：`mermaid preview`
2. 找到：`Mermaid: Preview Diagram`
3. 點擊左側的 `+` 圖示
4. 按下你想要的快捷鍵組合，例如：
   - **`Ctrl+Alt+M`**（推薦）
   - 或 `Ctrl+Shift+M`
   - 或任何你習慣的組合

#### 步驟 3: 測試

1. 開啟任何包含 Mermaid 的 Markdown 文件
2. 將游標放在 Mermaid 程式碼塊中
3. 按你設定的快捷鍵（如 `Ctrl+Alt+M`）
4. 應該立即開啟預覽視窗

---

## 🔧 可選優化：停用 bierner 擴充套件

如果你不需要在 Markdown 整體預覽中看到 Mermaid（只用獨立視窗），可以停用有問題的擴充套件：

### 步驟

1. 按 `Ctrl+Shift+X` 開啟擴充套件面板
2. 搜尋 "markdown mermaid"
3. 找到 "Markdown Preview Mermaid Support" (bierner)
4. 點擊 **"Disable"**
5. 按 `Ctrl+Shift+P` → "Reload Window"

### 權衡考量

**停用的優點**：
- 避免 Markdown 預覽中的閃爍問題
- 減少擴充套件衝突
- VS Code 效能可能稍微提升

**停用的缺點**：
- 無法在 `Ctrl+Shift+V` 的 Markdown 整體預覽中看到 Mermaid 圖表
- 必須使用獨立預覽視窗（但這本來就是更穩定的方式）

**建議**：保持啟用狀態，只在需要時使用獨立預覽

---

## 📊 工作流程建議

### 日常撰寫文件

1. **Markdown 文字內容**：使用 `Ctrl+Shift+V` 預覽整體排版
2. **Mermaid 圖表**：將游標放在圖表中 → 按 `Ctrl+Alt+M` → 在獨立視窗預覽

### 文件交付前檢查

1. **本地檢查**：使用獨立預覽視窗確認所有圖表
2. **線上驗證**：將圖表複製到 https://mermaid.live/ 最終確認
3. **匯出圖片**（可選）：在線上平台匯出 PNG/SVG

### 團隊協作

在專案 README 中說明：
```markdown
## Mermaid 圖表預覽方法

本專案文件包含 Mermaid 圖表，建議使用以下方式預覽：

1. **VS Code 使用者**：
   - 安裝 `vstirbu.vscode-mermaid-preview` 擴充套件
   - 游標放在圖表中 → `Ctrl+Shift+P` → "Mermaid: Preview Diagram"
   - 建議設定快捷鍵 `Ctrl+Alt+M`

2. **線上預覽**（所有平台）：
   - 訪問 https://mermaid.live/
   - 複製 Mermaid 程式碼貼上即可預覽
```

---

## 🎯 本專案的 Mermaid 使用統計

```bash
# 執行檢查腳本
bash check_mermaid.sh
```

**統計結果**（2025-10-30）：
- 總 Markdown 文件數：27
- 包含 Mermaid 的文件：16
- Mermaid 區塊總數：77
  - ✅ flowchart 語法：57 個（推薦語法）
  - ⚠️ 使用 subgraph：20 個（需用獨立預覽）
  - ✅ graph 語法：0 個（已全部修復）

**結論**：所有圖表語法正確，使用獨立預覽視窗即可正常渲染。

---

## 📚 相關文件

- [Mermaid 使用指南](Mermaid_使用指南.md) - 基礎語法和功能介紹
- [Mermaid 測試文件](Mermaid_測試.md) - 基本功能測試
- [Mermaid 快速測試](Mermaid_快速測試.md) - 診斷用測試案例
- [Mermaid 故障排除](Mermaid_故障排除.md) - 完整的問題排查指南
- [Mermaid 擴充套件切換指南](Mermaid_擴充套件切換指南.md) - 7 種解決方案詳解

---

## ✉️ 後續支援

如有其他 Mermaid 相關問題：

1. **語法問題**：參考 [Mermaid 官方文件](https://mermaid.js.org/)
2. **VS Code 擴充套件問題**：
   - [vstirbu 擴充套件 Issues](https://github.com/vstirbu/vscode-mermaid-preview/issues)
   - [bierner 擴充套件 Issues](https://github.com/mjbvz/vscode-markdown-mermaid/issues)
3. **本專案問題**：查看 [Mermaid 故障排除](Mermaid_故障排除.md)

---

**最後更新**：2025-10-30
**問題狀態**：✅ 已解決
**推薦方案**：使用 vstirbu 獨立預覽視窗 + 快捷鍵 `Ctrl+Alt+M`
