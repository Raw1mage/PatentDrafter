# Mermaid 擴充套件切換指南

## 🔴 問題症狀

**「圖閃一下就消失，然後顯示錯誤訊息」**

這表示：
- ✅ Mermaid 語法正確（引擎開始渲染了）
- ❌ VS Code 預覽擴充套件的渲染引擎在執行過程中崩潰

---

## 解決方案 1: 切換到獨立預覽窗口

您已經安裝了 `vstirbu.vscode-mermaid-preview@2.1.2`，它有**獨立的渲染引擎**。

### 使用步驟

1. **開啟測試檔案**：[`Mermaid_快速測試.md`](Mermaid_快速測試.md)

2. **將游標放在任意 Mermaid 程式碼塊中**

3. **開啟預覽**（三種方式任選）：
   - **快捷鍵**：無預設快捷鍵，需自行設定
   - **命令面板**：`Ctrl+Shift+P` → 輸入 "Mermaid: Preview" → 選擇
   - **右鍵選單**：在程式碼塊中右鍵 → "Preview Mermaid Diagram"

4. **查看獨立預覽視窗**：會在右側開啟新的預覽分頁

### 優點
- 獨立渲染引擎，更穩定
- 不依賴 Markdown 預覽
- 可以單獨調試每個圖表

### 缺點
- 需要手動觸發預覽
- 無法在 Markdown 整體預覽中看到所有圖表

---

## 解決方案 2: 設定快捷鍵（提高效率）

### 步驟

1. **開啟鍵盤快捷鍵設定**：
   - `Ctrl+K Ctrl+S`
   - 或 `File` → `Preferences` → `Keyboard Shortcuts`

2. **搜尋 "mermaid preview"**

3. **找到 "Mermaid: Preview Diagram"**

4. **設定快捷鍵**（建議）：
   - `Ctrl+Alt+M`
   - 或任何您習慣的組合

5. **測試**：
   - 游標放在 Mermaid 程式碼塊中
   - 按下快捷鍵
   - 應該會立即開啟預覽視窗

---

## 解決方案 3: 停用 bierner.markdown-mermaid（暫時）

如果 `bierner.markdown-mermaid` 造成衝突，可以暫時停用：

### 步驟

1. **開啟擴充套件面板**：`Ctrl+Shift+X`

2. **搜尋 "markdown mermaid"**

3. **找到 "Markdown Preview Mermaid Support"**（bierner）

4. **點擊 "Disable"**

5. **重新載入視窗**：`Ctrl+Shift+P` → "Reload Window"

6. **測試**：開啟 [`Mermaid_快速測試.md`](Mermaid_快速測試.md)，使用 `vstirbu` 預覽

### 何時重新啟用

- 如果 `vstirbu` 預覽穩定，可以保持 `bierner` 停用
- 如果需要在 Markdown 整體預覽中看到 Mermaid，再啟用

---

## 解決方案 4: 嘗試 Markdown Preview Enhanced

這是一個功能更強大的替代方案。

### 安裝

```bash
code --install-extension shd101wyy.markdown-preview-enhanced
```

### 使用

1. 開啟 Markdown 文件
2. **快捷鍵**：`Ctrl+K V`（或 `Ctrl+Shift+V`）
3. 選擇 "Markdown Preview Enhanced" 預覽

### 優點
- 支援更多圖表類型（PlantUML, Graphviz, etc.）
- 渲染引擎更穩定
- 可匯出 PDF、HTML

### 缺點
- 較重量級，啟動較慢
- 設定選項複雜

---

## 解決方案 5: 檢查 VS Code 設定

某些設定可能影響 Mermaid 渲染。

### 檢查步驟

1. **開啟設定**：`Ctrl+,`

2. **搜尋 "mermaid"**

3. **檢查以下設定**：

   ```json
   {
     // Markdown Preview Mermaid Support (bierner)
     "markdown.mermaid.theme": "default",

     // 如果有這個設定，確保沒有拼寫錯誤
     "mermaid.theme": "default"
   }
   ```

4. **嘗試切換主題**：
   - `default`（預設）
   - `dark`（深色）
   - `forest`（綠色）
   - `neutral`（中性）

5. **測試**：更改主題後重新預覽

---

## 解決方案 6: 清除 VS Code 快取

快取損壞可能導致渲染問題。

### 步驟

1. **關閉 VS Code**

2. **刪除快取目錄**：
   ```bash
   # Windows
   rmdir /s /q "%APPDATA%\Code\Cache"
   rmdir /s /q "%APPDATA%\Code\CachedData"

   # 或使用 PowerShell
   Remove-Item -Recurse -Force "$env:APPDATA\Code\Cache"
   Remove-Item -Recurse -Force "$env:APPDATA\Code\CachedData"
   ```

3. **重新啟動 VS Code**

4. **測試**：預覽 Mermaid 圖表

---

## 解決方案 7: 降級擴充套件版本

有時新版本有 bug，降級可能解決問題。

### 步驟

1. **開啟擴充套件面板**：`Ctrl+Shift+X`

2. **找到 "Markdown Preview Mermaid Support"**

3. **點擊右上角的齒輪圖示** → "Install Another Version..."

4. **選擇較舊的版本**（如 `v1.28.0`）

5. **重新載入視窗**

6. **測試**

---

## 推薦的診斷流程

### 第 1 步：快速測試
開啟 [`Mermaid_快速測試.md`](Mermaid_快速測試.md)，按順序測試 4 個圖表：

1. **測試 1（最簡單）**：如果失敗 → 擴充套件安裝有問題
2. **測試 2（帶標籤）**：如果失敗 → 文字渲染有問題
3. **測試 3（中等複雜）**：如果失敗 → 邏輯結構有問題
4. **測試 4（有 subgraph）**：如果失敗 → 確認是 subgraph 問題

### 第 2 步：切換預覽方式
- 使用 `vstirbu` 的獨立預覽（**強烈推薦**）
- 或安裝 Markdown Preview Enhanced

### 第 3 步：排除環境問題
- 清除快取
- 降級擴充套件
- 檢查 VS Code 設定

### 第 4 步：接受現實
如果所有方法都失敗，接受 VS Code 擴充套件的限制：
- 使用線上平台：https://mermaid.live/
- 或使用 Mermaid CLI 批量生成圖片

---

## 目前狀態檢查

執行以下命令檢查目前環境：

```bash
# 檢查已安裝的 Mermaid 擴充套件
code --list-extensions --show-versions | grep -i mermaid

# 輸出應該包含：
# bierner.markdown-mermaid@1.29.0
# bpruitt-goddard.mermaid-markdown-syntax-highlighting@1.7.4
# vstirbu.vscode-mermaid-preview@2.1.2
```

---

## 最終建議

**立即行動**：
1. 開啟 [`Mermaid_快速測試.md`](Mermaid_快速測試.md)
2. 將游標放在「測試 1」的 Mermaid 程式碼塊中
3. 按 `Ctrl+Shift+P` → "Mermaid: Preview Diagram"
4. 查看是否能在獨立視窗中正常顯示

**如果成功**：
- 設定快捷鍵 `Ctrl+Alt+M` 給 "Mermaid: Preview Diagram"
- 以後都用獨立預覽視窗

**如果失敗**：
- 使用線上平台 https://mermaid.live/（100% 可靠）

---

**建立日期**: 2025-10-30
**適用版本**: VS Code 1.80+, Mermaid Extensions 各版本
**問題症狀**: 圖表閃現後消失，顯示錯誤訊息
