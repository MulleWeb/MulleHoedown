## 0.5.0







feature: add Objective-C dependency declarations for loader

* add public MulleObjCDeps category exposing +dependencies so dependent libraries (and the MulleObjCLoader) can declare and query load-time dependencies
* register MulleHoedown's ObjC dependency pairs (NSData, NSString) via a generated objc-deps.inc so runtime initialization ordering is correct
