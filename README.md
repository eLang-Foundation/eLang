![Logo](logo/eLang.png)
# eLang
[![Line count](https://img.shields.io/tokei/lines/github/BekhruzSNiyazov/eLang)](https://github.com/BekhruzSNiyazov/eLang)
[![Open issues](https://img.shields.io/github/issues/BekhruzSNiyazov/eLang)](https://github.com/BekhruzSNiyazov/eLang/issues)
[![License](https://img.shields.io/github/license/BekhruzSNiyazov/eLang)](https://github.com/BekhruzSNiyazov/eLang/blob/master/LICENSE)

eLang is a programming language developed by Bekhruz Niyazov (it is still in development).

eLang is written in Python, but it is being translated into C right now.

Right now you are on `master` branch. Here only C code is included. If you want the source code of eLang 0.0.9 in Python switch to [`Python`](https://github.com/BekhruzSNiyazov/eLang/tree/Python) branch.
# Installation
Just grab the latest release for your operating system from _releases_ section, add it to the path (recommended), and you are good to go.

# Quick overview of syntax
eLang's syntax is similar to JavaScript and Python. Here is a sample greet program:
```
function greet(name) {
	print("Hello,", name)
}
greet("eLang")
```
Output:
```
Hello, eLang
```
You can view `test.elang` file for latest eLang features.

# License
eLang is licensed with MIT License.

# Credits
Special thanks to JetBrains who helped in the development of the project by providing free license to their products.

I would also like to thank [@kokke](https://github.com/kokke) for the awesome (regex library)[https://github.com/kokke/tiny-regex-c] they have developed.
