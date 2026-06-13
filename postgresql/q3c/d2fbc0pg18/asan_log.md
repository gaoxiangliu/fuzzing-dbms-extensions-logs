pgq3c_nearby_pm_it
```
ASan: asan.log.2457437, query: SELECT public.q3c_ang2ipix(-432455.329893,888018.307851);
=================================================================
==2457437==ERROR: AddressSanitizer: SEGV on unknown address 0x7f3ea6e0b138 (pc 0x7f3d2fc0d5b9 bp 0x7ffd9f1982b0 sp 0x7ffd9f198100 T0)
==2457437==The signal is caused by a READ memory access.
    #0 0x7f3d2fc0d5b9 in pgq3c_nearby_pm_it /q3c/q3c.c
    #1 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /q3c/q3c.c in pgq3c_nearby_pm_it
==2457437==ABORTING

ASan: asan.log.1492, query: SELECT public.q3c_nearby_pm_it(-954714.912015,-913377.333951,-56193.803823,-563139.487586,-1383412892,663796.904731,53407.515459,-91610);
ASan: asan.log.1492, query: SELECT public.q3c_version();
=================================================================
==1492==ERROR: AddressSanitizer: global-buffer-overflow on address 0x7f3d29a11790 at pc 0x7f3d2980d5b9 bp 0x7ffd9f1980f0 sp 0x7ffd9f1980e0
READ of size 8 at 0x7f3d29a11790 thread T0
    #0 0x7f3d2980d5b8 in pgq3c_nearby_pm_it /q3c/q3c.c
    #1 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d29a11790 is located 100240 bytes to the right of global variable '____xbits1' defined in 'dump.c:5:18' (0x7f3d29979000) of size 524288
SUMMARY: AddressSanitizer: global-buffer-overflow /q3c/q3c.c in pgq3c_nearby_pm_it
Shadow bytes around the buggy address:
  0x0fe82533a2a0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a2b0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a2c0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a2d0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a2e0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
=>0x0fe82533a2f0: f9 f9[f9]f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a300: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a310: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a320: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a330: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82533a340: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc


ASan: asan.log.273173, query: SELECT public.q3c_nearby_pm_it(-744738.644221,91901.994603,61075.496436,-869289.766986,2107036092,159929.703727,-936214.526837,25704829);
=================================================================
==273173==ERROR: AddressSanitizer: heap-use-after-free on address 0x7f3d34ee1248 at pc 0x7f3d2880d5b9 bp 0x7ffd9f1980f0 sp 0x7ffd9f1980e0
READ of size 8 at 0x7f3d34ee1248 thread T0
    #0 0x7f3d2880d5b8 in pgq3c_nearby_pm_it /q3c/q3c.c
    #1 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d34ee1248 is located 440904 bytes inside of 524288-byte region [0x7f3d34e75800,0x7f3d34ef5800)
freed by thread T0 here:
    #0 0x7f3d360b4537 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:127
    #1 0x605c4ca39198 in AllocSetReset /postgresql-18.0/src/backend/utils/mmgr/aset.c:588
    #2 0x605c4ca4c5cc in MemoryContextResetOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:419
    #3 0x605c4ca39614 in AllocSetDelete /postgresql-18.0/src/backend/utils/mmgr/aset.c:636
    #4 0x605c4ca4cd11 in MemoryContextDeleteOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:528
    #5 0x605c4ca4cd11 in MemoryContextDelete /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:482
    #6 0x605c4ca4ce2f in MemoryContextDeleteChildren /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:548
    #7 0x605c4ca4ceed in MemoryContextReset /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:389
    #8 0x605c4c604fca in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4539
    #9 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #10 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #11 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #12 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #13 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #14 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #15 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

previously allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4ecdc in palloc0 /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1362
    #4 0x605c4bd8761a in newNode ../../../src/include/nodes/nodes.h:155
    #5 0x605c4bd8761a in ParseFuncOrColumn /postgresql-18.0/src/backend/parser/parse_func.c:748
    #6 0x605c4bd713ee in transformFuncCall /postgresql-18.0/src/backend/parser/parse_expr.c:1474
    #7 0x605c4bd713ee in transformExprRecurse /postgresql-18.0/src/backend/parser/parse_expr.c:227
    #8 0x605c4bd7b265 in transformAExprOp /postgresql-18.0/src/backend/parser/parse_expr.c:987
    #9 0x605c4bd70ae8 in transformExprRecurse /postgresql-18.0/src/backend/parser/parse_expr.c:184
    #10 0x605c4bd70f4b in transformBoolExpr /postgresql-18.0/src/backend/parser/parse_expr.c:1430
    #11 0x605c4bd70f4b in transformExprRecurse /postgresql-18.0/src/backend/parser/parse_expr.c:223
    #12 0x605c4bd70f4b in transformBoolExpr /postgresql-18.0/src/backend/parser/parse_expr.c:1430
    #13 0x605c4bd70f4b in transformExprRecurse /postgresql-18.0/src/backend/parser/parse_expr.c:223
    #14 0x605c4bd70f4b in transformBoolExpr /postgresql-18.0/src/backend/parser/parse_expr.c:1430
    #15 0x605c4bd70f4b in transformExprRecurse /postgresql-18.0/src/backend/parser/parse_expr.c:223
    #16 0x605c4bd70126 in transformExpr /postgresql-18.0/src/backend/parser/parse_expr.c:128
    #17 0x605c4bdad16b in transformTargetEntry /postgresql-18.0/src/backend/parser/parse_target.c:93
    #18 0x605c4bdad2b6 in transformTargetList /postgresql-18.0/src/backend/parser/parse_target.c:181
    #19 0x605c4bd09681 in transformSelectStmt /postgresql-18.0/src/backend/parser/analyze.c:1415
    #20 0x605c4bd09681 in transformStmt /postgresql-18.0/src/backend/parser/analyze.c:374
    #21 0x605c4bd1145c in transformOptionalSelectInto /postgresql-18.0/src/backend/parser/analyze.c:304
    #22 0x605c4bd116e9 in transformTopLevelStmt /postgresql-18.0/src/backend/parser/analyze.c:254
    #23 0x605c4bd11bd1 in parse_analyze_withcb /postgresql-18.0/src/backend/parser/analyze.c:201
    #24 0x605c4c5fd9da in pg_analyze_and_rewrite_withcb /postgresql-18.0/src/backend/tcop/postgres.c:775
    #25 0x605c4c00c61c in prepare_next_query /postgresql-18.0/src/backend/executor/functions.c:943
    #26 0x605c4c00c61c in init_execution_state /postgresql-18.0/src/backend/executor/functions.c:682
    #27 0x605c4c01215a in fmgr_sql /postgresql-18.0/src/backend/executor/functions.c:1649
    #28 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #29 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #30 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #31 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #32 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #33 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #34 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #35 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #36 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #37 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #38 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729

SUMMARY: AddressSanitizer: heap-use-after-free /q3c/q3c.c in pgq3c_nearby_pm_it
Shadow bytes around the buggy address:
  0x0fe8269d41f0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4200: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4210: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4220: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4230: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x0fe8269d4240: fd fd fd fd fd fd fd fd fd[fd]fd fd fd fd fd fd
  0x0fe8269d4250: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4260: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4270: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4280: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d4290: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc

ASan: asan.log.314606, query: SELECT public.q3c_nearby_pm_it(647172.999178,846507.665848,-307843.091111,-49485.873599,-1941185427,129307.659963,530177.262674,855921);
=================================================================
==314606==ERROR: AddressSanitizer: use-after-poison on address 0x7f3d2b14c1e8 at pc 0x7f3d2a80d5b9 bp 0x7ffd9f1980f0 sp 0x7ffd9f1980e0
READ of size 8 at 0x7f3d2b14c1e8 thread T0
    #0 0x7f3d2a80d5b8 in pgq3c_nearby_pm_it /q3c/q3c.c
    #1 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d2b14c1e8 is located 3541480 bytes inside of 8388608-byte region [0x7f3d2adeb800,0x7f3d2b5eb800)
allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4e32f in MemoryContextAlloc /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1204
    #4 0x605c4c9f57eb in hash_create /postgresql-18.0/src/backend/utils/hash/dynahash.c:393
    #5 0x605c4c58e73d in ShmemInitHash /postgresql-18.0/src/backend/storage/ipc/shmem.c:367
    #6 0x605c4c65ea74 in WaitEventCustomShmemInit /postgresql-18.0/src/backend/utils/activity/wait_event.c:149
    #7 0x605c4c573b4c in CreateOrAttachShmemStructs /postgresql-18.0/src/backend/storage/ipc/ipci.c:343
    #8 0x605c4c573b4c in CreateSharedMemoryAndSemaphores /postgresql-18.0/src/backend/storage/ipc/ipci.c:238
    #9 0x605c4c3e2d29 in PostmasterStateMachine /postgresql-18.0/src/backend/postmaster/postmaster.c:3220
    #10 0x605c4c3e478a in process_pm_child_exit /postgresql-18.0/src/backend/postmaster/postmaster.c:2555
    #11 0x605c4c3e478a in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1693
    #12 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #13 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #14 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: use-after-poison /q3c/q3c.c in pgq3c_nearby_pm_it
Shadow bytes around the buggy address:
  0x0fe8256217e0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe8256217f0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621800: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621810: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621820: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
=>0x0fe825621830: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7[f7]f7 f7
  0x0fe825621840: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621850: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621860: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621870: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825621880: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc

```


