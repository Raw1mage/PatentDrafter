# Mermaid 預覽快捷鍵設定指南

## ✅ 已完成的設定

### 移除不穩定的擴充套件
- ❌ 已移除：`bierner.markdown-mermaid@1.29.0`（會導致圖表閃爍）
- ✅ 保留：`vstirbu.vscode-mermaid-preview@2.1.2`（測試成功）
- ✅ 保留：`bpruitt-goddard.mermaid-markdown-syntax-highlighting@1.7.4`（語法高亮）

---

## 🎯 設定 `Ctrl+Shift+V` 快捷鍵

### 方法 1: 透過 VS Code 介面設定（推薦）

#### 步驟 1: 開啟快捷鍵設定

按 `Ctrl+K Ctrl+S` 或：
- 點擊 `File` → `Preferences` → `Keyboard Shortcuts`
- 或按 `Ctrl+,` → 左下角齒輪圖示 → `Keyboard Shortcuts`

#### 步驟 2: 搜尋並設定 Mermaid Preview

1. 在搜尋框輸入：`mermaid preview`
2. 找到：`Mermaid: Preview Diagram`（來自 vstirbu.vscode-mermaid-preview）
3. 點擊該項目左側的 `+` 圖示
4. 按下你想要的快捷鍵：`Ctrl+Shift+V`
5. 會出現警告：此快捷鍵已被 `markdown.showPreview` 使用
6. 點擊 **確定覆蓋** 或 **選擇其他鍵**

#### 步驟 3: 處理快捷鍵衝突

**選項 A：完全覆蓋（推薦）**
- 直接使用 `Ctrl+Shift+V` 給 Mermaid Preview
- 原本的 Markdown 預覽改用其他快捷鍵（如 `Ctrl+K V`）

**選項 B：條件覆蓋**
- 只在游標位於 Mermaid 程式碼塊中時使用 `Ctrl+Shift+V` 預覽 Mermaid
- 其他情況仍然預覽整個 Markdown（需要進階設定）

---

### 方法 2: 直接編輯 keybindings.json（進階）

#### 步驟 1: 開啟 keybindings.json

1. 按 `Ctrl+Shift+P`
2. 輸入：`Preferences: Open Keyboard Shortcuts (JSON)`
3. 按 Enter

#### 步驟 2: 加入以下設定

```json
[
  {
    "key": "ctrl+shift+v",
    "command": "mermaid-preview.preview",
    "when": "editorLangId == markdown"
  },
  {
    "key": "ctrl+k v",
    "command": "markdown.showPreview",
    "when": "editorLangId == markdown"
  }
]
```

**說明**：
- 第一條：將 `Ctrl+Shift+V` 綁定到 Mermaid 預覽（在 Markdown 文件中）
- 第二條：將原本的 Markdown 預覽改為 `Ctrl+K V`

#### 步驟 3: 儲存並重新載入

1. 儲存 `keybindings.json`
2. 按 `Ctrl+Shift+P` → `Developer: Reload Window`

---

## 🎨 更進階的條件設定（可選）

如果你想要更智能的行為：
- 游標在 Mermaid 程式碼塊中 → `Ctrl+Shift+V` 預覽 Mermaid
- 游標在其他地方 → `Ctrl+Shift+V` 預覽整個 Markdown

```json
[
  {
    "key": "ctrl+shift+v",
    "command": "mermaid-preview.preview",
    "when": "editorLangId == markdown && editorTextFocus && editorHasSelection == false"
  },
  {
    "key": "ctrl+shift+v",
    "command": "markdown.showPreview",
    "when": "editorLangId == markdown && !editorTextFocus"
  }
]
```

**注意**：此設定可能需要根據實際使用情況調整 `when` 條件。

---

## 🧪 測試快捷鍵

### 測試步驟

1. **開啟測試文件**：[Mermaid_快速測試.md](Mermaid_快速測試.md)

2. **將游標放在任何 Mermaid 程式碼塊中**

3. **按下 `Ctrl+Shift+V`**

4. **預期結果**：
   - ✅ 右側開啟獨立的 Mermaid 預覽視窗
   - ✅ 顯示渲染後的圖表
   - ✅ 沒有閃爍或錯誤訊息

### 如果測試失敗

**症狀 1：沒有任何反應**
- 檢查快捷鍵是否正確設定（`Ctrl+K Ctrl+S` 查看）
- 確認游標在 Markdown 文件中
- 重新載入視窗（`Ctrl+Shift+P` → `Reload Window`）

