# ð ãã¯ã­

DynASMã®åä½ãå¤æ´ããããã«ãã³ã³ãã¤ã«æã«ããã¤ãã®ãã¯ã­ãå®ç¾©ãããã¨ãã§ãã¾ãã

ç¹å®ã®ãã¯ã­ã®ããã©ã«ãã®å®ç¾©ãé©åã§ãªãå ´åã¯ãèªåã®Cã®ã³ã¼ãããDynASMã®ããããã¤ã³ã¯ã«ã¼ãããåã«ãããã®ãã¯ã­ãåå®ç¾©ããå¿è¦ãããã¾ãã

## DASM_ALIGNED_WRITES

çç¥

## DASM_CHECKS

çç¥

## DASM_EXTERN

```cpp
#define DASM_EXTERN(ctx, addr, idx, type) 0
```

ãã®ã¦ã¼ã¶ã¼å®ç¾©ãã¯ã­ã¯ã`dasm_encode`ãexternã¢ãã¬ã¹ãã¨ã³ã³ã¼ãããå¿è¦ãããã¨ãã«ã`dasm_x86.h`ã«ãã£ã¦ä½¿ç¨ãããexternã¢ãã¬ã¹ãä½¿ç¨ãããå ´åã¯åå®ç¾©ããå¿è¦ãããã¾ãã

`ctx`ãã©ã¡ã¼ã¿ã¯ã`Dst_DECL`ã§å®ç¾©ãããå¤æ°ã¨åãåã§ããã`dasm_encode`ã®ç¬¬1å¼æ°ã«è¨­å®ããã¾ãã

`addr`ãã©ã¡ã¼ã¿ã¯ï¼`unsigned char*`åã§ï¼x86/x64å½ä»¤ã®ä¸é¨ã¨ãã¦æ¸ãè¾¼ã¾ãã`int32_t`ãã£ã¼ã«ãã®ã¢ãã¬ã¹ãæå®ãã¾ãã

`idx`ãã©ã¡ã¼ã¿ã¯`unsigned int`åã§ã`.externnames`éåã¸ã®ã¤ã³ããã¯ã¹ãæå®ããæ¸ãè¾¼ã¾ããç¹å®ã®externã¢ãã¬ã¹ãç¹å®ãã¦ãã¾ãã

ä¾ãã°ãexternåãåçã«æ¤ç´¢å¯è½ãªã·ã³ãã«ã§ããã°ã`DASM_EXTERN`ã¯æ¬¡ã®ããã«å®ç¾©ãããããããã¾ããã

```cpp
#define DASM_EXTERN(ctx, addr, idx, type) (\
    (type) ? (int)((unsigned char*)dlsym(RTLD_DEFAULT, externs[idx]) - (addr) - 4) : (int)dlsym(RTLD_DEFAULT, externs[idx])\
)
```

## DASM_FDEF

```cpp
#define DASM_FDEF extern

DASM_FDEF void dasm_init(Dst_DECL, int maxsection);
// â
extern void dasm_init(Dst_DECL, int maxsection);
```

ãã®ã¦ã¼ã¶ã¼å®ç¾©ãã¯ã­ã¯ããã¹ã¦ã®`dasm_`é¢æ°ã®ã¢ã¯ã»ãµãå¶å¾¡ããããã«ä½¿ç¨ããã¾ãã

## DASM_M_FREE

çç¥

## DASM_M_GROW

```cpp
#define DASM_M_GROW(ctx, t, p, sz, need) \
  do { \
    size_t _sz = (sz), _need = (need); \
    if (_sz < _need) { \
      if (_sz < 16) _sz = 16; \
      while (_sz < _need) _sz += _sz; \
      (p) = (t *)realloc((p), _sz); \
      if ((p) == NULL) exit(1); \
      (sz) = _sz; \
    } \
  } while(0)
```

ãã®ã¦ã¼ã¶ã¼å®ç¾©ãã¯ã­ã¯ã`dasm_x86.h`ã«ãã£ã¦ãã¡ã¢ãªã®å²ãå½ã¦ãåå²ãå½ã¦ãå¿è¦ãªã¨ããã¤ã¾ã`dasm_init`ãå¸¸ã«å¿è¦ã§ããä»ã®æ§ããª`dasm_`é¢æ°ãæãå¿è¦ãªã¨ãã«ãä½¿ç¨ããã¾ãã

ãã®ãã¯ã­ã¯ãããã©ã«ãã®Cã®`realloc/free`ã«ããã¡ã¢ãªå²ãå½ã¦ã¡ã«ããºã ãé©åã§ãªãã¨ãã«ã`DASM_M_FREE`ã¨å±ã«åå®ç¾©ãããã¹ãã§ãã

`ctx`ãã©ã¡ã¼ã¿ã¯ã`Dst_DECL`ã§å®ç¾©ãããå¤æ°ã¨åãåã§ãããå²ãå½ã¦ãè¡ã`dasm_`é¢æ°ã®ç¬¬1å¼æ°ã«è¨­å®ããã¾ãã

## Dst_DECL

```cpp
#define Dst_DECL dasm_State **Dst

DASM_FDEF void dasm_init(Dst_DECL, int maxsection);
// â
DASM_FDEF void dasm_init(dasm_State **Dst, int maxsection); // Dst_DECL == ã·ã°ããã£
```

ãã®ã¦ã¼ã¶ã¼å®ç¾©ãã¯ã­ã¯ããã¹ã¦ã®`dasm_`é¢æ°ã®ã·ã°ããã£ã«ã¤ãã¦ãç¬¬ä¸å¼æ°ã®åã¨ååãå®ç¾©ããããã®ãã¯ã­ã§ãã

ä¸è¨ã®ãã©ã¡ã¼ã¿ã®åå`Dst`ã¯ã`Dst`ã®ã¾ã¾ã«ãã¦ããããããã§ä½¿ããã¦ããååã«åããã¦`Dst`ãåå®ç¾©ããããªãã­ã»ããµãã¯ã­ãå¿è¦ã§ãã

ä¸è¨ã®ãã©ã¡ã¼ã¿ã®å`dasm_State`ã¯ã`Dst_REF`ã«æ¸¡ãããªãã°ãªãã§ãå¤§ä¸å¤«ã§ãã

## Dst_REF

```cpp
#define Dst_REF (*Dst)
```

ãã®ã¦ã¼ã¶ã¼å®ç¾©ãã¯ã­ã¯ã`dasm_x86.h`ã«ãã£ã¦ãå¤æ°`Dst`ãã`dasm_State*`åã®ã¤ã³ã¿ã¼ãã§ã¼ã¹å¤ãåãåºãããæã«ä½¿ç¨ããã¾ãã

`Dst_DECL`ãåå®ç¾©ããå ´åã¯ããã®ãã¯ã­ãåå®ç¾©ããå¿è¦ãããã¾ãã