pgq3c_nearby_it
```
ASan: asan.log.2741013, query: SELECT public.q3c_in_poly(502306.619405,481653.181756,ARRAY[676517.116685, 671607.403825]);
=================================================================
==2741013==ERROR: AddressSanitizer: SEGV on unknown address 0x7f3fa7c1d350 (pc 0x7f3d17c0c854 bp 0x7ffd9f1982b0 sp 0x7ffd9f198140 T0)
==2741013==The signal is caused by a READ memory access.
    #0 0x7f3d17c0c854 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /q3c/q3c.c in pgq3c_nearby_it
==2741013==ABORTING


ASan: asan.log.1042425, query: SELECT public.q3c_nearby_it(552552.268795,-795431.984370,699302.939895,-260903);
=================================================================
==1042425==ERROR: AddressSanitizer: global-buffer-overflow on address 0x7f3d2a0c6c48 at pc 0x7f3d2a00c854 bp 0x7ffd9f198130 sp 0x7ffd9f198120
READ of size 8 at 0x7f3d2a0c6c48 thread T0
    #0 0x7f3d2a00c853 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d2a0c6c48 is located 56392 bytes to the right of global variable '____xbits' defined in 'dump.c:3:18' (0x7f3d2a039000) of size 524288
SUMMARY: AddressSanitizer: global-buffer-overflow /q3c/q3c.c in pgq3c_nearby_it
Shadow bytes around the buggy address:
  0x0fe825410d30: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410d40: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410d50: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410d60: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410d70: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
=>0x0fe825410d80: f9 f9 f9 f9 f9 f9 f9 f9 f9[f9]f9 f9 f9 f9 f9 f9
  0x0fe825410d90: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410da0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410db0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410dc0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825410dd0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc



ASan: asan.log.2924475, query: SELECT public.q3c_nearby_it(-700996.860748,-507816.483456,-475868.447386,-44403179);
=================================================================
==2924475==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x7f3d17fff628 at pc 0x7f3d2d00c854 bp 0x7ffd9f198130 sp 0x7ffd9f198120
READ of size 8 at 0x7f3d17fff628 thread T0
    #0 0x7f3d2d00c853 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d17fff628 is located 472 bytes to the left of 2097152-byte region [0x7f3d17fff800,0x7f3d181ff800)
allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4e32f in MemoryContextAlloc /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1204
    #4 0x605c4c9f57eb in hash_create /postgresql-18.0/src/backend/utils/hash/dynahash.c:393
    #5 0x605c4c58e73d in ShmemInitHash /postgresql-18.0/src/backend/storage/ipc/shmem.c:367
    #6 0x605c4c5cb699 in PredicateLockShmemInit /postgresql-18.0/src/backend/storage/lmgr/predicate.c:1206
    #7 0x605c4c573aaa in CreateOrAttachShmemStructs /postgresql-18.0/src/backend/storage/ipc/ipci.c:303
    #8 0x605c4c573aaa in CreateSharedMemoryAndSemaphores /postgresql-18.0/src/backend/storage/ipc/ipci.c:238
    #9 0x605c4c3e2d29 in PostmasterStateMachine /postgresql-18.0/src/backend/postmaster/postmaster.c:3220
    #10 0x605c4c3e478a in process_pm_child_exit /postgresql-18.0/src/backend/postmaster/postmaster.c:2555
    #11 0x605c4c3e478a in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1693
    #12 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #13 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #14 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: heap-buffer-overflow /q3c/q3c.c in pgq3c_nearby_it
Shadow bytes around the buggy address:
  0x0fe822ff7e70: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7e80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7e90: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7ea0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7eb0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0fe822ff7ec0: fa fa fa fa fa[fa]fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7ed0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7ee0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7ef0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0fe822ff7f00: 00 00 00 00 00 f7 f7 00 00 00 00 00 00 00 00 00
  0x0fe822ff7f10: 00 00 00 00 00 03 f7 f7 f7 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc




ASan: asan.log.4074393, query: SELECT public.q3c_nearby_it(433730.978997,-478997.123873,288378.649905,-1496081);
=================================================================
==4074393==ERROR: AddressSanitizer: heap-use-after-free on address 0x7f3d2775a4f8 at pc 0x7f3d2800c854 bp 0x7ffd9f198130 sp 0x7ffd9f198120
READ of size 8 at 0x7f3d2775a4f8 thread T0
    #0 0x7f3d2800c853 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d2775a4f8 is located 126200 bytes inside of 131072-byte region [0x7f3d2773b800,0x7f3d2775b800)
freed by thread T0 here:
    #0 0x7f3d360b4537 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:127
    #1 0x605c4ca39198 in AllocSetReset /postgresql-18.0/src/backend/utils/mmgr/aset.c:588
    #2 0x605c4ca4c5cc in MemoryContextResetOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:419
    #3 0x605c4ca39614 in AllocSetDelete /postgresql-18.0/src/backend/utils/mmgr/aset.c:636
    #4 0x605c4ca4cd11 in MemoryContextDeleteOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:528
    #5 0x605c4ca4cd11 in MemoryContextDelete /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:482
    #6 0x605c4ca4ce2f in MemoryContextDeleteChildren /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:548
    #7 0x605c4ca4ceed in MemoryContextReset /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:389
    #8 0x605c4c604fca in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4539
    #9 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #10 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #11 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #12 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #13 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #14 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #15 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

previously allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4ecdc in palloc0 /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1362
    #4 0x605c4c123747 in newNode ../../../src/include/nodes/nodes.h:155
    #5 0x605c4c123747 in _copyFuncExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:256
    #6 0x605c4c115c8a in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:58
    #7 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #8 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #9 0x605c4c123efd in _copyOpExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:295
    #10 0x605c4c115caa in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:64
    #11 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #12 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #13 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #14 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #15 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #16 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #17 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #18 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #19 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #20 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #21 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #22 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #23 0x605c4c1297b4 in _copyTargetEntry /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:930
    #24 0x605c4c115f7a in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:199
    #25 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #26 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #27 0x605c4c12a93d in _copyQuery /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:1026
    #28 0x605c4c115fca in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:214
    #29 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #30 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192

SUMMARY: AddressSanitizer: heap-use-after-free /q3c/q3c.c in pgq3c_nearby_it
Shadow bytes around the buggy address:
  0x0fe824ee3440: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee3450: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee3460: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee3470: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee3480: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x0fe824ee3490: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd[fd]
  0x0fe824ee34a0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee34b0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee34c0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee34d0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe824ee34e0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc



ASan: asan.log.1336250, query: SELECT public.q3c_nearby_it(80287.932869,961465.684127,-665251.829802,17750145);
=================================================================
==1336250==ERROR: AddressSanitizer: unknown-crash on address 0x7f3d36a30988 at pc 0x7f3d2e00c854 bp 0x7ffd9f198130 sp 0x7ffd9f198120
READ of size 8 at 0x7f3d36a30988 thread T0
    #0 0x7f3d2e00c853 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

Address 0x7f3d36a30988 is a wild pointer.
SUMMARY: AddressSanitizer: unknown-crash /q3c/q3c.c in pgq3c_nearby_it
Shadow bytes around the buggy address:
  0x0fe826d3e0e0: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e0f0: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e100: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e110: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e120: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
=>0x0fe826d3e130: fe[fe]fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e140: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e150: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e160: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e170: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826d3e180: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc


ASan: asan.log.2345161, query: SELECT public.q3c_nearby_it(-175587.363904,-440288.228091,-407352.260507,975784);
=================================================================
==2345161==ERROR: AddressSanitizer: use-after-poison on address 0x7f3d28a362c0 at pc 0x7f3d2800c854 bp 0x7ffd9f198130 sp 0x7ffd9f198120
READ of size 8 at 0x7f3d28a362c0 thread T0
    #0 0x7f3d2800c853 in pgq3c_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d28a362c0 is located 4541120 bytes inside of 8388608-byte region [0x7f3d285e1800,0x7f3d28de1800)
allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4e32f in MemoryContextAlloc /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1204
    #4 0x605c4c9f57eb in hash_create /postgresql-18.0/src/backend/utils/hash/dynahash.c:393
    #5 0x605c4c58e73d in ShmemInitHash /postgresql-18.0/src/backend/storage/ipc/shmem.c:367
    #6 0x605c4c65ea74 in WaitEventCustomShmemInit /postgresql-18.0/src/backend/utils/activity/wait_event.c:149
    #7 0x605c4c573b4c in CreateOrAttachShmemStructs /postgresql-18.0/src/backend/storage/ipc/ipci.c:343
    #8 0x605c4c573b4c in CreateSharedMemoryAndSemaphores /postgresql-18.0/src/backend/storage/ipc/ipci.c:238
    #9 0x605c4c3e2d29 in PostmasterStateMachine /postgresql-18.0/src/backend/postmaster/postmaster.c:3220
    #10 0x605c4c3e478a in process_pm_child_exit /postgresql-18.0/src/backend/postmaster/postmaster.c:2555
    #11 0x605c4c3e478a in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1693
    #12 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #13 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #14 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: use-after-poison /q3c/q3c.c in pgq3c_nearby_it
Shadow bytes around the buggy address:
  0x0fe82513ec00: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec10: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec20: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec30: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec40: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
=>0x0fe82513ec50: f7 f7 f7 f7 f7 f7 f7 f7[f7]f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec60: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec70: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec80: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513ec90: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe82513eca0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
```

