Flat profile:
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ps/call  ps/call  name    
 38.36     13.85    13.85                             volume_get (volume_baseline.c:8 @ 4698)
 20.74     21.33     7.49 8112019542   922.87   922.87  volume_get (volume_baseline.c:7 @ 4679)
 19.78     28.47     7.14                             conv_forward (layers_baseline.c:98 @ 374c)
  4.56     30.12     1.65                             volume_get (volume_baseline.c:9 @ 46cb)
  4.20     31.64     1.52                             conv_forward (layers_baseline.c:97 @ 378e)
  3.83     33.02     1.38                             conv_forward (layers_baseline.c:97 @ 3743)
  2.27     33.84     0.82                             conv_forward (layers_baseline.c:96 @ 3720)
  0.89     34.16     0.32                             conv_forward (layers_baseline.c:94 @ 379d)
  0.86     34.47     0.31                             conv_forward (layers_baseline.c:95 @ 3715)
  0.69     34.72     0.25                             volume_set (volume_baseline.c:12 @ 46f1)
  0.61     34.94     0.22                             softmax_forward (layers_baseline.c:354 @ 4659)
  0.53     35.13     0.19                             conv_forward (layers_baseline.c:104 @ 37c2)
  0.25     35.22     0.09                             conv_forward (layers_baseline.c:94 @ 3709)
  0.22     35.30     0.08                             relu_forward (layers_baseline.c:165 @ 3b74)
  0.19     35.37     0.07 126793634   552.55   552.55  volume_set (volume_baseline.c:11 @ 46cd)
  0.19     35.44     0.07                             conv_forward (layers_baseline.c:93 @ 36fe)
  0.17     35.50     0.06                             volume_set (volume_baseline.c:13 @ 4729)
  0.14     35.55     0.05                             pool_forward (layers_baseline.c:220 @ 3e27)
  0.14     35.60     0.05                             pool_forward (layers_baseline.c:218 @ 3e89)
  0.12     35.65     0.05                             relu_forward (layers_baseline.c:166 @ 3be0)
  0.11     35.69     0.04                             conv_forward (layers_baseline.c:92 @ 37af)
  0.11     35.73     0.04                             pool_forward (layers_baseline.c:221 @ 3e32)
  0.08     35.76     0.03                             load_batch (benchmark.c:91 @ 1962)
  0.08     35.79     0.03                             pool_forward (layers_baseline.c:219 @ 3e1c)
  0.08     35.82     0.03                             relu_forward (layers_baseline.c:164 @ 3c0e)
  0.06     35.84     0.02                             load_batch (benchmark.c:90 @ 19d1)
  0.06     35.86     0.02                             make_volume (volume_baseline.c:25 @ 47b8)
  0.06     35.88     0.02                             make_volume (volume_baseline.c:26 @ 47c1)
  0.06     35.90     0.02                             pool_forward (layers_baseline.c:222 @ 3e55)
  0.04     35.91     0.02                             conv_forward (layers_baseline.c:92 @ 36f2)
  0.04     35.93     0.02                             pool_forward (layers_baseline.c:224 @ 3e7f)
  0.04     35.94     0.02                             relu_forward (layers_baseline.c:164 @ 3b68)
  0.03     35.95     0.01                             fc_forward (layers_baseline.c:272 @ 40e2)
  0.03     35.96     0.01                             pool_forward (layers_baseline.c:214 @ 3dee)
  0.03     35.97     0.01                             pool_forward (layers_baseline.c:217 @ 3e07)
  0.03     35.98     0.01                             pool_forward (layers_baseline.c:223 @ 3e73)
  0.03     35.99     0.01                             pool_forward (layers_baseline.c:231 @ 3ead)
  0.03     36.00     0.01                             pool_forward (layers_baseline.c:214 @ 3ec8)
  0.01     36.01     0.01                             conv_forward (layers_baseline.c:91 @ 36e9)
  0.01     36.01     0.01                             pool_forward (layers_baseline.c:217 @ 3e98)
  0.01     36.02     0.01                             softmax_forward (layers_baseline.c:334 @ 452e)
  0.01     36.02     0.01                             softmax_forward (layers_baseline.c:335 @ 453f)
  0.00     36.02     0.00    10094     0.00     0.00  free_volume (volume_baseline.c:48 @ 4923)
  0.00     36.02     0.00    10094     0.00     0.00  make_volume (volume_baseline.c:15 @ 472c)
  0.00     36.02     0.00     3600     0.00     0.00  conv_forward (layers_baseline.c:76 @ 3622)
  0.00     36.02     0.00     3600     0.00     0.00  pool_forward (layers_baseline.c:204 @ 3d51)
  0.00     36.02     0.00     3600     0.00     0.00  relu_forward (layers_baseline.c:160 @ 3b20)
  0.00     36.02     0.00     1200     0.00     0.00  copy_volume (volume_baseline.c:34 @ 4803)
  0.00     36.02     0.00     1200     0.00     0.00  fc_forward (layers_baseline.c:264 @ 405e)
  0.00     36.02     0.00     1200     0.00     0.00  net_forward (network_baseline.c:116 @ 314c)
  0.00     36.02     0.00     1200     0.00     0.00  softmax_forward (layers_baseline.c:326 @ 43e9)
  0.00     36.02     0.00        3     0.00     0.00  conv_load (layers_baseline.c:112 @ 385f)
  0.00     36.02     0.00        3     0.00     0.00  make_conv_layer (layers_baseline.c:10 @ 348b)
  0.00     36.02     0.00        3     0.00     0.00  make_pool_layer (layers_baseline.c:173 @ 3c59)
  0.00     36.02     0.00        3     0.00     0.00  make_relu_layer (layers_baseline.c:144 @ 3aab)
  0.00     36.02     0.00        1     0.00     0.00  do_benchmark (benchmark.c:206 @ 227f)
  0.00     36.02     0.00        1     0.00     0.00  fc_load (layers_baseline.c:280 @ 41b2)
  0.00     36.02     0.00        1     0.00     0.00  free_batch (network_baseline.c:106 @ 30b1)
  0.00     36.02     0.00        1     0.00     0.00  free_network (network_baseline.c:47 @ 2ce7)
  0.00     36.02     0.00        1     0.00     0.00  get_accuracy (benchmark.c:104 @ 1a50)
  0.00     36.02     0.00        1     0.00     0.00  load_batch (benchmark.c:71 @ 17d0)
  0.00     36.02     0.00        1     0.00     0.00  load_cnn_snapshot (benchmark.c:30 @ 14e0)
  0.00     36.02     0.00        1     0.00     0.00  make_batch (network_baseline.c:95 @ 2fc2)
  0.00     36.02     0.00        1     0.00     0.00  make_fc_layer (layers_baseline.c:238 @ 3f28)
  0.00     36.02     0.00        1     0.00     0.00  make_network (network_baseline.c:7 @ 278c)
  0.00     36.02     0.00        1     0.00     0.00  make_softmax_layer (layers_baseline.c:301 @ 4346)
  0.00     36.02     0.00        1     0.00     0.00  net_classify (network_baseline.c:130 @ 3385)
  0.00     36.02     0.00        1     0.00     0.00  run_classification (benchmark.c:136 @ 1c97)


			Call graph


