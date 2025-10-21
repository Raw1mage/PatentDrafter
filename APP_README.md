# 专利提案生成器 - Streamlit Web应用

这是一个基于Streamlit的Web应用，用于生成专利提案。用户可以上传DOCX文件，调用Claude AI进行专利提案的生成，并实时查看生成过程的日志。

## 🚀 快速开始

### 方法1: 使用启动脚本（推荐）

```bash
python run_app.py
```

启动脚本会自动：
- 检查并安装依赖
- 创建必要目录
- 验证Claude CLI
- 启动Web应用

### 方法2: 直接启动Streamlit

```bash
# 安装依赖
pip install -r requirements.txt

# 启动应用
streamlit run patent_writer_app.py
```

## 📋 功能特性

- 📄 **文件上传**: 支持DOCX格式技术交底书上传
- 🤖 **AI驱动**: 使用Claude AI生成专业专利提案
- 📊 **实时日志**: 流式显示生成过程的详细日志，支持格式化显示
- ⏯️ **进程控制**: 支持开始、中止、强制清理操作
- 📚 **历史管理**: 查看和管理历史会话记录
- 🔄 **自动刷新**: 运行时自动刷新日志内容
- 🎛️ **显示选项**: 支持原始JSON/格式化显示，行数限制等
- 📊 **状态监控**: 实时显示进程和会话状态

## 🛠️ 系统要求

- Python 3.8+
- Claude CLI工具
- 网络连接（用于Claude API）

## 📁 目录结构

```
PatentWriterLocal/
├── patent_writer_app.py    # Streamlit应用主文件
├── run_app.py              # 启动脚本
├── requirements.txt        # Python依赖
├── data/                   # 输入文件目录
│   └── 输入.docx          # 上传的技术交底书
├── output/                 # 输出文件目录
│   ├── {session_id}.log   # 各会话的日志文件
│   └── temp_*/            # Claude生成的专利文件
└── APP_README.md          # 应用说明文档
```

## 💡 使用方法

### 1. 启动应用

```bash
python run_app.py
```

应用将在 http://localhost:8501 打开

### 2. 上传文件

- 在侧边栏点击"上传DOCX文件"
- 选择您的技术交底书文件
- 系统会自动保存并验证文件

### 3. 生成专利提案

1. **创建新会话**: 点击"生成新Session"按钮
2. **开始生成**: 点击"开始"按钮启动Claude AI
3. **查看日志**: 主界面会实时显示生成过程
4. **控制进程**: 可以随时中止或强制清理进程

### 4. 查看历史

- 在侧边栏的"历史Session"区域选择过往会话
- 支持恢复中断的会话
- 查看完整的生成日志

## 🔧 高级功能

### 日志显示选项

- **原始JSON**: 显示Claude的原始输出格式
- **格式化显示**: 易读的格式化日志内容
- **行数限制**: 控制显示的日志行数
- **自动刷新**: 运行时自动更新日志内容

### 进程管理

- **优雅中止**: 尝试正常终止Claude进程
- **强制清理**: 终止所有相关的Claude进程
- **状态监控**: 实时显示进程状态和活动状态

### Session管理

- **自动检测**: 智能检测活跃的Session
- **会话恢复**: 支持恢复中断的会话
- **历史查看**: 查看所有历史会话记录

## ⚠️ 故障排除

### 常见问题

1. **Claude CLI未找到**
   ```bash
   # 检查Claude是否安装
   claude --version

   # 如果未安装，请参考官方文档安装
   # https://docs.anthropic.com/claude/reference/claude-cli
   ```

2. **进程无法中止**
   - 使用"强制清理所有Claude进程"按钮
   - 或者手动在终端中终止进程

3. **日志不显示**
   - 点击"手动刷新"按钮
   - 检查output目录下是否存在对应的日志文件
   - 尝试切换到原始JSON格式查看

4. **文件上传失败**
   - 确保文件格式为DOCX
   - 检查文件大小是否合理（建议<50MB）
   - 确保data目录有写入权限

### 警告信息

应用可能会显示以下警告，这些通常可以忽略：
- `Thread 'Thread-X': missing ScriptRunContext!` - 这是Streamlit多线程环境中的正常警告
- `missing ScriptRunContext! This warning can be ignored when running in bare mode` - 同上

这些警告不影响应用功能，是Streamlit框架的已知行为。

## 🎯 使用技巧

1. **最佳实践**：
   - 上传完整的、结构清晰的技术交底书
   - 使用具体的Session ID便于后续管理
   - 定期清理旧的日志文件节省空间

2. **性能优化**：
   - 限制显示的日志行数可以提高界面响应速度
   - 在长时间运行时可以使用手动刷新减少资源消耗

3. **调试技巧**：
   - 使用原始JSON格式查看详细的Claude输出
   - 检查状态详情了解进程和会话的准确状态

## 📞 支持

如果遇到问题：

1. 检查本文档的故障排除部分
2. 确认Claude CLI正确安装和配置
3. 查看终端输出的详细错误信息
4. 检查网络连接和API访问权限

## 🔒 隐私说明

- 上传的文件仅在本地处理，不会上传到外部服务器
- 日志文件存储在本地output目录
- Claude API调用遵循Anthropic的隐私政策
- 建议定期清理包含敏感信息的日志文件