pgq3c_ellipse_nearby_it
```
ASan: asan.log.3708235, query: SELECT public.q3c_ellipse_nearby_it(232511.034480,434653.944325,314219.927075,197208.462760,650558.135703,-259036);
=================================================================
==3708235==ERROR: AddressSanitizer: global-buffer-overflow on address 0x7f3d278ca8c0 at pc 0x7f3d2780de3f bp 0x7ffd9f198110 sp 0x7ffd9f198100
READ of size 8 at 0x7f3d278ca8c0 thread T0
    #0 0x7f3d2780de3e in pgq3c_ellipse_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d278ca8c0 is located 71872 bytes to the right of global variable '____xbits' defined in 'dump.c:3:18' (0x7f3d27839000) of size 524288
SUMMARY: AddressSanitizer: global-buffer-overflow /q3c/q3c.c in pgq3c_ellipse_nearby_it
Shadow bytes around the buggy address:
  0x0fe824f114c0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f114d0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f114e0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f114f0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11500: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
=>0x0fe824f11510: f9 f9 f9 f9 f9 f9 f9 f9[f9]f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11520: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11530: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11540: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11550: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe824f11560: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc



ASan: asan.log.309007, query: SELECT public.q3c_ellipse_nearby_it(-581383.167115,-213739.519864,3418.704627,792843.254019,49420.151682,22566060);
=================================================================
==309007==ERROR: AddressSanitizer: heap-use-after-free on address 0x7f3d34eeed00 at pc 0x7f3d2a00de3f bp 0x7ffd9f198110 sp 0x7ffd9f198100
READ of size 8 at 0x7f3d34eeed00 thread T0
    #0 0x7f3d2a00de3e in pgq3c_ellipse_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d34eeed00 is located 357632 bytes inside of 524288-byte region [0x7f3d34e97800,0x7f3d34f17800)
freed by thread T0 here:
    #0 0x7f3d360b4537 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:127
    #1 0x605c4ca39198 in AllocSetReset /postgresql-18.0/src/backend/utils/mmgr/aset.c:588
    #2 0x605c4ca4c5cc in MemoryContextResetOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:419
    #3 0x605c4ca39614 in AllocSetDelete /postgresql-18.0/src/backend/utils/mmgr/aset.c:636
    #4 0x605c4ca4cd11 in MemoryContextDeleteOnly /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:528
    #5 0x605c4ca4cd11 in MemoryContextDelete /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:482
    #6 0x605c4ca4ce2f in MemoryContextDeleteChildren /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:548
    #7 0x605c4ca4ceed in MemoryContextReset /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:389
    #8 0x605c4c604fca in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4539
    #9 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #10 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #11 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #12 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #13 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #14 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #15 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

previously allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4eaf4 in palloc /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1342
    #4 0x605c4c175b82 in new_list /postgresql-18.0/src/backend/nodes/list.c:137
    #5 0x605c4c179e13 in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1649
    #6 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #7 0x605c4c12b88b in _copyA_Expr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:1097
    #8 0x605c4c11600a in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:226
    #9 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #10 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #11 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #12 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #13 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #14 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #15 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #16 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #17 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #18 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #19 0x605c4c124af0 in _copyBoolExpr /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:358
    #20 0x605c4c115cea in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:76
    #21 0x605c4c12c6c3 in _copyResTarget /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:1215
    #22 0x605c4c116450 in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:256
    #23 0x605c4c179f2f in list_copy_deep /postgresql-18.0/src/backend/nodes/list.c:1652
    #24 0x605c4c12155e in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.c:192
    #25 0x605c4c134dff in _copySelectStmt /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:2106
    #26 0x605c4c116810 in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:436
    #27 0x605c4c13428a in _copyRawStmt /postgresql-18.0/src/backend/nodes/copyfuncs.funcs.c:2032
    #28 0x605c4c1167c0 in copyObjectImpl /postgresql-18.0/src/backend/nodes/copyfuncs.switch.c:421
    #29 0x605c4c00c578 in prepare_next_query /postgresql-18.0/src/backend/executor/functions.c:939
    #30 0x605c4c00c578 in init_execution_state /postgresql-18.0/src/backend/executor/functions.c:682

SUMMARY: AddressSanitizer: heap-use-after-free /q3c/q3c.c in pgq3c_ellipse_nearby_it
Shadow bytes around the buggy address:
  0x0fe8269d5d50: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5d60: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5d70: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5d80: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5d90: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x0fe8269d5da0:[fd]fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5db0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5dc0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5dd0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5de0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x0fe8269d5df0: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc



ASan: asan.log.2464119, query: SELECT public.q3c_ellipse_nearby_it(183248.813286,-250056.520639,-611017.238153,661461.974285,750660.060684,22567278);
=================================================================
==2464119==ERROR: AddressSanitizer: unknown-crash on address 0x7f3d35ef1310 at pc 0x7f3d2b00de3f bp 0x7ffd9f198110 sp 0x7ffd9f198100
READ of size 8 at 0x7f3d35ef1310 thread T0
    #0 0x7f3d2b00de3e in pgq3c_ellipse_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

Address 0x7f3d35ef1310 is a wild pointer.
SUMMARY: AddressSanitizer: unknown-crash /q3c/q3c.c in pgq3c_ellipse_nearby_it
Shadow bytes around the buggy address:
  0x0fe826bd6210: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6220: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6230: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6240: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6250: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
=>0x0fe826bd6260: fe fe[fe]fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6270: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6280: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd6290: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd62a0: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
  0x0fe826bd62b0: fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe fe
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc



ASan: asan.log.488607, query: SELECT public.q3c_ellipse_nearby_it(260212.776027,383733.990975,-124092.254797,-653854.263627,-581134.423486,1268260);
=================================================================
==488607==ERROR: AddressSanitizer: use-after-poison on address 0x7f3d2a4718c0 at pc 0x7f3d2980de3f bp 0x7ffd9f198110 sp 0x7ffd9f198100
READ of size 8 at 0x7f3d2a4718c0 thread T0
    #0 0x7f3d2980de3e in pgq3c_ellipse_nearby_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d2a4718c0 is located 6856896 bytes inside of 8388608-byte region [0x7f3d29de7800,0x7f3d2a5e7800)
allocated by thread T0 here:
    #0 0x7f3d360b4887 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cpp:145
    #1 0x605c4ca35c97 in AllocSetAllocFromNewBlock /postgresql-18.0/src/backend/utils/mmgr/aset.c:908
    #2 0x605c4ca36b3c in AllocSetAlloc /postgresql-18.0/src/backend/utils/mmgr/aset.c:1051
    #3 0x605c4ca4e32f in MemoryContextAlloc /postgresql-18.0/src/backend/utils/mmgr/mcxt.c:1204
    #4 0x605c4c9f57eb in hash_create /postgresql-18.0/src/backend/utils/hash/dynahash.c:393
    #5 0x605c4c58e73d in ShmemInitHash /postgresql-18.0/src/backend/storage/ipc/shmem.c:367
    #6 0x605c4c5ae301 in LockManagerShmemInit /postgresql-18.0/src/backend/storage/lmgr/lock.c:484
    #7 0x605c4c573aa5 in CreateOrAttachShmemStructs /postgresql-18.0/src/backend/storage/ipc/ipci.c:298
    #8 0x605c4c573aa5 in CreateSharedMemoryAndSemaphores /postgresql-18.0/src/backend/storage/ipc/ipci.c:238
    #9 0x605c4c3e2d29 in PostmasterStateMachine /postgresql-18.0/src/backend/postmaster/postmaster.c:3220
    #10 0x605c4c3e478a in process_pm_child_exit /postgresql-18.0/src/backend/postmaster/postmaster.c:2555
    #11 0x605c4c3e478a in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1693
    #12 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #13 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #14 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58

SUMMARY: AddressSanitizer: use-after-poison /q3c/q3c.c in pgq3c_ellipse_nearby_it
Shadow bytes around the buggy address:
  0x0fe8254862c0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe8254862d0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe8254862e0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe8254862f0: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825486300: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
=>0x0fe825486310: f7 f7 f7 f7 f7 f7 f7 f7[f7]f7 f7 f7 f7 f7 f7 f7
  0x0fe825486320: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825486330: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825486340: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825486350: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
  0x0fe825486360: f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7 f7
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
```

