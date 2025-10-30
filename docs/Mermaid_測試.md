# Mermaid 圖表測試

## 測試 1: 簡單流程圖

```mermaid
graph TD
    A[開始] --> B[處理]
    B --> C[結束]
```

## 測試 2: A0 頂層功能圖（簡化版）

```mermaid
graph TB
    A1[A1 介面管理] --> A2[A2 文件解析]
    A2 --> A3[A3 專利檢索]
    A3 --> A4[A4 大綱生成]
    A4 --> A5[A5 內容撰寫]
    A5 --> A6[A6 圖表生成]
    A6 --> A7[A7 文件整合]

    A8[A8 流程控制] -.監控.-> A2
    A8 -.監控.-> A3
    A8 -.監控.-> A4
```

## 測試 3: A0 頂層功能圖（完整版 - 無 subgraph）

```mermaid
graph TB
    Input[📄 技術交底書] --> A1

    A1[A1 介面管理<br/>UI Management] --> A2[A2 文件解析<br/>Document Parsing]
    A2 --> A3[A3 專利檢索<br/>Patent Search]
    A3 --> A4[A4 大綱生成<br/>Outline Generation]
    A4 --> A5[A5 內容撰寫<br/>Content Writing]
    A5 --> A6[A6 圖表生成<br/>Diagram Generation]
    A6 --> A7[A7 文件整合<br/>Document Merging]
    A7 --> Output[📑 完整專利文件]

    A8[A8 流程控制<br/>Workflow Control] -.監控.-> A2
    A8 -.監控.-> A3
    A8 -.監控.-> A4
    A8 -.監控.-> A5
    A8 -.監控.-> A6
    A8 -.監控.-> A7

    Control[⚙️ 控制] -.-> A8
    Mechanism[🔧 機制] -.-> A8

    style A1 fill:#FFF9C4,stroke:#F57C00,stroke-width:2px
    style A2 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A3 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A4 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A5 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A6 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A7 fill:#C8E6C9,stroke:#388E3C,stroke-width:2px
    style A8 fill:#FFCCBC,stroke:#D84315,stroke-width:2px
```

## 測試 4: 使用 flowchart 語法（較新）

```mermaid
flowchart TB
    subgraph A0["A0: 專利文件自動生成系統"]
        A1["A1 介面管理"]
        A2["A2 文件解析"]
        A3["A3 專利檢索"]
        A4["A4 大綱生成"]
        A5["A5 內容撰寫"]
        A6["A6 圖表生成"]
        A7["A7 文件整合"]
        A8["A8 流程控制"]
    end

    Input["技術交底書"] --> A1
    A1 --> A2 --> A3 --> A4 --> A5 --> A6 --> A7 --> Output["完整專利文件"]

    A8 -.監控.-> A2
    A8 -.監控.-> A3
    A8 -.監控.-> A4
    A8 -.監控.-> A5
    A8 -.監控.-> A6
    A8 -.監控.-> A7
```

## 診斷說明

如果您看到以下錯誤訊息：
```
No diagram type detected matching given configuration for text
```

可能的原因：
1. **Mermaid 版本過舊**：某些語法在舊版本中不支援
2. **subgraph 語法問題**：部分 Mermaid 渲染器對 subgraph 支援不完整
3. **特殊字符問題**：emoji 或繁體中文可能導致問題
4. **換行符問題**：`<br/>` 在某些版本中可能不支援

## 解決方案

### 方案 1: 更新 Mermaid 擴充套件

```bash
# 更新到最新版本
code --install-extension bierner.markdown-mermaid --force
```

### 方案 2: 簡化圖表語法

移除可能導致問題的元素：
- 移除 emoji 符號
- 移除 `subgraph`
- 簡化 `<br/>` 換行
- 使用 `flowchart` 代替 `graph`

### 方案 3: 使用線上編輯器驗證

訪問 https://mermaid.live/ 測試您的 Mermaid 程式碼

## 測試結果

請按 `Ctrl + Shift + V` (或 `Cmd + Shift + V`) 開啟預覽，查看哪些圖表可以正常顯示。

如果測試 1-3 都無法顯示，可能是擴充套件安裝問題。
如果測試 1 可以但測試 2-4 不行，可能是語法複雜度問題。