granularity: each sample hit covers 2 byte(s) for 0.03% of 36.02 seconds

index % time    self  children    called     name
                0.00    0.00 3686400/8112019542     copy_volume (volume_baseline.c:42 @ 48c9) [40]
                0.03    0.00 27340800/8112019542     pool_forward (layers_baseline.c:222 @ 3e55) [22]
                0.03    0.00 33581142/8112019542     relu_forward (layers_baseline.c:165 @ 3b74) [13]
                7.43    0.00 8047411200/8112019542     conv_forward (layers_baseline.c:98 @ 374c) [1]
[3]     20.8    7.49    0.00 8112019542         volume_get (volume_baseline.c:7 @ 4679) [3]
-----------------------------------------------
                0.00    0.00      56/126793634     conv_load (layers_baseline.c:138 @ 3a54) [46]
                0.00    0.00   19200/126793634     conv_load (layers_baseline.c:129 @ 39c9) [45]
                0.00    0.00 3686400/126793634     copy_volume (volume_baseline.c:42 @ 48c9) [40]
                0.00    0.00 6835200/126793634     pool_forward (layers_baseline.c:231 @ 3ead) [34]
                0.02    0.00 27340800/126793634     conv_forward (layers_baseline.c:105 @ 37ec) [30]
                0.02    0.00 27340800/126793634     relu_forward (layers_baseline.c:166 @ 3be0) [17]
                0.02    0.00 30720000/126793634     load_batch (benchmark.c:91 @ 1962) [21]
                0.02    0.00 30851178/126793634     make_volume (volume_baseline.c:26 @ 47c1) [25]
