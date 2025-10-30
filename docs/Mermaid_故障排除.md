# Mermaid 圖表故障排除指南

## 🚨 常見錯誤訊息

### 錯誤 1: "No diagram type detected matching given configuration for text"

**症狀**：
- Mermaid 圖表無法渲染
- 顯示錯誤訊息而非圖表
- 預覽視窗中圖表區域為空白

**可能原因**：

1. **語法版本不相容**
   - 使用了較新的 `subgraph` 語法，但擴充套件版本較舊
   - 某些複雜的巢狀結構不被支援

2. **特殊字符問題**
   - Emoji 符號在某些版本中可能導致解析失敗
   - 繁體中文字符編碼問題
   - 換行符 `<br/>` 在舊版本中不支援

3. **語法錯誤**
   - 缺少必要的關鍵字
   - 引號或括號不匹配
   - 圖表類型聲明錯誤

---

## ✅ 解決方案

### 方案 1: 使用 `flowchart` 替代 `graph`

**問題語法**（可能導致錯誤）：
````markdown
```mermaid
flowchart TB
    subgraph A0["系統"]
        A1["模組1"]
        A2["模組2"]
    end
```
````

**修復後語法**（更兼容）：
````markdown
```mermaid
flowchart TB
    A1["模組1"] --> A2["模組2"]
```
````

**差異說明**：
- `flowchart` 是較新的語法，向後兼容性更好
- 移除 `subgraph` 可以避免巢狀結構問題
- 保持圖表扁平化結構

---

### 方案 2: 簡化特殊字符

**問題語法**：
````markdown
```mermaid
flowchart TD
    A["📄 文件<br/>多行標題<br/>更多內容"]
```
````

**修復後語法**：
````markdown
```mermaid
flowchart TD
    A["文件 - 多行標題"]
```
````

**建議**：
- 減少 `<br/>` 的使用
- 移除 emoji（或移到註解中）
- 使用簡短的節點標籤

---

### 方案 3: 更新擴充套件

```bash
# 強制更新到最新版本
code --install-extension bierner.markdown-mermaid --force

# 重新載入 VS Code
# Ctrl+Shift+P → "Reload Window"
```

---

### 方案 4: 檢查語法正確性

使用線上編輯器驗證：
1. 訪問 https://mermaid.live/
2. 複製您的 Mermaid 程式碼
3. 即時查看渲染結果
4. 修正錯誤後再貼回 VS Code

---

## 🔧 本專案的修復記錄

### 已修復的檔案

#### 1. `docs/A0_system_idef0.md`

**原始問題**：
- A0 頂層功能圖無法渲染
- 使用 `graph TB` + `subgraph` 組合
- 錯誤訊息：No diagram type detected

**修復方式**：
```diff
- graph TB
-     subgraph A0["A0: 專利文件自動生成系統"]
-         A1["A1<br/>介面管理<br/>UI Management"]
-         ...
-     end
+ flowchart TB
+     A1["A1 介面管理<br/>UI Management"] --> A2["A2 文件解析<br/>Document Parsing"]
+     ...
```

**效果**：
- ✅ 圖表成功渲染
- ✅ 保留所有節點和連線關係
- ✅ 樣式（顏色、邊框）正常顯示

---

## 📋 Mermaid 語法最佳實踐

### ✅ 推薦寫法

```mermaid
flowchart TB
    %% 使用簡潔的節點標籤
    A1[模組1] --> A2[模組2]
    A2 --> A3[模組3]

    %% 虛線表示監控或控制關係
    Control[控制] -.控制.-> A1

    %% 樣式定義
    style A1 fill:#FFE5B4,stroke:#333,stroke-width:2px
```

### ❌ 避免的寫法

```mermaid
flowchart TB
    %% 避免過度巢狀的 subgraph
    subgraph Layer1
        subgraph Layer2
            subgraph Layer3
                A[節點]
            end
        end
    end

    %% 避免過長的標籤
    A["📄 這是一個<br/>非常非常長的<br/>多行標籤<br/>可能導致問題"]
```

---

## 🎯 快速診斷流程

### 步驟 1: 測試基本圖表

