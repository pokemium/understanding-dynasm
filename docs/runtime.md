# ランタイム

**dasm_proto.h**

[`dasm_proto.h`](../dasm_proto.h)には、様々なマクロのデフォルト定義と、様々な関数の型シグネチャが含まれており、これらをまとめてDynASMランタイムライブラリを構成しています。

DynASMを使ってマシンコードを生成したいすべてのC/C++ファイルでは、このヘッダファイルをインクルードする必要があります。

**dasm_$ARCH.h**

`dasm_$ARCH.h`には、アーキテクチャ用のDynASMランタイムライブラリの様々な関数の実装が含まれています。