[15]     0.2    0.07    0.00 126793634         volume_set (volume_baseline.c:11 @ 46cd) [15]
-----------------------------------------------
                0.00    0.00       1/10094       free_network (network_baseline.c:56 @ 2d77) [226]
                0.00    0.00       1/10094       free_network (network_baseline.c:62 @ 2dde) [231]
                0.00    0.00       1/10094       free_network (network_baseline.c:68 @ 2e4e) [236]
                0.00    0.00       1/10094       free_network (network_baseline.c:75 @ 2ec0) [241]
                0.00    0.00      10/10094       free_network (network_baseline.c:72 @ 2e6e) [238]
                0.00    0.00      12/10094       free_network (network_baseline.c:49 @ 2d06) [220]
                0.00    0.00      12/10094       free_batch (network_baseline.c:109 @ 30dc) [213]
                0.00    0.00      16/10094       free_network (network_baseline.c:52 @ 2d50) [224]
                0.00    0.00      20/10094       free_network (network_baseline.c:59 @ 2d94) [228]
                0.00    0.00      20/10094       free_network (network_baseline.c:65 @ 2dfb) [233]
                0.00    0.00   10000/10094       run_classification (benchmark.c:187 @ 2180) [542]
[47]     0.0    0.00    0.00   10094         free_volume (volume_baseline.c:48 @ 4923) [47]
-----------------------------------------------
                0.00    0.00       1/10094       make_network (network_baseline.c:10 @ 27ac) [390]
                0.00    0.00       1/10094       make_network (network_baseline.c:13 @ 2802) [392]
                0.00    0.00       1/10094       make_network (network_baseline.c:16 @ 2869) [394]
                0.00    0.00       1/10094       make_network (network_baseline.c:19 @ 28d9) [396]
                0.00    0.00       1/10094       make_network (network_baseline.c:22 @ 2959) [398]
                0.00    0.00       1/10094       make_network (network_baseline.c:25 @ 29c3) [400]
                0.00    0.00       1/10094       make_network (network_baseline.c:28 @ 2a3f) [402]
                0.00    0.00       1/10094       make_network (network_baseline.c:31 @ 2acb) [404]
                0.00    0.00       1/10094       make_network (network_baseline.c:34 @ 2b3e) [406]
                0.00    0.00       1/10094       make_network (network_baseline.c:37 @ 2bba) [408]
                0.00    0.00       1/10094       make_network (network_baseline.c:40 @ 2c30) [410]
                0.00    0.00       1/10094       make_network (network_baseline.c:43 @ 2ca2) [412]
                0.00    0.00       1/10094       make_fc_layer (layers_baseline.c:256 @ 4029) [386]
                0.00    0.00       3/10094       make_conv_layer (layers_baseline.c:35 @ 35ec) [370]
                0.00    0.00      10/10094       make_fc_layer (layers_baseline.c:252 @ 3fd9) [383]
                0.00    0.00      12/10094       make_batch (network_baseline.c:100 @ 3029) [341]
                0.00    0.00      56/10094       make_conv_layer (layers_baseline.c:30 @ 359a) [367]
                0.00    0.00   10000/10094       load_batch (benchmark.c:82 @ 18ae) [283]