開啟 [`docs/Mermaid_測試.md`](Mermaid_測試.md) 並預覽（`Ctrl+Shift+V`）：

- ✅ **測試 1 成功**：基本功能正常
- ❌ **測試 1 失敗**：擴充套件未安裝或損壞 → 重新安裝

### 步驟 2: 測試進階功能

- ✅ **測試 2 成功**：支援虛線和樣式
- ❌ **測試 2 失敗**：版本過舊 → 更新擴充套件

### 步驟 3: 測試複雜結構

- ✅ **測試 3-4 成功**：支援所有語法
- ❌ **測試 3-4 失敗**：語法問題 → 簡化圖表結構

---

## 🛠️ 維護建議

### 定期更新

```bash
# 每月更新一次 Mermaid 擴充套件
code --install-extension bierner.markdown-mermaid --force
```

### 備份策略

1. **保留簡化版本**：為每個複雜圖表保留一個簡化版本
2. **記錄問題**：在註解中標註可能的兼容性問題
3. **測試環境**：在線上編輯器中驗證新語法

### 版本控制

```markdown
<!-- Mermaid 版本說明 -->
<!-- 此圖表需要 Mermaid v9.0+ -->
<!-- 如遇渲染問題，請參考 docs/Mermaid_故障排除.md -->
```

---

## 📚 參考資源

