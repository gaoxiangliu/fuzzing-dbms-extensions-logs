#include "postgres.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "nodes/nodes.h"
#include "nodes/parsenodes.h"
#include "parser/scanner.h"
#include "utils/xml.h"
#include "utils/json.h"
#include "common/jsonapi.h"
#include "pgsp_json.h"
#include "pgsp_json_int.h"
#include "pgsp_token_types.h"
void normalize_expr(char *expr, _Bool preserve_space);
static const char *converter_core(word_table *tbl, const char *src,
                                  pgsp_parser_mode mode);
static JsonParseErrorType json_objstart(void *state);
static JsonParseErrorType json_objend(void *state);
static JsonParseErrorType json_arrstart(void *state);
static JsonParseErrorType json_arrend(void *state);
static JsonParseErrorType json_ofstart(void *state, char *fname, _Bool isnull);
static JsonParseErrorType json_aestart(void *state, _Bool isnull);
static JsonParseErrorType json_scalar(void *state, char *token,
                                      JsonTokenType tokentype);
static JsonParseErrorType yaml_objstart(void *state);
static JsonParseErrorType yaml_objend(void *state);
static JsonParseErrorType yaml_arrstart(void *state);
static JsonParseErrorType yaml_arrend(void *state);
static JsonParseErrorType yaml_ofstart(void *state, char *fname, _Bool isnull);
static JsonParseErrorType yaml_aestart(void *state, _Bool isnull);
static JsonParseErrorType yaml_scalar(void *state, char *token,
                                      JsonTokenType tokentype);
static void adjust_wbuf(pgspParserContext *ctx, int len);
static char *hyphenate_words(pgspParserContext *ctx, char *src);
static JsonParseErrorType xml_objstart(void *state);
static JsonParseErrorType xml_objend(void *state);
static JsonParseErrorType xml_arrend(void *state);
static JsonParseErrorType xml_ofstart(void *state, char *fname, _Bool isnull);
static JsonParseErrorType xml_ofend(void *state, char *fname, _Bool isnull);
static JsonParseErrorType xml_aestart(void *state, _Bool isnull);
static JsonParseErrorType xml_aeend(void *state, _Bool isnull);
static JsonParseErrorType xml_scalar(void *state, char *token,
                                     JsonTokenType tokentype);