[48]     0.0    0.00    0.00   10094         make_volume (volume_baseline.c:15 @ 472c) [48]
-----------------------------------------------
                0.00    0.00    1200/3600        net_forward (network_baseline.c:117 @ 316c) [469]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:120 @ 31f5) [472]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:123 @ 3288) [475]
[49]     0.0    0.00    0.00    3600         conv_forward (layers_baseline.c:76 @ 3622) [49]
-----------------------------------------------
                0.00    0.00    1200/3600        net_forward (network_baseline.c:119 @ 31c6) [471]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:122 @ 3256) [474]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:125 @ 32ec) [477]
[50]     0.0    0.00    0.00    3600         pool_forward (layers_baseline.c:204 @ 3d51) [50]
-----------------------------------------------
                0.00    0.00    1200/3600        net_forward (network_baseline.c:118 @ 3197) [470]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:121 @ 3224) [473]
                0.00    0.00    1200/3600        net_forward (network_baseline.c:124 @ 32ba) [476]
[51]     0.0    0.00    0.00    3600         relu_forward (layers_baseline.c:160 @ 3b20) [51]
-----------------------------------------------
                0.00    0.00    1200/1200        net_classify (network_baseline.c:134 @ 33c7) [461]
[52]     0.0    0.00    0.00    1200         copy_volume (volume_baseline.c:34 @ 4803) [52]
-----------------------------------------------
                0.00    0.00    1200/1200        net_forward (network_baseline.c:127 @ 3350) [479]
[53]     0.0    0.00    0.00    1200         fc_forward (layers_baseline.c:264 @ 405e) [53]
-----------------------------------------------
                0.00    0.00    1200/1200        net_classify (network_baseline.c:135 @ 33f3) [462]
[54]     0.0    0.00    0.00    1200         net_forward (network_baseline.c:116 @ 314c) [54]
-----------------------------------------------
                0.00    0.00    1200/1200        net_forward (network_baseline.c:127 @ 3350) [479]
[55]     0.0    0.00    0.00    1200         softmax_forward (layers_baseline.c:326 @ 43e9) [55]
-----------------------------------------------
                0.00    0.00       1/3           load_cnn_snapshot (benchmark.c:32 @ 1500) [296]
                0.00    0.00       1/3           load_cnn_snapshot (benchmark.c:33 @ 1517) [297]
                0.00    0.00       1/3           load_cnn_snapshot (benchmark.c:34 @ 152e) [298]
[56]     0.0    0.00    0.00       3         conv_load (layers_baseline.c:112 @ 385f) [56]
-----------------------------------------------
                0.00    0.00       1/3           make_network (network_baseline.c:11 @ 27cb) [391]
                0.00    0.00       1/3           make_network (network_baseline.c:20 @ 290f) [397]
                0.00    0.00       1/3           make_network (network_baseline.c:29 @ 2a7e) [403]
[57]     0.0    0.00    0.00       3         make_conv_layer (layers_baseline.c:10 @ 348b) [57]
-----------------------------------------------
                0.00    0.00       1/3           make_network (network_baseline.c:17 @ 289f) [395]
                0.00    0.00       1/3           make_network (network_baseline.c:26 @ 2a02) [401]
                0.00    0.00       1/3           make_network (network_baseline.c:35 @ 2b7d) [407]
[58]     0.0    0.00    0.00       3         make_pool_layer (layers_baseline.c:173 @ 3c59) [58]
-----------------------------------------------
                0.00    0.00       1/3           make_network (network_baseline.c:14 @ 2838) [393]
                0.00    0.00       1/3           make_network (network_baseline.c:23 @ 298f) [399]
                0.00    0.00       1/3           make_network (network_baseline.c:32 @ 2b0a) [405]