q3c_xiyi2ipix
```
ASan: asan.log.997567, query: SELECT public.q3c_join(337411.646566,980062.989043,-747471.184193,82822.425422,-271476.430786);
=================================================================
==997567==ERROR: AddressSanitizer: global-buffer-overflow on address 0x7f3d280d7f78 at pc 0x7f3d2802138f bp 0x7ffd9f195fd0 sp 0x7ffd9f195fc0
READ of size 8 at 0x7f3d280d7f78 thread T0
    #0 0x7f3d2802138e in q3c_xiyi2ipix /q3c/q3cube.c:842
    #1 0x7f3d2802138e in q3c_get_nearby /q3c/q3cube.c:818
    #2 0x7f3d2800c7e5 in pgq3c_nearby_it /q3c/q3c.c:459
    #3 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #4 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #5 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #6 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #7 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #8 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #9 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c350f9d in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4101
    #12 0x605c4c34b30a in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2643
    #13 0x605c4c34cb16 in simplify_and_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3930
    #14 0x605c4c34cb16 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2875
    #15 0x605c4c34c79e in simplify_or_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3834
    #16 0x605c4c34c79e in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2847
    #17 0x605c4c34cb16 in simplify_and_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3930
    #18 0x605c4c34cb16 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2875
    #19 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #20 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #21 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #22 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #23 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #24 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #25 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #26 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #27 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #28 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #29 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #30 0x605c4c98d9ac in BuildCachedPlan /postgresql-18.0/src/backend/utils/cache/plancache.c:1074
    #31 0x605c4c98e2b1 in GetCachedPlan /postgresql-18.0/src/backend/utils/cache/plancache.c:1356
    #32 0x605c4c00cb38 in init_execution_state /postgresql-18.0/src/backend/executor/functions.c:698
    #33 0x605c4c01215a in fmgr_sql /postgresql-18.0/src/backend/executor/functions.c:1649
    #34 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #35 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #36 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #37 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #38 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #39 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #40 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #41 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #42 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #43 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #44 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #45 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #46 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #47 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #48 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #49 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #50 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #51 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #52 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #53 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #54 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #55 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #56 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #57 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #58 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #59 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #60 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #61 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #62 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d280d7f78 is located 126840 bytes to the right of global variable '____xbits' defined in 'dump.c:3:18' (0x7f3d28039000) of size 524288
SUMMARY: AddressSanitizer: global-buffer-overflow /q3c/q3cube.c:842 in q3c_xiyi2ipix
Shadow bytes around the buggy address:
  0x0fe825012f90: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825012fa0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825012fb0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825012fc0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825012fd0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
=>0x0fe825012fe0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9[f9]
  0x0fe825012ff0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825013000: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825013010: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825013020: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe825013030: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc

ASan: asan.log.1103402, query: SELECT public.q3c_join(-441485.935449,277653.220332,899598.957407,-440582.792275,-275167.362630);
=================================================================
==1103402==ERROR: AddressSanitizer: global-buffer-overflow on address 0x7f3d2a0b95a0 at pc 0x7f3d2a0212f5 bp 0x7ffd9f195fd0 sp 0x7ffd9f195fc0
READ of size 8 at 0x7f3d2a0b95a0 thread T0
    #0 0x7f3d2a0212f4 in q3c_xiyi2ipix /q3c/q3cube.c:840
    #1 0x7f3d2a0212f4 in q3c_get_nearby /q3c/q3cube.c:818
    #2 0x7f3d2a00c7e5 in pgq3c_nearby_it /q3c/q3c.c:459
    #3 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #4 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #5 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #6 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #7 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #8 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #9 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c350f9d in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4101
    #12 0x605c4c34b30a in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2643
    #13 0x605c4c34cb16 in simplify_and_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3930
    #14 0x605c4c34cb16 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2875
    #15 0x605c4c34c79e in simplify_or_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3834
    #16 0x605c4c34c79e in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2847
    #17 0x605c4c34cb16 in simplify_and_arguments /postgresql-18.0/src/backend/optimizer/util/clauses.c:3930
    #18 0x605c4c34cb16 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2875
    #19 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #20 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #21 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #22 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #23 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #24 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #25 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #26 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #27 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #28 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #29 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #30 0x605c4c98d9ac in BuildCachedPlan /postgresql-18.0/src/backend/utils/cache/plancache.c:1074
    #31 0x605c4c98e2b1 in GetCachedPlan /postgresql-18.0/src/backend/utils/cache/plancache.c:1356
    #32 0x605c4c00cb38 in init_execution_state /postgresql-18.0/src/backend/executor/functions.c:698
    #33 0x605c4c01215a in fmgr_sql /postgresql-18.0/src/backend/executor/functions.c:1649
    #34 0x605c4bfbbeb7 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:926
    #35 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #36 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #37 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #38 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #39 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #40 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #41 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #42 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #43 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #44 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #45 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #46 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #47 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #48 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #49 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #50 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #51 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #52 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #53 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #54 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #55 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #56 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #57 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #58 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #59 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #60 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #61 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #62 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

0x7f3d2a0b95a0 is located 1440 bytes to the right of global variable '____xbits' defined in 'dump.c:3:18' (0x7f3d2a039000) of size 524288
SUMMARY: AddressSanitizer: global-buffer-overflow /q3c/q3cube.c:840 in q3c_xiyi2ipix
Shadow bytes around the buggy address:
  0x0fe82540f260: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f270: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f280: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f290: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f2a0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
=>0x0fe82540f2b0: f9 f9 f9 f9[f9]f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f2c0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f2d0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f2e0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f2f0: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
  0x0fe82540f300: f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9 f9
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
  Shadow gap:              cc
```