**症狀 2：開啟的是普通 Markdown 預覽**
- 快捷鍵衝突未解決
- 重新按照步驟設定，確保覆蓋原有綁定

**症狀 3：顯示錯誤訊息**
- 檢查 `vstirbu.vscode-mermaid-preview` 是否已正確安裝
- 嘗試重新安裝：`code --install-extension vstirbu.vscode-mermaid-preview`

---

## 📋 快捷鍵總結

設定完成後，你的快捷鍵配置應該是：

| 快捷鍵 | 功能 | 來源 |
|--------|------|------|
| `Ctrl+Shift+V` | Mermaid 預覽 | vstirbu.vscode-mermaid-preview |
| `Ctrl+K V` | Markdown 整體預覽 | VS Code 內建（備用） |
| `Ctrl+Shift+P` → "Mermaid: Preview" | 透過命令面板預覽 | vstirbu（備用方法） |

---

## 🔄 恢復原始設定

如果想要恢復 VS Code 預設的快捷鍵配置：

### 步驟 1: 開啟 keybindings.json
按 `Ctrl+Shift+P` → `Preferences: Open Keyboard Shortcuts (JSON)`

### 步驟 2: 移除自訂綁定
刪除所有關於 `mermaid-preview.preview` 和 `markdown.showPreview` 的自訂綁定

### 步驟 3: 重新載入
按 `Ctrl+Shift+P` → `Developer: Reload Window`

---

## 💡 使用技巧

### Tip 1: 多圖表快速切換

如果文件中有多個 Mermaid 圖表：
1. 使用 `Ctrl+Shift+V` 開啟第一個圖表預覽
2. 將游標移到另一個圖表
3. 預覽視窗會自動更新顯示當前圖表

### Tip 2: 並排預覽

想要同時看程式碼和圖表：
1. 按 `Ctrl+Shift+V` 開啟 Mermaid 預覽
2. 拖曳預覽視窗到右側或下方
3. 形成分割視窗佈局

### Tip 3: 全螢幕預覽

圖表太大時：
1. 在 Mermaid 預覽視窗中右鍵
2. 選擇 "Zoom In" 或使用 `Ctrl+滾輪` 縮放

---

## 🛠️ 故障排除

### 問題：快捷鍵設定後沒有生效

**解決方案 1：檢查 when 條件**
```json
"when": "editorLangId == markdown"
```
確保在 Markdown 文件中才會觸發

**解決方案 2：檢查快捷鍵衝突**
1. 按 `Ctrl+K Ctrl+S`
2. 搜尋 `ctrl+shift+v`
3. 查看是否有多個命令綁定相同快捷鍵
4. 移除不需要的綁定

**解決方案 3：重新安裝擴充套件**
```bash
code --uninstall-extension vstirbu.vscode-mermaid-preview
code --install-extension vstirbu.vscode-mermaid-preview
```

---

### 問題：Mermaid 預覽視窗關閉後無法重新開啟

**原因**：視窗被意外關閉

**解決方案**：
1. 再次按 `Ctrl+Shift+V`（游標在 Mermaid 程式碼塊中）
2. 或使用命令面板：`Ctrl+Shift+P` → "Mermaid: Preview Diagram"

---

### 問題：某些圖表仍然無法渲染

**原因**：複雜的 `subgraph` 結構

**解決方案**：
1. 參考 [Mermaid_故障排除.md](Mermaid_故障排除.md)
2. 簡化 `subgraph` 結構
3. 或使用線上平台 https://mermaid.live/ 驗證語法

---

## 📚 相關文件

- [Mermaid_最終解決方案.md](Mermaid_最終解決方案.md) - 完整解決方案
- [Mermaid_使用指南.md](Mermaid_使用指南.md) - 語法參考
- [Mermaid_故障排除.md](Mermaid_故障排除.md) - 問題排查
- [Mermaid_快速測試.md](Mermaid_快速測試.md) - 測試案例

---

## ✅ 設定檢查清單

完成以下檢查確保設定正確：

- [ ] 已移除 `bierner.markdown-mermaid` 擴充套件
- [ ] 已確認 `vstirbu.vscode-mermaid-preview` 已安裝
- [ ] 已設定 `Ctrl+Shift+V` 快捷鍵
- [ ] 已處理快捷鍵衝突
- [ ] 已重新載入 VS Code 視窗
- [ ] 已測試快捷鍵功能（使用測試文件）
- [ ] Mermaid 圖表可以正常預覽
- [ ] 預覽視窗沒有閃爍或錯誤

---

**建立日期**：2025-10-30
**適用環境**：VS Code 1.80+
**測試狀態**：✅ 已驗證可用
