# Markdown 批量匯出為 HTML (PowerShell)
# 使用 Markdown Preview Enhanced
# 目標目錄：docs/html/

Write-Host "🚀 PatentWriterAgent - Markdown 批量匯出為 HTML" -ForegroundColor Green
Write-Host "==========================================="
Write-Host ""

# 設定來源和目標目錄
$sourceDir = "docs"
$outputDir = "docs\html"

# 確保輸出目錄存在
New-Item -ItemType Directory -Force -Path $outputDir | Out-Null

# 需要匯出的文件清單（IDEF0 架構文件）
$files = @(
    "README.md",
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

# 計數器
$total = $files.Count
$processed = 0
$success = 0
$skipped = 0

Write-Host "📋 準備匯出 $total 個文件"
Write-Host ""
Write-Host "📌 操作說明：" -ForegroundColor Cyan
Write-Host "   1. 腳本會依次開啟每個 Markdown 文件"
Write-Host "   2. 請在 VS Code 中："
Write-Host "      - 按 Ctrl+Shift+V 開啟預覽"
Write-Host "      - 在預覽視窗右鍵 → HTML → HTML (offline)"
Write-Host "   3. 完成後按 Enter 繼續下一個文件"
Write-Host "   4. 如要跳過，直接按 Enter"
Write-Host ""
Read-Host "按 Enter 開始"
Write-Host ""

# 遍歷文件清單
foreach ($file in $files) {
    $processed++
    $mdPath = Join-Path $sourceDir $file

    if (-not (Test-Path $mdPath)) {
        Write-Host "[$processed/$total] ⚠️  文件不存在: $file" -ForegroundColor Yellow
        $skipped++
        continue
    }

    $filename = [System.IO.Path]::GetFileNameWithoutExtension($file)
    Write-Host "[$processed/$total] 📄 處理: $file" -ForegroundColor Cyan

    # 開啟 VS Code
    code $mdPath

    # 提示使用者
    Write-Host "   ⏸️  請在 VS Code 中：" -ForegroundColor Yellow
    Write-Host "      1. 按 Ctrl+Shift+V 開啟預覽"
    Write-Host "      2. 右鍵 → HTML → HTML (offline)"
    Write-Host "      3. 完成後按 Enter 繼續，或直接 Enter 跳過"
    Write-Host ""
    Read-Host "   完成後按 Enter"

    # 檢查是否生成了 HTML 文件
    $htmlPath = Join-Path $sourceDir "$filename.html"
    $targetPath = Join-Path $outputDir "$filename.html"

    if (Test-Path $htmlPath) {
        # 移動到目標目錄
        Move-Item -Path $htmlPath -Destination $targetPath -Force
        Write-Host "   ✅ 已匯出並移動: $filename.html" -ForegroundColor Green
        $success++
    } else {
        Write-Host "   ⏭️  跳過（未找到匯出文件）" -ForegroundColor Yellow
        $skipped++
    }

    Write-Host ""
}

# 顯示統計資訊
Write-Host "==========================================="
Write-Host "📊 匯出完成！" -ForegroundColor Green
Write-Host ""
Write-Host "統計資訊："
Write-Host "   總計: $total 個文件"
Write-Host "   成功: $success 個" -ForegroundColor Green
Write-Host "   跳過: $skipped 個" -ForegroundColor Yellow
Write-Host ""

if ($success -gt 0) {
    Write-Host "✅ HTML 文件位置: $outputDir\" -ForegroundColor Green
    Write-Host ""
    Write-Host "已匯出的文件："

    Get-ChildItem -Path $outputDir -Filter *.html | ForEach-Object {
        $size = "{0:N2} KB" -f ($_.Length / 1KB)
        Write-Host "   - $($_.Name) ($size)" -ForegroundColor Cyan
    }
}

Write-Host ""
Write-Host "==========================================="
Write-Host "💡 提示：" -ForegroundColor Cyan
Write-Host "   - 查看所有 HTML: Get-ChildItem $outputDir"
Write-Host "   - 在瀏覽器開啟: Start-Process '$outputDir\A0_system_idef0.html'"
Write-Host "==========================================="