pgq3c_poly_query_it

```
ASan: asan.log.169012, query: SELECT public.q3c_join(-311592.685843,-620447.985040,-262725.544794,-741968.052718,-734101.510185);
=================================================================
==169012==ERROR: AddressSanitizer: SEGV on unknown address 0x5282e7231c48 (pc 0x7f3d2f00eead bp 0x7ffd9f1982b0 sp 0x7ffd9f198160 T0)
==169012==The signal is caused by a READ memory access.
    #0 0x7f3d2f00eead in pgq3c_poly_query_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /q3c/q3c.c in pgq3c_poly_query_it
==169012==ABORTING
```

pgq3c_ellipse_query_it
```
ASan: asan.log.1204274, query: SELECT public.q3c_join(-402325.199908,893139.279726,244755.852002,-388544.040871,-279837.129387);
=================================================================
==1204274==ERROR: AddressSanitizer: SEGV on unknown address 0x7f402a0c48b0 (pc 0x7f3d2f00e738 bp 0x7ffd9f1982b0 sp 0x7ffd9f198250 T0)
==1204274==The signal is caused by a READ memory access.
    #0 0x7f3d2f00e738 in pgq3c_ellipse_query_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /q3c/q3c.c in pgq3c_ellipse_query_it
==1204274==ABORTING
```