static void init_json_semaction(JsonSemAction *sem, pgspParserContext *ctx);
word_table propfields[] = {
    {P_NodeType, "t", "Node Type", ((void *)0), 1, conv_nodetype,
     pgsp_node_set_node_type},
    {P_RelationShip, "h", "Parent Relationship", ((void *)0), 1,
     conv_relasionship, ((void *)0)},
    {P_RelationName, "n", "Relation Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_obj_name},
    {P_FunctioName, "f", "Function Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_obj_name},
    {P_IndexName, "i", "Index Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_index_name},
    {P_CTEName, "c", "CTE Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_obj_name},
    {P_TrgRelation, "w", "Relation", ((void *)0), 1, ((void *)0),
     pgsp_node_set_trig_relation},
    {P_Schema, "s", "Schema", ((void *)0), 1, ((void *)0),
     pgsp_node_set_schema_name},
    {P_Alias, "a", "Alias", ((void *)0), 1, ((void *)0), pgsp_node_set_alias},
    {P_Output, "o", "Output", ((void *)0), 1, conv_expression,
     pgsp_node_set_output},
    {P_ScanDir, "d", "Scan Direction", ((void *)0), 1, conv_scandir,
     pgsp_node_set_scan_dir},
    {P_MergeCond, "m", "Merge Cond", ((void *)0), 1, conv_expression,
     pgsp_node_set_merge_cond},
    {P_Strategy, "g", "Strategy", ((void *)0), 1, conv_strategy,
     pgsp_node_set_strategy},
    {P_JoinType, "j", "Join Type", ((void *)0), 1, conv_jointype,
     pgsp_node_set_join_type},
    {P_SortMethod, "e", "Sort Method", ((void *)0), 1, conv_sortmethod,
     pgsp_node_set_sort_method},
    {P_SortKey, "k", "Sort Key", ((void *)0), 1, conv_expression,
     pgsp_node_set_sort_key},
    {P_Filter, "5", "Filter", ((void *)0), 1, conv_expression,
     pgsp_node_set_filter},
    {P_JoinFilter, "6", "Join Filter", ((void *)0), 1, conv_expression,
     pgsp_node_set_join_filter},
    {P_HashCond, "7", "Hash Cond", ((void *)0), 1, conv_expression,
     pgsp_node_set_hash_cond},
    {P_IndexCond, "8", "Index Cond", ((void *)0), 1, conv_expression,
     pgsp_node_set_index_cond},
    {P_TidCond, "9", "TID Cond", ((void *)0), 1, conv_expression,
     pgsp_node_set_tid_cond},
    {P_RecheckCond, "0", "Recheck Cond", ((void *)0), 1, conv_expression,
     pgsp_node_set_recheck_cond},
    {P_Operation, "!", "Operation", ((void *)0), 1, conv_operation,
     pgsp_node_set_operation},
    {P_SubplanName, "q", "Subplan Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_subplan_name},
    {P_Command, "b", "Command", ((void *)0), 1, conv_setsetopcommand,
     pgsp_node_set_setopcommand},
    {P_Triggers, "r", "Triggers", ((void *)0), 1, ((void *)0), ((void *)0)},
    {P_Trigger, "u", "Trigger", ((void *)0), 1, ((void *)0),
     pgsp_node_set_node_type},
    {P_TriggerName, "v", "Trigger Name", ((void *)0), 1, ((void *)0),
     pgsp_node_set_trig_name},
    {P_ConstraintName, "x", "Constraint Name", ((void *)0), 1, ((void *)0),
     ((void *)0)},
    {P_Plans, "l", "Plans", ((void *)0), 1, ((void *)0), ((void *)0)},
    {P_Plan, "p", "Plan", ((void *)0), 1, ((void *)0), ((void *)0)},
    {P_GroupKey, "-", "Group Key", ((void *)0), 1, ((void *)0),
     pgsp_node_set_group_key},
    {P_GroupSets, "=", "Grouping Sets", ((void *)0), 1, ((void *)0),
     ((void *)0)},
    {P_GroupKeys, "\\", "Group Keys", ((void *)0), 1, ((void *)0),
     pgsp_node_set_group_key},
    {P_HashKeys, "~", "Hash Keys", ((void *)0), 1, ((void *)0),
     pgsp_node_set_hash_key},
    {P_HashKey, "|", "Hash Key", ((void *)0), 1, ((void *)0),
     pgsp_node_set_hash_key},
    {P_Parallel, "`", "Parallel Aware", ((void *)0), 1, ((void *)0),
     pgsp_node_set_parallel_aware},
    {P_PartialMode, ">", "Partial Mode", ((void *)0), 1, conv_partialmode,
     pgsp_node_set_partial_mode},
    {P_WorkersPlanned, "{", "Workers Planned", ((void *)0), 1, ((void *)0),
     pgsp_node_set_workers_planned},
    {P_WorkersLaunched, "}", "Workers Launched", ((void *)0), 1, ((void *)0),
     pgsp_node_set_workers_launched},
    {P_InnerUnique, "?", "Inner Unique", ((void *)0), 1, ((void *)0),
     pgsp_node_set_inner_unique},
    {P_AsyncCapable, "ac", "Async Capable", ((void *)0), 1, ((void *)0),
     pgsp_node_set_async_capable},
    {P_FunctionCall, "y", "Function Call", ((void *)0), 0, ((void *)0),
     pgsp_node_set_func_call},
    {P_StartupCost, "1", "Startup Cost", ((void *)0), 0, ((void *)0),
     pgsp_node_set_startup_cost},
    {P_TotalCost, "2", "Total Cost", ((void *)0), 0, ((void *)0),
     pgsp_node_set_total_cost},
    {P_PlanRows, "3", "Plan Rows", ((void *)0), 0, ((void *)0),
     pgsp_node_set_plan_rows},
    {P_PlanWidth, "4", "Plan Width", ((void *)0), 0, ((void *)0),
     pgsp_node_set_plan_width},
    {P_ActualStartupTime, "A", "Actual Startup Time", ((void *)0), 0,
     ((void *)0), pgsp_node_set_actual_startup_time},
    {P_ActualTotalTime, "B", "Actual Total Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_actual_total_time},
    {P_ActualRows, "C", "Actual Rows", ((void *)0), 0, ((void *)0),
     pgsp_node_set_actual_rows},
    {P_ActualLoops, "D", "Actual Loops", ((void *)0), 0, ((void *)0),
     pgsp_node_set_actual_loops},
    {P_HeapFetches, "E", "Heap Fetches", ((void *)0), 0, ((void *)0),
     pgsp_node_set_heap_fetches},
    {P_SharedHitBlks, "F", "Shared Hit Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_shared_hit_blks},
    {P_SharedReadBlks, "G", "Shared Read Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_shared_read_blks},
    {P_SharedDirtiedBlks, "H", "Shared Dirtied Blocks", ((void *)0), 0,
     ((void *)0), pgsp_node_set_shared_dirtied_blks},
    {P_SharedWrittenBlks, "I", "Shared Written Blocks", ((void *)0), 0,
     ((void *)0), pgsp_node_set_shared_written_blks},
    {P_LocalHitBlks, "J", "Local Hit Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_local_hit_blks},
    {P_LocalReadBlks, "K", "Local Read Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_local_read_blks},
    {P_LocalDirtiedBlks, "L", "Local Dirtied Blocks", ((void *)0), 0,
     ((void *)0), pgsp_node_set_local_dirtied_blks},
    {P_LocalWrittenBlks, "M", "Local Written Blocks", ((void *)0), 0,
     ((void *)0), pgsp_node_set_local_written_blks},
    {P_TempReadBlks, "N", "Temp Read Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_temp_read_blks},
    {P_TempWrittenBlks, "O", "Temp Written Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_temp_written_blks},
    {P_IOReadTime, "P", "I/O Read Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_io_read_time},
    {P_IOWwriteTime, "Q", "I/O Write Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_io_write_time},
    {P_SortSpaceUsed, "R", "Sort Space Used", ((void *)0), 0, ((void *)0),
     pgsp_node_set_sort_space_used},
    {P_SortSpaceType, "S", "Sort Space Type", ((void *)0), 0,
     conv_sortspacetype, pgsp_node_set_sort_space_type},
    {P_PeakMemoryUsage, "T", "Peak Memory Usage", ((void *)0), 0, ((void *)0),
     pgsp_node_set_peak_memory_usage},
    {P_OrgHashBatches, "U", "Original Hash Batches", ((void *)0), 0,
     ((void *)0), pgsp_node_set_org_hash_batches},
    {P_OrgHashBuckets, "*", "Original Hash Buckets", ((void *)0), 0,
     ((void *)0), pgsp_node_set_org_hash_buckets},
    {P_HashBatches, "V", "Hash Batches", ((void *)0), 0, ((void *)0),
     pgsp_node_set_hash_batches},
    {P_HashBuckets, "W", "Hash Buckets", ((void *)0), 0, ((void *)0),
     pgsp_node_set_hash_buckets},
    {P_RowsFilterRmvd, "X", "Rows Removed by Filter", ((void *)0), 0,
     ((void *)0), pgsp_node_set_filter_removed},
    {P_RowsIdxRchkRmvd, "Y", "Rows Removed by Index Recheck", ((void *)0), 0,
     ((void *)0), pgsp_node_set_idxrchk_removed},
    {P_TrgTime, "Z", "Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_trig_time},
    {P_TrgCalls, "z", "Calls", ((void *)0), 0, ((void *)0),
     pgsp_node_set_trig_calls},
    {P_PlanTime, "#", "Planning Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_plan_time},
    {P_ExecTime, "$", "Execution Time", ((void *)0), 0, ((void *)0),
     pgsp_node_set_exec_time},
    {P_ExactHeapBlks, "&", "Exact Heap Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_exact_heap_blks},
    {P_LossyHeapBlks, "(", "Lossy Heap Blocks", ((void *)0), 0, ((void *)0),
     pgsp_node_set_lossy_heap_blks},
    {P_RowsJoinFltRemvd, ")", "Rows Removed by Join Filter", ((void *)0), 0,
     ((void *)0), pgsp_node_set_joinfilt_removed},
    {P_TargetTables, "_", "Target Tables", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {P_ConfRes, "%", "Conflict Resolution", ((void *)0), 0, ((void *)0),
     pgsp_node_set_conflict_resolution},
    {P_ConfArbitIdx, "@", "Conflict Arbiter Indexes", ((void *)0), 0,
     ((void *)0), pgsp_node_set_conflict_arbiter_indexes},
    {P_TuplesInserted, "^", "Tuples Inserted", ((void *)0), 0, ((void *)0),
     pgsp_node_set_tuples_inserted},
    {P_ConfTuples, "+", "Conflicting Tuples", ((void *)0), 0, ((void *)0),
     pgsp_node_set_conflicting_tuples},
    {P_SamplingMethod, ":", "Sampling Method", ((void *)0), 0, ((void *)0),
     pgsp_node_set_sampling_method},
    {P_SamplingParams, ";", "Sampling Parameters", ((void *)0), 0, ((void *)0),
     pgsp_node_set_sampling_params},
    {P_RepeatableSeed, "<", "Repeatable Seed", ((void *)0), 0, ((void *)0),
     pgsp_node_set_repeatable_seed},
    {P_Workers, "[", "Workers", ((void *)0), 0, ((void *)0), ((void *)0)},
    {P_WorkerNumber, "]", "Worker Number", ((void *)0), 0, ((void *)0),
     pgsp_node_set_worker_number},
    {P_TableFuncName, "aa", "Table Function Name", ((void *)0), 0, ((void *)0),
     pgsp_node_set_table_func_name},
    {P_PresortedKey, "pk", "Presorted Key", ((void *)0), 0, ((void *)0),
     pgsp_node_set_presorted_key},
    {P_FullsortGroups, "fg", "Full-sort Groups", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {P_SortMethodsUsed, "su", "Sort Methods Used", ((void *)0), 0, ((void *)0),
     pgsp_node_set_sortmethod_used},
    {P_SortSpaceMemory, "sm", "Sort Space Memory", ((void *)0), 0, ((void *)0),
     pgsp_node_set_sortspace_mem},
    {P_GroupCount, "gc", "Group Count", ((void *)0), 0, ((void *)0),
     pgsp_node_set_group_count},
    {P_AvgSortSpcUsed, "as", "Average Sort Space Used", ((void *)0), 0,
     ((void *)0), pgsp_node_set_avg_sortspc_used},
    {P_PeakSortSpcUsed, "ps", "Peak Sort Space Used", ((void *)0), 0,
     ((void *)0), pgsp_node_set_peak_sortspc_used},
    {P_PreSortedGroups, "pg", "Pre-sorted Groups", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {P_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
word_table nodetypes[] = {
    {T_Result, "a", "Result", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_ModifyTable, "b", "ModifyTable", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Append, "c", "Append", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_MergeAppend, "d", "Merge Append", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_RecursiveUnion, "e", "Recursive Union", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_BitmapAnd, "f", "BitmapAnd", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_BitmapOr, "g", "BitmapOr", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_SeqScan, "h", "Seq Scan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_IndexScan, "i", "Index Scan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_IndexOnlyScan, "j", "Index Only Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_BitmapIndexScan, "k", "Bitmap Index Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_BitmapHeapScan, "l", "Bitmap Heap Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_TidScan, "m", "Tid Scan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_SubqueryScan, "n", "Subquery Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_FunctionScan, "o", "Function Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_ValuesScan, "p", "Values Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_CteScan, "q", "CTE Scan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_WorkTableScan, "r", "WorkTable Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_ForeignScan, "s", "Foreign Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_NestLoop, "t", "Nested Loop", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_MergeJoin, "u", "Merge Join", "Merge", 0, ((void *)0), ((void *)0)},
    {T_HashJoin, "v", "Hash Join", "Hash", 0, ((void *)0), ((void *)0)},
    {T_Material, "w", "Materialize", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Sort, "x", "Sort", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Group, "y", "Group", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Agg, "z", "Aggregate", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_WindowAgg, "0", "WindowAgg", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Unique, "1", "Unique", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Hash, "2", "Hash", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_SetOp, "3", "SetOp", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_LockRows, "4", "LockRows", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Limit, "5", "Limit", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_SampleScan, "B", "Sample Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Gather, "6", "Gather", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_ProjectSet, "7", "ProjectSet", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_TableFuncScan, "8", "Table Function Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_NamedTuplestoreScan, "9", "Named Tuplestore Scan", ((void *)0), 0,
     ((void *)0), ((void *)0)},
    {T_GatherMerge, "A", "Gather Merge", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_IncrementalSort, "C", "Incremental Sort", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_TidRangeScan, "D", "Tid Range Scan", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Memoize, "E", "Memoize", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table directions[] = {
    {T_Invalid, "b", "Backward", "Backward", 0, ((void *)0), ((void *)0)},
    {T_Invalid, "n", "NoMovement", "", 0, ((void *)0), ((void *)0)},
    {T_Invalid, "f", "Forward", "", 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table relationships[] = {
    {T_Invalid, "o", "Outer", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "i", "Inner", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "s", "Subquery", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "m", "Member", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "I", "InitPlan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "S", "SubPlan", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
word_table strategies[] = {
    {S_Plain, "p", "Plain", ((void *)0), 0, ((void *)0), ((void *)0)},
    {S_Sorted, "s", "Sorted", ((void *)0), 0, ((void *)0), ((void *)0)},
    {S_Hashed, "h", "Hashed", ((void *)0), 0, ((void *)0), ((void *)0)},
    {S_Mixed, "m", "Mixed", ((void *)0), 0, ((void *)0), ((void *)0)},
    {S_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table operations[] = {
    {T_Invalid, "i", "Insert", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "d", "Delete", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "u", "Update", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table jointypes[] = {
    {T_Invalid, "i", "Inner", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "l", "Left", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "f", "Full", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "r", "Right", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "s", "Semi", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "a", "Anti", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table setsetopcommands[] = {
    {T_Invalid, "i", "Intersect", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "I", "Intersect All", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "e", "Except", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "E", "Except All", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table sortmethods[] = {
    {T_Invalid, "h", "top-N heapsort", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Invalid, "q", "quicksort", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "e", "external sort", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "E", "external merge", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Invalid, "s", "still in progress", ((void *)0), 0, ((void *)0),
     ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table sortspacetype[] = {
    {T_Invalid, "d", "Disk", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "m", "Memory", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
static word_table partialmode[] = {
    {T_Invalid, "p", "Partial", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "f", "Finalize", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, "s", "Simple", ((void *)0), 0, ((void *)0), ((void *)0)},
    {T_Invalid, ((void *)0), ((void *)0), ((void *)0), 0, ((void *)0),
     ((void *)0)}};
word_table *search_word_table(word_table *tbl, const char *word, int mode) {
  word_table *p;
  _Bool longname = (mode == PGSP_JSON_SHORTEN || mode == PGSP_JSON_NORMALIZE);
  for (p = tbl; p->longname; p++) {
    if (strcmp(longname ? p->longname : p->shortname, word) == 0)
      break;
  }
  if (p->longname == ((void *)0) && mode == PGSP_JSON_TEXTIZE) {
    for (p = tbl; p->longname; p++)
      if (strcmp(p->longname, word) == 0)
        break;
  }
  return (p->longname ? p : ((void *)0));
}
const char *converter_core(word_table *tbl, const char *src,
                           pgsp_parser_mode mode) {
  word_table *p;
  char *ret;
  p = search_word_table(tbl, src, mode);
  if (!p)
    return src;
  ret = p->shortname;
  switch (mode) {
  case PGSP_JSON_SHORTEN:
  case PGSP_JSON_NORMALIZE:
    ret = p->shortname;
    break;
  case PGSP_JSON_INFLATE:
  case PGSP_JSON_YAMLIZE:
  case PGSP_JSON_XMLIZE:
    ret = p->longname;
    break;
  case PGSP_JSON_TEXTIZE:
    if (p->textname)
      ret = p->textname;
    else
      ret = p->longname;
    break;
  default:
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(21) && (21) >= 21
              ? errstart_cold(21, ((void *)0))
              : errstart(21, ((void *)0)))
        errmsg_internal("Internal error"),
            errfinish("pgsp_json.c", 402, __func__);
      if (__builtin_constant_p(21) && (21) >= 21)
        abort();
    } while (0);
  }
  return ret;
}
const char *conv_nodetype(const char *src, pgsp_parser_mode mode) {
  return converter_core(nodetypes, src, mode);
}
const char *conv_scandir(const char *src, pgsp_parser_mode mode) {
  return converter_core(directions, src, mode);
}
const char *conv_relasionship(const char *src, pgsp_parser_mode mode) {
  return converter_core(relationships, src, mode);
}
const char *conv_strategy(const char *src, pgsp_parser_mode mode) {
  return converter_core(strategies, src, mode);
}
static int norm_yylex(char *str, core_YYSTYPE *yylval, int *yylloc,
                      core_yyscan_t yyscanner) {
  int tok;
  do {
    sigjmp_buf *_save_exception_stack = PG_exception_stack;
    ErrorContextCallback *_save_context_stack = error_context_stack;
    sigjmp_buf _local_sigjmp_buf;
    _Bool _do_rethrow = 0;
    if (__sigsetjmp(_local_sigjmp_buf, 0) == 0) {
      PG_exception_stack = &_local_sigjmp_buf;
      { tok = core_yylex(yylval, yylloc, yyscanner); }
    } else {
      PG_exception_stack = _save_exception_stack;
      error_context_stack = _save_context_stack;
      {
        FlushErrorState();
        return -1;
      }
    }
    if (_do_rethrow)
      pg_re_throw();
    PG_exception_stack = _save_exception_stack;
    error_context_stack = _save_context_stack;
  } while (0);
  if (tok == Op && str[*yylloc] == '?' &&
      strchr("~!@#^&|`?+-*/%<>=", str[*yylloc + 1]) == ((void *)0))
    tok = SCONST;
  if (tok == Op && strchr("~!@#^&|`?+-*/%<>=", str[*yylloc]) != ((void *)0))
    tok = '=';
  return tok;
}
void normalize_expr(char *expr, _Bool preserve_space) {
  core_yyscan_t yyscanner;
  core_yy_extra_type yyextra;
  core_YYSTYPE yylval;
  int yylloc;
  int lastloc;
  int start;
  char *wp;
  int tok, lasttok;
  wp = expr;
  yyscanner = scanner_init(expr, &yyextra, &ScanKeywords, ScanKeywordTokens);
  yyextra.escape_string_warning = 0;
  lasttok = 0;
  lastloc = -1;
  for (;;) {
    tok = norm_yylex(expr, &yylval, &yylloc, yyscanner);
    start = yylloc;
    if (lastloc >= 0) {
      int i, i2;
      for (i = lastloc; i < start && ((expr[i]) == ' ' || (expr[i]) == '\n' ||
                                      (expr[i]) == '\t');
           i++)
        ;
      for (i2 = i; i2 < start && !((expr[i2]) == ' ' || (expr[i2]) == '\n' ||
                                   (expr[i2]) == '\t');
           i2++)
        ;
      if (lasttok == IDENT) {
        memcpy(wp, expr + i, i2 - i);
        wp += i2 - i;
      } else if (lasttok == ';') {
      } else {
        char *sp;
        for (sp = expr + i; sp < expr + i2; sp++, wp++)
          *wp = (*sp >= 'a' && *sp <= 'z' ? *sp - ('a' - 'A') : *sp);
      }
      if (tok > 0 && i2 < start &&
          (preserve_space ||
           (tok >= IDENT && lasttok >= IDENT &&
            !(tok == FCONST || tok == SCONST || tok == BCONST ||
              tok == XCONST || tok == ICONST || tok == NULL_P ||
              tok == TRUE_P || tok == FALSE_P || tok == CURRENT_CATALOG ||
              tok == CURRENT_DATE || tok == CURRENT_ROLE ||
              tok == CURRENT_SCHEMA || tok == CURRENT_TIME ||
              tok == CURRENT_TIMESTAMP || tok == CURRENT_USER ||
              tok == LOCALTIME || tok == LOCALTIMESTAMP) &&
            !(lasttok == FCONST || lasttok == SCONST || lasttok == BCONST ||
              lasttok == XCONST || lasttok == ICONST || lasttok == NULL_P ||
              lasttok == TRUE_P || lasttok == FALSE_P ||
              lasttok == CURRENT_CATALOG || lasttok == CURRENT_DATE ||
              lasttok == CURRENT_ROLE || lasttok == CURRENT_SCHEMA ||
              lasttok == CURRENT_TIME || lasttok == CURRENT_TIMESTAMP ||
              lasttok == CURRENT_USER || lasttok == LOCALTIME ||
              lasttok == LOCALTIMESTAMP))))
        *wp++ = ' ';
      start = i2;
    }
    if (tok < 0) {
      *wp = 0;
      return;
    }
    if (tok == '-')
      tok = norm_yylex(expr, &yylval, &yylloc, yyscanner);
    if (tok < 0) {
      *wp = 0;
      return;
    }
    if ((tok == FCONST || tok == SCONST || tok == BCONST || tok == XCONST ||
         tok == ICONST || tok == NULL_P || tok == TRUE_P || tok == FALSE_P ||
         tok == CURRENT_CATALOG || tok == CURRENT_DATE || tok == CURRENT_ROLE ||
         tok == CURRENT_SCHEMA || tok == CURRENT_TIME ||
         tok == CURRENT_TIMESTAMP || tok == CURRENT_USER || tok == LOCALTIME ||
         tok == LOCALTIMESTAMP)) {
      int end;
      tok = norm_yylex(expr, &yylval, &end, yyscanner);
      if (tok < 0) {
        *wp = 0;
        return;
      }
      if (lasttok == '(' && tok == ')') {
        wp -= (start - lastloc);
        start = lastloc;
        end++;
      }
      while (expr[end - 1] == ' ')
        end--;
      *wp++ = '?';
      yylloc = end;
    }
    if (tok == 0)
      break;
    lasttok = tok;
    lastloc = yylloc;
  }
  *wp = 0;
}
const char *conv_expression(const char *src, pgsp_parser_mode mode) {
  const char *ret = src;
  if (mode == PGSP_JSON_NORMALIZE) {
    char *t = pstrdup(src);
    normalize_expr(t, 1);
    ret = (const char *)t;
  }
  return ret;
}
const char *conv_operation(const char *src, pgsp_parser_mode mode) {
  return converter_core(operations, src, mode);
}
const char *conv_jointype(const char *src, pgsp_parser_mode mode) {
  return converter_core(jointypes, src, mode);
}
const char *conv_setsetopcommand(const char *src, pgsp_parser_mode mode) {
  return converter_core(setsetopcommands, src, mode);
}
const char *conv_sortmethod(const char *src, pgsp_parser_mode mode) {
  return converter_core(sortmethods, src, mode);
}
const char *conv_sortspacetype(const char *src, pgsp_parser_mode mode) {
  return converter_core(sortspacetype, src, mode);
}
const char *conv_partialmode(const char *src, pgsp_parser_mode mode) {
  return converter_core(partialmode, src, mode);
}
static JsonParseErrorType json_objstart(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->mode == PGSP_JSON_INFLATE) {
    if (!ctx->fname && ctx->dest->len > 0) {
      appendStringInfoChar(ctx->dest, '\n');
      appendStringInfoSpaces(ctx->dest, (ctx->level) * 2);
    }
    ctx->fname = ((void *)0);
  }
  appendStringInfoChar(ctx->dest, '{');
  ctx->level++;
  ctx->first = bms_add_member(ctx->first, ctx->level);
  if (ctx->mode == PGSP_JSON_INFLATE)
    appendStringInfoChar(ctx->dest, '\n');
  return JSON_SUCCESS;
}
static JsonParseErrorType json_objend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->mode == PGSP_JSON_INFLATE) {
    if (!bms_is_member(ctx->level, ctx->first))
      appendStringInfoChar(ctx->dest, '\n');
    appendStringInfoSpaces(ctx->dest, (ctx->level - 1) * 2);
  }
  appendStringInfoChar(ctx->dest, '}');
  ctx->level--;
  ctx->last_elem_is_object = 1;
  ctx->first = bms_del_member(ctx->first, ctx->level);
  ctx->fname = ((void *)0);
  return JSON_SUCCESS;
}
static JsonParseErrorType json_arrstart(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (((ctx->current_list) == P_GroupKeys || (ctx->current_list) == P_HashKeys))
    ctx->wlist_level++;
  appendStringInfoChar(ctx->dest, '[');
  ctx->fname = ((void *)0);
  ctx->level++;
  ctx->last_elem_is_object = 1;
  ctx->first = bms_add_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType json_arrend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (((ctx->current_list) == P_GroupKeys || (ctx->current_list) == P_HashKeys))
    ctx->wlist_level--;
  if (ctx->mode == PGSP_JSON_INFLATE &&
      (((ctx->current_list) == P_GroupKeys || (ctx->current_list) == P_HashKeys)
           ? ctx->wlist_level == 0
           : ctx->last_elem_is_object)) {
    appendStringInfoChar(ctx->dest, '\n');
    appendStringInfoSpaces(ctx->dest, (ctx->level - 1) * 2);
  }
  appendStringInfoChar(ctx->dest, ']');
  ctx->level--;
  return JSON_SUCCESS;
}
static JsonParseErrorType json_ofstart(void *state, char *fname, _Bool isnull) {
  word_table *p;
  pgspParserContext *ctx = (pgspParserContext *)state;
  char *fn;
  ctx->remove = 0;
  p = search_word_table(propfields, fname, ctx->mode);
  if (!p) {
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(14) && (14) >= 21
              ? errstart_cold(14, ((void *)0))
              : errstart(14, ((void *)0)))
        (errmsg("JSON parser encoutered unknown field name: \"%s\".", fname),
         errdetail_log("INPUT: \"%s\"", ctx->org_string)),
            errfinish("pgsp_json.c", 807, __func__);
      if (__builtin_constant_p(14) && (14) >= 21)
        abort();
    } while (0);
  }
  ctx->remove = (ctx->mode == PGSP_JSON_NORMALIZE && (!p || !p->normalize_use));
  if (ctx->remove)
    return JSON_SUCCESS;
  if (!bms_is_member(ctx->level, ctx->first)) {
    appendStringInfoChar(ctx->dest, ',');
    if (ctx->mode == PGSP_JSON_INFLATE)
      appendStringInfoChar(ctx->dest, '\n');
  } else
    ctx->first = bms_del_member(ctx->first, ctx->level);
  if (ctx->mode == PGSP_JSON_INFLATE)
    appendStringInfoSpaces(ctx->dest, ctx->level * 2);
  if (!p || !p->longname)
    fn = fname;
  else if (ctx->mode == PGSP_JSON_INFLATE || !(p->shortname && p->shortname[0]))
    fn = p->longname;
  else
    fn = p->shortname;
  escape_json(ctx->dest, fn);
  ctx->fname = fn;
  ctx->valconverter = (p ? p->converter : ((void *)0));
  appendStringInfoChar(ctx->dest, ':');
  if (ctx->mode == PGSP_JSON_INFLATE)
    appendStringInfoChar(ctx->dest, ' ');
  if (p && ((p->tag) == P_GroupKeys || (p->tag) == P_HashKeys)) {
    ctx->current_list = p->tag;
    ctx->list_fname = fname;
    ctx->wlist_level = 0;
  }
  return JSON_SUCCESS;
}
static JsonParseErrorType json_ofend(void *state, char *fname, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->list_fname && strcmp(fname, ctx->list_fname) == 0) {
    ctx->list_fname = ((void *)0);
    ctx->current_list = P_Invalid;
  }
  return JSON_SUCCESS;
}
static JsonParseErrorType json_aestart(void *state, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->remove)
    return JSON_SUCCESS;
  if (((ctx->current_list) == P_GroupKeys ||
       (ctx->current_list) == P_HashKeys) &&
      ctx->wlist_level == 1) {
    if (!bms_is_member(ctx->level, ctx->first))
      appendStringInfoChar(ctx->dest, ',');
    if (ctx->mode == PGSP_JSON_INFLATE) {
      appendStringInfoChar(ctx->dest, '\n');
      appendStringInfoSpaces(ctx->dest, (ctx->level) * 2);
    }
  } else {
    if (!bms_is_member(ctx->level, ctx->first)) {
      appendStringInfoChar(ctx->dest, ',');
      if (ctx->mode == PGSP_JSON_INFLATE && !ctx->last_elem_is_object)
        appendStringInfoChar(ctx->dest, ' ');
    }
  }
  ctx->first = bms_del_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType json_scalar(void *state, char *token,
                                      JsonTokenType tokentype) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  const char *val = token;
  if (ctx->remove)
    return JSON_SUCCESS;
  if (ctx->valconverter)
    val = ctx->valconverter(token, ctx->mode);
  if (tokentype == JSON_TOKEN_STRING)
    escape_json(ctx->dest, val);
  else
    appendStringInfoString(ctx->dest, val);
  ctx->last_elem_is_object = 0;
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_objstart(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->fname) {
    if (ctx->dest->len > 0)
      appendStringInfoChar(ctx->dest, '\n');
    appendStringInfoSpaces(ctx->dest, (ctx->level - 1) * 2);
    appendStringInfoString(ctx->dest, "- ");
    appendStringInfoString(ctx->dest, ctx->fname);
    appendStringInfoString(ctx->dest, ":\n");
    appendStringInfoSpaces(ctx->dest, (ctx->level + 1) * 2);
    ctx->fname = ((void *)0);
  }
  ctx->level++;
  ctx->first = bms_add_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_objend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  ctx->level--;
  ctx->last_elem_is_object = 1;
  ctx->first = bms_del_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_arrstart(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->fname) {
    appendStringInfoString(ctx->dest, ctx->fname);
    appendStringInfoString(ctx->dest, ":");
  }
  ctx->fname = ((void *)0);
  ctx->level++;
  ctx->first = bms_add_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_arrend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  ctx->level--;
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_ofstart(void *state, char *fname, _Bool isnull) {
  word_table *p;
  pgspParserContext *ctx = (pgspParserContext *)state;
  char *s;
  p = search_word_table(propfields, fname, ctx->mode);
  if (!p) {
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(14) && (14) >= 21
              ? errstart_cold(14, ((void *)0))
              : errstart(14, ((void *)0)))
        (errmsg("Short JSON parser encoutered unknown field name: \"%s\".",
                fname),
         errdetail_log("INPUT: \"%s\"", ctx->org_string)),
            errfinish("pgsp_json.c", 1006, __func__);
      if (__builtin_constant_p(14) && (14) >= 21)
        abort();
    } while (0);
  }
  s = (p ? p->longname : fname);
  if (!bms_is_member(ctx->level, ctx->first)) {
    appendStringInfoString(ctx->dest, "\n");
    appendStringInfoSpaces(ctx->dest, ctx->level * 2);
  } else
    ctx->first = bms_del_member(ctx->first, ctx->level);
  ctx->valconverter = ((void *)0);
  ctx->fname = s;
  ctx->valconverter = (p ? p->converter : ((void *)0));
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_aestart(void *state, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  appendStringInfoString(ctx->dest, "\n");
  ctx->first = bms_del_member(ctx->first, ctx->level);
  appendStringInfoSpaces(ctx->dest, ctx->level * 2);
  appendStringInfoString(ctx->dest, "- ");
  return JSON_SUCCESS;
}
static JsonParseErrorType yaml_scalar(void *state, char *token,
                                      JsonTokenType tokentype) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  if (ctx->fname) {
    appendStringInfoString(ctx->dest, ctx->fname);
    appendStringInfoString(ctx->dest, ": ");
    ctx->fname = ((void *)0);
  }
  json_scalar(state, token, tokentype);
  ctx->last_elem_is_object = 0;
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_objstart(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  ctx->level++;
  ctx->first = bms_add_member(ctx->first, ctx->level);
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_objend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  appendStringInfoChar(ctx->dest, '\n');
  appendStringInfoSpaces(ctx->dest, ctx->level * 2);
  ctx->level--;
  ctx->first = bms_del_member(ctx->first, ctx->level);
  ctx->last_elem_is_object = 1;
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_arrend(void *state) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  appendStringInfoChar(ctx->dest, '\n');
  appendStringInfoSpaces(ctx->dest, (ctx->level + 1) * 2);
  return JSON_SUCCESS;
}
static void adjust_wbuf(pgspParserContext *ctx, int len) {
  int buflen;
  for (buflen = ctx->wbuflen; len > buflen; buflen *= 2)
    ;
  if (buflen > ctx->wbuflen) {
    ctx->wbuf = (char *)palloc(buflen);
    ctx->wbuflen = buflen;
  }
}
static char *hyphenate_words(pgspParserContext *ctx, char *src) {
  char *p;
  adjust_wbuf(ctx, strlen(src) + 1);
  strcpy(ctx->wbuf, src);
  for (p = ctx->wbuf; *p; p++)
    if (*p == ' ')
      *p = '-';
  return ctx->wbuf;
}
static JsonParseErrorType xml_ofstart(void *state, char *fname, _Bool isnull) {
  word_table *p;
  pgspParserContext *ctx = (pgspParserContext *)state;
  char *s;
  p = search_word_table(propfields, fname, ctx->mode);
  if (!p) {
    do {
      int __errno_location __attribute__((unused));
      if (__builtin_constant_p(14) && (14) >= 21
              ? errstart_cold(14, ((void *)0))
              : errstart(14, ((void *)0)))
        (errmsg("Short JSON parser encoutered unknown field name: \"%s\".",
                fname),
         errdetail_log("INPUT: \"%s\"", ctx->org_string)),
            errfinish("pgsp_json.c", 1136, __func__);
      if (__builtin_constant_p(14) && (14) >= 21)
        abort();
    } while (0);
  }
  s = (p ? p->longname : fname);
  if (p && (p->tag == P_Plan || p->tag == P_Triggers))
    ctx->section = p->tag;
  appendStringInfoChar(ctx->dest, '\n');
  appendStringInfoSpaces(ctx->dest, (ctx->level + 1) * 2);
  ctx->valconverter = ((void *)0);
  appendStringInfoChar(ctx->dest, '<');
  appendStringInfoString(ctx->dest, escape_xml(hyphenate_words(ctx, s)));
  appendStringInfoChar(ctx->dest, '>');
  ctx->valconverter = (p ? p->converter : ((void *)0));
  if (p && (p->tag == P_Plans || p->tag == P_Triggers))
    ctx->not_item = bms_add_member(ctx->not_item, ctx->level + 1);
  else
    ctx->not_item = bms_del_member(ctx->not_item, ctx->level + 1);
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_ofend(void *state, char *fname, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  word_table *p;
  char *s;
  p = search_word_table(propfields, fname, ctx->mode);
  s = (p ? p->longname : fname);
  appendStringInfoString(ctx->dest, "</");
  appendStringInfoString(ctx->dest, escape_xml(hyphenate_words(ctx, s)));
  appendStringInfoChar(ctx->dest, '>');
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_aestart(void *state, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  char *tag;
  ctx->level++;
  if (bms_is_member(ctx->level, ctx->not_item)) {
    if (ctx->section == P_Plan)
      tag = "<Plan>";
    else
      tag = "<Trigger>";
  } else
    tag = "<Item>";
  appendStringInfoChar(ctx->dest, '\n');
  appendStringInfoSpaces(ctx->dest, (ctx->level + 1) * 2);
  appendStringInfoString(ctx->dest, tag);
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_aeend(void *state, _Bool isnull) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  char *tag;
  if (bms_is_member(ctx->level, ctx->not_item)) {
    if (ctx->section == P_Plan)
      tag = "</Plan>";
    else
      tag = "</Trigger>";
  } else
    tag = "</Item>";
  appendStringInfoString(ctx->dest, tag);
  ctx->level--;
  return JSON_SUCCESS;
}
static JsonParseErrorType xml_scalar(void *state, char *token,
                                     JsonTokenType tokentype) {
  pgspParserContext *ctx = (pgspParserContext *)state;
  const char *s = token;
  if (ctx->valconverter)
    s = ctx->valconverter(token, PGSP_JSON_XMLIZE);
  if (tokentype == JSON_TOKEN_STRING)
    s = escape_xml(s);
  appendStringInfoString(ctx->dest, s);
  ctx->last_elem_is_object = 0;
  return JSON_SUCCESS;
}
void init_parser_context(pgspParserContext *ctx, int mode, char *orgstr,
                         char *buf, int buflen) {
  memset(ctx, 0, sizeof(*ctx));
  ctx->dest = makeStringInfo();
  ctx->mode = mode;
  ctx->org_string = orgstr;
  ctx->wbuf = buf;
  ctx->wbuflen = buflen;
}
_Bool run_pg_parse_json(JsonLexContext *lex, JsonSemAction *sem) {
  return pg_parse_json(lex, sem) == JSON_SUCCESS;
}
void init_json_lex_context(JsonLexContext *lex, char *json) {
  makeJsonLexContextCstringLen(lex, json, strlen(json), GetDatabaseEncoding(),
                               1);
}
static void init_json_semaction(JsonSemAction *sem, pgspParserContext *ctx) {
  sem->semstate = (void *)ctx;
  sem->object_start = json_objstart;
  sem->object_end = json_objend;
  sem->array_start = json_arrstart;
  sem->array_end = json_arrend;
  sem->object_field_start = json_ofstart;
  sem->object_field_end = json_ofend;
  sem->array_element_start = json_aestart;
  sem->array_element_end = ((void *)0);
  sem->scalar = json_scalar;
}
char *pgsp_json_shorten(char *json) {
  JsonLexContext lex;
  JsonSemAction sem;
  pgspParserContext ctx;
  init_json_lex_context(&lex, json);
  init_parser_context(&ctx, PGSP_JSON_SHORTEN, json, ((void *)0), 0);
  init_json_semaction(&sem, &ctx);
  run_pg_parse_json(&lex, &sem);
  return ctx.dest->data;
}
char *pgsp_json_normalize(char *json) {
  JsonLexContext lex;
  JsonSemAction sem;
  pgspParserContext ctx;
  init_json_lex_context(&lex, json);
  init_parser_context(&ctx, PGSP_JSON_NORMALIZE, json, ((void *)0), 0);
  init_json_semaction(&sem, &ctx);
  run_pg_parse_json(&lex, &sem);
  return ctx.dest->data;
}
char *pgsp_json_inflate(char *json) {
  JsonLexContext lex;
  JsonSemAction sem;
  pgspParserContext ctx;
  init_json_lex_context(&lex, json);
  init_parser_context(&ctx, PGSP_JSON_INFLATE, json, ((void *)0), 0);
  init_json_semaction(&sem, &ctx);
  if (!run_pg_parse_json(&lex, &sem)) {
    if (ctx.dest->len > 0 && ctx.dest->data[ctx.dest->len - 1] != '\n')
      appendStringInfoChar(ctx.dest, '\n');
    if (ctx.dest->len == 0)
      appendStringInfoString(ctx.dest, "<Input was not JSON>");
    else
      appendStringInfoString(ctx.dest, "<truncated>");
  }
  return ctx.dest->data;
}
char *pgsp_json_yamlize(char *json) {
  pgspParserContext ctx;
  JsonSemAction sem;
  JsonLexContext lex;
  init_json_lex_context(&lex, json);
  init_parser_context(&ctx, PGSP_JSON_YAMLIZE, json, ((void *)0), 0);
  sem.semstate = (void *)&ctx;
  sem.object_start = yaml_objstart;
  sem.object_end = yaml_objend;
  sem.array_start = yaml_arrstart;
  sem.array_end = yaml_arrend;
  sem.object_field_start = yaml_ofstart;
  sem.object_field_end = ((void *)0);
  sem.array_element_start = yaml_aestart;
  sem.array_element_end = ((void *)0);
  sem.scalar = yaml_scalar;
  if (!run_pg_parse_json(&lex, &sem)) {
    if (ctx.dest->len > 0 && ctx.dest->data[ctx.dest->len - 1] != '\n')
      appendStringInfoChar(ctx.dest, '\n');
    if (ctx.dest->len == 0)
      appendStringInfoString(ctx.dest, "<Input was not JSON>");
    else
      appendStringInfoString(ctx.dest, "<truncated>");
  }
  return ctx.dest->data;
}
char *pgsp_json_xmlize(char *json) {
  pgspParserContext ctx;
  JsonSemAction sem;
  JsonLexContext lex;
  int start_len;
  char buf[32];
  init_json_lex_context(&lex, json);
  init_parser_context(&ctx, PGSP_JSON_XMLIZE, json, buf, sizeof(buf));
  sem.semstate = (void *)&ctx;
  sem.object_start = xml_objstart;
  sem.object_end = xml_objend;
  sem.array_start = ((void *)0);
  sem.array_end = xml_arrend;
  sem.object_field_start = xml_ofstart;
  sem.object_field_end = xml_ofend;
  sem.array_element_start = xml_aestart;
  sem.array_element_end = xml_aeend;
  sem.scalar = xml_scalar;
  appendStringInfo(
      ctx.dest,
      "<explain xmlns=\"http://www.postgresql.org/2009/explain\">\n  <Query>");
  start_len = ctx.dest->len;
  if (!run_pg_parse_json(&lex, &sem)) {
    if (ctx.dest->len > start_len && ctx.dest->data[ctx.dest->len - 1] != '\n')
      appendStringInfoChar(ctx.dest, '\n');
    if (ctx.dest->len == start_len) {
      resetStringInfo(ctx.dest);
      appendStringInfoString(ctx.dest, "<Input was not JSON>");
    } else
      appendStringInfoString(ctx.dest, "<truncated>");
  } else
    appendStringInfo(ctx.dest, "</Query>\n</explain>\n");
  return ctx.dest->data;
}