[59]     0.0    0.00    0.00       3         make_relu_layer (layers_baseline.c:144 @ 3aab) [59]
-----------------------------------------------
                0.00    0.00       1/1           main (benchmark.c:295 @ 26dd) [326]
[60]     0.0    0.00    0.00       1         do_benchmark (benchmark.c:206 @ 227f) [60]
-----------------------------------------------
                0.00    0.00       1/1           load_cnn_snapshot (benchmark.c:35 @ 1548) [299]
[61]     0.0    0.00    0.00       1         fc_load (layers_baseline.c:280 @ 41b2) [61]
-----------------------------------------------
                0.00    0.00       1/1           net_classify (network_baseline.c:141 @ 3477) [467]
[62]     0.0    0.00    0.00       1         free_batch (network_baseline.c:106 @ 30b1) [62]
-----------------------------------------------
                0.00    0.00       1/1           run_classification (benchmark.c:181 @ 2135) [537]
[63]     0.0    0.00    0.00       1         free_network (network_baseline.c:47 @ 2ce7) [63]
-----------------------------------------------
                0.00    0.00       1/1           run_classification (benchmark.c:179 @ 20f9) [536]
[64]     0.0    0.00    0.00       1         get_accuracy (benchmark.c:104 @ 1a50) [64]
-----------------------------------------------
                0.00    0.00       1/1           run_classification (benchmark.c:149 @ 1d8b) [513]
[65]     0.0    0.00    0.00       1         load_batch (benchmark.c:71 @ 17d0) [65]
-----------------------------------------------
                0.00    0.00       1/1           run_classification (benchmark.c:137 @ 1cd8) [504]
[66]     0.0    0.00    0.00       1         load_cnn_snapshot (benchmark.c:30 @ 14e0) [66]
                0.00    0.00       1/1           make_network (network_baseline.c:7 @ 278c) [69]
-----------------------------------------------
                0.00    0.00       1/1           net_classify (network_baseline.c:131 @ 33a6) [459]
[67]     0.0    0.00    0.00       1         make_batch (network_baseline.c:95 @ 2fc2) [67]
-----------------------------------------------
                0.00    0.00       1/1           make_network (network_baseline.c:38 @ 2bf9) [409]
[68]     0.0    0.00    0.00       1         make_fc_layer (layers_baseline.c:238 @ 3f28) [68]
-----------------------------------------------
                0.00    0.00       1/1           load_cnn_snapshot (benchmark.c:30 @ 14e0) [66]
[69]     0.0    0.00    0.00       1         make_network (network_baseline.c:7 @ 278c) [69]
-----------------------------------------------
                0.00    0.00       1/1           make_network (network_baseline.c:41 @ 2c6e) [411]
[70]     0.0    0.00    0.00       1         make_softmax_layer (layers_baseline.c:301 @ 4346) [70]
-----------------------------------------------
                0.00    0.00       1/1           run_classification (benchmark.c:164 @ 1f1c) [524]
[71]     0.0    0.00    0.00       1         net_classify (network_baseline.c:130 @ 3385) [71]
-----------------------------------------------
                0.00    0.00       1/1           do_benchmark (benchmark.c:223 @ 2345) [130]
[72]     0.0    0.00    0.00       1         run_classification (benchmark.c:136 @ 1c97) [72]
-----------------------------------------------


