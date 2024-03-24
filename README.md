# VC版本的ChatGPT聊天工具

这是一个利用MFC通过HTTP访问OpenAI的VC版本ChatGPT聊天工具，演示了VC++访问openai的全部细节。它允许用户通过选择不同的ChatGPT版本（如ChatGPT3.5或ChatGPT4）来使用，为那些不希望支付ChatGPT4月费用的用户提供了一种更灵活的支付方式——根据使用流量来支付。

## 功能简介

- **版本灵活性**：支持切换至ChatGPT3.5或ChatGPT4版本。
- **成本效益**：无需支付固定月费用，按实际使用流量付费。


## 开始之前

在使用本工具之前，您需要拥有一个OpenAI账号，并将您的OpenAI API密钥保存在计算机的系统变量`hyt123`中。

### 设置OpenAI API密钥

将您的OpenAI API密钥添加到系统变量中，可以通过下列步骤实现：

1. 在计算机的环境变量中创建一个名为`hyt123`的变量。
2. 将您的OpenAI API密钥作为该变量的值。

程序将通过以下代码读取并设置API密钥：

```c
DWORD count = ::GetEnvironmentVariableW(L"hyt123", x, 1024 * 10);
```

## 使用指南

1. **准备工作**：确保您已设置系统环境变量`hyt123`。
2. **打开项目**：使用Visual Studio 2022打开此工程。
3. **编译运行**：编译工程，然后运行程序。