### 官方文件
- [Mermaid 官方文件](https://mermaid.js.org/)
- [Mermaid 語法參考](https://mermaid.js.org/intro/syntax-reference.html)
- [Flowchart 語法](https://mermaid.js.org/syntax/flowchart.html)

### 線上工具
- [Mermaid Live Editor](https://mermaid.live/) - 即時預覽和驗證
- [Mermaid CLI](https://github.com/mermaid-js/mermaid-cli) - 命令列工具

### VS Code 擴充套件
- [Markdown Preview Mermaid Support](https://marketplace.visualstudio.com/items?itemName=bierner.markdown-mermaid)
- [Mermaid Preview](https://marketplace.visualstudio.com/items?itemName=vstirbu.vscode-mermaid-preview)

---

## 🎓 學習路徑

### 初學者
1. 從簡單的流程圖開始
2. 逐步增加節點和連線
3. 學習基本樣式設定

### 進階使用者
1. 掌握所有圖表類型（時序圖、狀態圖等）
2. 學習樣式自訂和主題
3. 整合到 CI/CD 流程

### 專家級
1. 開發自訂插件
2. 貢獻到 Mermaid 開源專案
3. 創建企業級圖表標準

---

## 💡 小技巧

### Tip 1: 使用註解

```mermaid
flowchart TB
    %% 這是註解，不會顯示在圖表中
    %% 可用於說明圖表結構和邏輯
    A[開始] --> B[處理]
```

### Tip 2: 分段建構

先建立基本結構，確認可以渲染後再添加細節：

```mermaid
%% 第一步：基本流程
flowchart TB
    A --> B --> C

%% 第二步：添加標籤
%% A[開始] --> B[處理] --> C[結束]

%% 第三步：添加樣式
%% style A fill:#90EE90
```

### Tip 3: 使用變數

對於重複的樣式定義，可以使用 classDef：

```mermaid
flowchart TB
    A[模組A]:::processClass
    B[模組B]:::processClass

    classDef processClass fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
```

---

## 🔴 已知問題：VS Code 擴充套件兼容性

### 問題描述

**症狀**：
- Mermaid 圖表在 VS Code 預覽中**時好時壞**，間歇性無法渲染
- 相同的 Mermaid 程式碼在官方平台（https://mermaid.live/ 或 https://www.mermaidchart.com/）上**渲染正常**
- 錯誤訊息："No diagram type detected matching given configuration for text"

**根本原因**：
- VS Code 擴充套件 `bierner.markdown-mermaid@1.29.0` 對某些 `subgraph` 結構的支援不穩定
- 即使使用正確的 `flowchart` 語法，複雜的 `subgraph` 巢狀仍可能觸發渲染失敗
- 這是擴充套件的已知限制，而非語法錯誤

**驗證方法**：
```bash
# 檢查專案中的 subgraph 使用情況
bash check_mermaid.sh

# 輸出示例：
# - flowchart 語法: 57 個 (推薦)
# - 使用 subgraph: 20 個 (可能有問題)
```

---

### 解決方案選項

#### 選項 1: 使用官方線上平台（推薦）

**優點**：
- 100% 語法支援，渲染穩定
- 無需安裝額外軟體
- 支援匯出 PNG/SVG

**操作步驟**：
1. 訪問 https://mermaid.live/ 或 https://www.mermaidchart.com/
2. 複製 VS Code 中的 Mermaid 程式碼
3. 貼上到線上編輯器
4. 即時預覽和匯出

**適用場景**：
- 需要確認圖表最終渲染效果
- 準備文件交付或簡報
- 調試複雜的 subgraph 結構

#### 選項 2: 簡化 subgraph 結構

**修改前**：
````markdown
```mermaid
flowchart TB
    subgraph System["系統"]
        subgraph Module1["模組1"]
            A[組件A]
            B[組件B]
        end
        subgraph Module2["模組2"]
            C[組件C]
        end
    end
```
````

**修改後**（扁平化）：
````markdown
```mermaid
flowchart TB
    A[組件A] --> B[組件B]
    B --> C[組件C]

    %% 使用註解標記模組邊界
    %% Module1: A, B
    %% Module2: C
```
````

**權衡考量**：
- ✅ VS Code 預覽兼容性提升
- ❌ 失去視覺化的模組分組
- ❌ 需要手動維護註解

#### 選項 3: 使用 Mermaid CLI（進階）

**安裝**：
```bash
npm install -g @mermaid-js/mermaid-cli
```

**使用**：
```bash
# 將 .md 文件中的 Mermaid 圖表轉為 PNG
mmdc -i docs/A0_system_idef0.md -o output/diagrams.png

# 批量處理
find docs -name "*.md" -exec mmdc -i {} -o {}.png \;
```

**優點**：
- 本地渲染，無需網路
- 可整合到 CI/CD 流程
- 支援批量處理

**缺點**：
- 需要安裝 Node.js 環境
- 學習曲線較高

#### 選項 4: 嘗試替代擴充套件

**可選擴充套件**：
1. **Mermaid Preview** (`vstirbu.vscode-mermaid-preview`)
   ```bash
   # 使用快捷鍵開啟獨立預覽視窗
   # Ctrl+Shift+P → "Mermaid: Preview Diagram"
   ```
   - 優點：獨立渲染引擎，可能更穩定
   - 缺點：需要額外的預覽步驟

2. **Markdown Preview Enhanced** (`shd101wyy.markdown-preview-enhanced`)
   - 優點：功能強大，支援多種圖表
   - 缺點：較重量級，可能影響效能

---

### 本專案的策略建議

**開發階段**：
- 使用 VS Code 預覽進行快速迭代
- 遇到渲染問題時，立即切換到 https://mermaid.live/ 驗證

**文件交付階段**：
- 所有圖表在官方平台上最終確認
- 必要時使用 Mermaid CLI 批量生成 PNG/SVG
- 在專案 README 中附上官方平台的分享連結

**長期維護**：
- 定期檢查擴充套件更新（每季度）
- 記錄新發現的兼容性問題
- 保持 `check_mermaid.sh` 腳本更新

---

## ✉️ 獲取幫助

如果問題仍未解決：

1. **檢查本文件** 的所有解決方案，特別是「已知問題」章節
2. **查看測試檔案** [`docs/Mermaid_測試.md`](Mermaid_測試.md)
3. **訪問線上編輯器** 驗證語法：https://mermaid.live/
4. **查閱官方文件** 確認語法正確性：https://mermaid.js.org/
5. **檢查擴充套件問題**：https://github.com/mjbvz/vscode-markdown-mermaid/issues
6. **提交 Issue** 到 Mermaid GitHub 專案（如確認是 Mermaid.js 本身的問題）

---

**最後更新**: 2025-10-30
**適用版本**: Mermaid v9.0+ / VS Code Mermaid Extensions v1.29.0+
**已知限制**: VS Code 擴充套件對複雜 subgraph 結構支援不穩定