Index by function name

  [49] conv_forward (layers_baseline.c:76 @ 3622) [65] load_batch (benchmark.c:71 @ 17d0) [38] pool_forward (layers_baseline.c:223 @ 3e73)
  [41] conv_forward (layers_baseline.c:91 @ 36e9) [21] load_batch (benchmark.c:91 @ 1962) [32] pool_forward (layers_baseline.c:224 @ 3e7f)
  [31] conv_forward (layers_baseline.c:92 @ 36f2) [28] load_batch (benchmark.c:90 @ 19d1) [20] pool_forward (layers_baseline.c:218 @ 3e89)
  [16] conv_forward (layers_baseline.c:93 @ 36fe) [66] load_cnn_snapshot (benchmark.c:30 @ 14e0) [42] pool_forward (layers_baseline.c:217 @ 3e98)
  [14] conv_forward (layers_baseline.c:94 @ 3709) [67] make_batch (network_baseline.c:95 @ 2fc2) [34] pool_forward (layers_baseline.c:231 @ 3ead)
   [9] conv_forward (layers_baseline.c:95 @ 3715) [57] make_conv_layer (layers_baseline.c:10 @ 348b) [39] pool_forward (layers_baseline.c:214 @ 3ec8)
   [7] conv_forward (layers_baseline.c:96 @ 3720) [68] make_fc_layer (layers_baseline.c:238 @ 3f28) [51] relu_forward (layers_baseline.c:160 @ 3b20)
   [6] conv_forward (layers_baseline.c:97 @ 3743) [69] make_network (network_baseline.c:7 @ 278c) [33] relu_forward (layers_baseline.c:164 @ 3b68)
   [1] conv_forward (layers_baseline.c:98 @ 374c) [58] make_pool_layer (layers_baseline.c:173 @ 3c59) [13] relu_forward (layers_baseline.c:165 @ 3b74)
   [5] conv_forward (layers_baseline.c:97 @ 378e) [59] make_relu_layer (layers_baseline.c:144 @ 3aab) [17] relu_forward (layers_baseline.c:166 @ 3be0)
   [8] conv_forward (layers_baseline.c:94 @ 379d) [70] make_softmax_layer (layers_baseline.c:301 @ 4346) [27] relu_forward (layers_baseline.c:164 @ 3c0e)
  [23] conv_forward (layers_baseline.c:92 @ 37af) [48] make_volume (volume_baseline.c:15 @ 472c) [72] run_classification (benchmark.c:136 @ 1c97)
  [12] conv_forward (layers_baseline.c:104 @ 37c2) [29] make_volume (volume_baseline.c:25 @ 47b8) [55] softmax_forward (layers_baseline.c:326 @ 43e9)
  [56] conv_load (layers_baseline.c:112 @ 385f) [25] make_volume (volume_baseline.c:26 @ 47c1) [43] softmax_forward (layers_baseline.c:334 @ 452e)
  [52] copy_volume (volume_baseline.c:34 @ 4803) [71] net_classify (network_baseline.c:130 @ 3385) [44] softmax_forward (layers_baseline.c:335 @ 453f)
  [60] do_benchmark (benchmark.c:206 @ 227f) [54] net_forward (network_baseline.c:116 @ 314c) [11] softmax_forward (layers_baseline.c:354 @ 4659)
  [53] fc_forward (layers_baseline.c:264 @ 405e) [50] pool_forward (layers_baseline.c:204 @ 3d51) [3] volume_get (volume_baseline.c:7 @ 4679)
  [35] fc_forward (layers_baseline.c:272 @ 40e2) [36] pool_forward (layers_baseline.c:214 @ 3dee) [2] volume_get (volume_baseline.c:8 @ 4698)
  [61] fc_load (layers_baseline.c:280 @ 41b2) [37] pool_forward (layers_baseline.c:217 @ 3e07) [4] volume_get (volume_baseline.c:9 @ 46cb)
  [62] free_batch (network_baseline.c:106 @ 30b1) [26] pool_forward (layers_baseline.c:219 @ 3e1c) [15] volume_set (volume_baseline.c:11 @ 46cd)
  [63] free_network (network_baseline.c:47 @ 2ce7) [19] pool_forward (layers_baseline.c:220 @ 3e27) [10] volume_set (volume_baseline.c:12 @ 46f1)
  [47] free_volume (volume_baseline.c:48 @ 4923) [24] pool_forward (layers_baseline.c:221 @ 3e32) [18] volume_set (volume_baseline.c:13 @ 4729)
  [64] get_accuracy (benchmark.c:104 @ 1a50) [22] pool_forward (layers_baseline.c:222 @ 3e55)
```