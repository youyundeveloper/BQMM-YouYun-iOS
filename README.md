# BQMM-YouYun-iOS

此SDK包含 游云IM SDK和表情云SDK。

集成游云IM SDK 请参考[游云IM SDK集成指南](https://github.com/youyundeveloper/wchatsdk_ios)，集成表情云SDK请参考[表情云SDK使用指南](http://open.biaoqingmm.com/doc/sdk/index.html)。

SDK默认不开启表情云服务，如果要开启表情云服务，请在游云官网勾选表情云服务后，集成时调用如下方法：

```objective-c
[WChatSDK startEmotionFunction];
```