pgq3c_radial_query_it
```
ASan: asan.log.2496555, query: SELECT public.q3c_dist(827887.256199,958882.811683,-871695.555757,791001.199039);
=================================================================
==2496555==ERROR: AddressSanitizer: SEGV on unknown address 0x7f3d1b5b9dc0 (pc 0x7f3d2880e267 bp 0x7ffd9f1982b0 sp 0x7ffd9f198260 T0)
==2496555==The signal is caused by a READ memory access.
    #0 0x7f3d2880e267 in pgq3c_radial_query_it /q3c/q3c.c
    #1 0x605c4bfbc127 in ExecInterpExpr /postgresql-18.0/src/backend/executor/execExprInterp.c:953
    #2 0x605c4bfa8137 in ExecInterpExprStillValid /postgresql-18.0/src/backend/executor/execExprInterp.c:2299
    #3 0x605c4c349c53 in ExecEvalExprSwitchContext ../../../../src/include/executor/executor.h:440
    #4 0x605c4c349c53 in evaluate_expr /postgresql-18.0/src/backend/optimizer/util/clauses.c:5014
    #5 0x605c4c351329 in evaluate_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4521
    #6 0x605c4c351329 in simplify_function /postgresql-18.0/src/backend/optimizer/util/clauses.c:4110
    #7 0x605c4c34ad8c in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:2595
    #8 0x605c4c188ed6 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3486
    #9 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #10 0x605c4c189476 in expression_tree_mutator_impl /postgresql-18.0/src/backend/nodes/nodeFuncs.c:3572
    #11 0x605c4c34a0c6 in eval_const_expressions_mutator /postgresql-18.0/src/backend/optimizer/util/clauses.c:3729
    #12 0x605c4c350ae4 in eval_const_expressions /postgresql-18.0/src/backend/optimizer/util/clauses.c:2270
    #13 0x605c4c2dfdbd in preprocess_expression /postgresql-18.0/src/backend/optimizer/plan/planner.c:1284
    #14 0x605c4c2fcdc2 in subquery_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:904
    #15 0x605c4c2ff0cb in standard_planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:435
    #16 0x605c4c301016 in planner /postgresql-18.0/src/backend/optimizer/plan/planner.c:295
    #17 0x605c4c5fdae1 in pg_plan_query /postgresql-18.0/src/backend/tcop/postgres.c:900
    #18 0x605c4c5fdffe in pg_plan_queries /postgresql-18.0/src/backend/tcop/postgres.c:994
    #19 0x605c4c5fea03 in exec_simple_query /postgresql-18.0/src/backend/tcop/postgres.c:1192
    #20 0x605c4c600a89 in PostgresMain /postgresql-18.0/src/backend/tcop/postgres.c:4766
    #21 0x605c4c5f4209 in BackendMain /postgresql-18.0/src/backend/tcop/backend_startup.c:124
    #22 0x605c4c3dc5cd in postmaster_child_launch /postgresql-18.0/src/backend/postmaster/launch_backend.c:290
    #23 0x605c4c3e509b in BackendStartup /postgresql-18.0/src/backend/postmaster/postmaster.c:3587
    #24 0x605c4c3e509b in ServerLoop /postgresql-18.0/src/backend/postmaster/postmaster.c:1702
    #25 0x605c4c3e8159 in PostmasterMain /postgresql-18.0/src/backend/postmaster/postmaster.c:1400
    #26 0x605c4c10f05b in main /postgresql-18.0/src/backend/main/main.c:227
    #27 0x7f3d35429d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
    #28 0x7f3d35429e3f in __libc_start_main_impl ../csu/libc-start.c:392
    #29 0x605c4b978ba4 in _start (/pg180/bin/postgres+0x41eba4)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /q3c/q3c.c in pgq3c_radial_query_it
==2496555==ABORTING
```
