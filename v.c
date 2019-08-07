    
#include <stdio.h>  // TODO remove all these includes, define all function signatures and types manually 
#include <stdlib.h>
#include <signal.h>
#include <stdarg.h> // for va_list 
#include <inttypes.h>  // int64_t etc 
#include <string.h> // memcpy 

#define STRUCT_DEFAULT_VALUE {}
#define EMPTY_STRUCT_DECLARATION
#define EMPTY_STRUCT_INIT
#define OPTION_CAST(x) (x)

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// must be included after <windows.h> 
#include <shellapi.h>

#include <io.h> // _waccess
#include <fcntl.h> // _O_U8TEXT
#include <direct.h> // _wgetcwd
//#include <WinSock2.h>
#ifdef _MSC_VER
// On MSVC these are the same (as long as /volatile:ms is passed)
#define _Atomic volatile

// MSVC can't parse some things properly
#undef STRUCT_DEFAULT_VALUE
#define STRUCT_DEFAULT_VALUE {0}
#undef EMPTY_STRUCT_DECLARATION
#define EMPTY_STRUCT_DECLARATION void *____dummy_variable;
#undef EMPTY_STRUCT_INIT
#define EMPTY_STRUCT_INIT 0
#undef OPTION_CAST
#define OPTION_CAST(x)
#endif

void pthread_mutex_lock(HANDLE *m) {
	WaitForSingleObject(*m, INFINITE);
}

void pthread_mutex_unlock(HANDLE *m) {
	ReleaseMutex(*m);
}
#else
#include <pthread.h> 
#endif 

//================================== TYPEDEFS ================================*/ 

typedef unsigned char byte;
typedef unsigned int uint;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uint32_t rune;
typedef float f32;
typedef double f64; 
typedef unsigned char* byteptr;
typedef int* intptr;
typedef void* voidptr;
typedef struct array array;
typedef struct map map;
typedef array array_string; 
typedef array array_int; 
typedef array array_byte; 
typedef array array_uint; 
typedef array array_float; 
typedef array array_f32; 
typedef array array_f64; 
typedef map map_int; 
typedef map map_string; 
#ifndef bool
	typedef int bool;
	#define true 1
	#define false 0
#endif

//============================== HELPER C MACROS =============================*/ 

#define _PUSH(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push(arr, &tmp);}
#define _PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push_many(arr, tmp.data, tmp.len);}
#define _IN(typ, val, arr) array_##typ##_contains(arr, val) 
#define _IN_MAP(val, m) map__exists(m, val) 
#define ALLOC_INIT(type, ...) (type *)memdup((type[]){ __VA_ARGS__ }, sizeof(type)) 

//================================== GLOBALS =================================*/   
//int V_ZERO = 0; 
byteptr g_str_buf; 
int load_so(byteptr);
void reload_so();
void init_consts();
 int g_test_ok = 1; 
 /*================================== FNS =================================*/
#include <float.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#ifndef _WIN32
#include <dirent.h>
#endif
#ifndef _WIN32
#include <unistd.h>
#endif
#include <math.h>
#include <time.h>
typedef struct array array;
typedef array array_int;
typedef array array_u64;
typedef array array_string;
typedef array array_byte;
typedef struct string string;
typedef struct ustring ustring;
typedef struct map map;
typedef struct Node Node;
typedef struct Option Option;
typedef struct strings__Builder strings__Builder;
typedef struct os__File os__File;
typedef struct os__FileInfo os__FileInfo;
typedef Option Option_string;
typedef array array_ustring;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef struct os__filetime os__filetime;
typedef struct os__win32finddata os__win32finddata;
typedef struct time__Time time__Time;
typedef Option Option_int;
typedef struct CGen CGen;
typedef struct Fn Fn;
typedef array array_Var;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef struct V V;
typedef struct Preferences Preferences;
typedef struct ModDepGraphNode ModDepGraphNode;
typedef struct ModDepGraph ModDepGraph;
typedef array array_ModDepGraphNode;
typedef struct DepSet DepSet;
typedef array array_FileImportTable;
typedef struct Var Var;
typedef struct Parser Parser;
typedef struct Scanner Scanner;
typedef struct ScanRes ScanRes;
typedef struct Table Table;
typedef array array_Type;
typedef map map_Fn;
typedef array array_GenTable;
typedef struct GenTable GenTable;
typedef struct FileImportTable FileImportTable;
typedef int AccessMod;
typedef struct Type Type;
typedef array array_Fn;
typedef int Token;
typedef array array_Token;
typedef Option Option_string;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_os__File;
typedef Option Option_int;
typedef int BuildMode;
typedef int OS;
typedef int Pass;
typedef map map_ModDepGraphNode;
typedef map map_DepSet;
typedef int AccessMod;
typedef int Token;
struct array {
void* data;
int len;
int cap;
int element_size;
}; 
struct string {
byte* str;
int len;
}; 
struct ustring {
string s;
array_int runes;
int len;
}; 
struct map {
int element_size;
Node* root;
array_string _keys;
int key_i;
int size;
}; 
struct Node {
Node* left;
Node* right;
bool is_empty;
string key;
void* val;
}; 
struct Option {
byte data  [500 ];
string error;
bool ok;
}; 
struct strings__Builder {
array_byte buf;
int len;
}; 
struct os__File {
FILE* cfile;
}; 
struct os__FileInfo {
string name;
int size;
}; 
struct os__filetime {
u32 dwLowDateTime;
u32 dwHighDateTime;
}; 
struct os__win32finddata {
u32 dwFileAttributes;
os__filetime ftCreationTime;
os__filetime ftLastAccessTime;
os__filetime ftLastWriteTime;
u32 nFileSizeHigh;
u32 nFileSizeLow;
u32 dwReserved0;
u32 dwReserved1;
u16 cFileName  [260 ];
u16 cAlternateFileName  [14 ];
u32 dwFileType;
u32 dwCreatorType;
u16 wFinderFlags;
}; 
struct time__Time {
int year;
int month;
int day;
int hour;
int minute;
int second;
int uni;
}; 
struct CGen {
os__File out;
string out_path;
array_string typedefs;
array_string type_aliases;
array_string includes;
array_string types;
array_string thread_args;
array_string thread_fns;
array_string consts;
array_string fns;
array_string so_fns;
array_string consts_init;
bool is_user;
array_string lines;
Pass pass;
bool nogen;
string tmp_line;
string cur_line;
string prev_line;
bool is_tmp;
string fn_main;
string stash;
string file;
int line;
bool line_directives;
}; 
struct Fn {
string name;
string mod;
array_Var local_vars;
int var_idx;
array_Var args;
bool is_interface;
int scope_level;
string typ;
bool is_c;
string receiver_typ;
bool is_public;
bool is_method;
bool returns_error;
bool is_decl;
string defer_text;
}; 
struct V {
OS os;
string out_name_c;
array_string files;
string dir;
Table* table;
CGen* cgen;
Preferences* pref;
string lang_dir;
string out_name;
string vroot;
string mod;
}; 
struct Preferences {
BuildMode build_mode;
bool nofmt;
bool is_test;
bool is_script;
bool is_live;
bool is_so;
bool is_prof;
bool translated;
bool is_prod;
bool is_verbose;
bool obfuscate;
bool is_play;
bool is_repl;
bool is_run;
bool show_c_cmd;
bool sanitize;
bool is_debuggable;
bool is_debug;
bool no_auto_free;
string cflags;
}; 
struct ModDepGraphNode {
string name;
array_string deps;
string last_cycle;
}; 
struct ModDepGraph {
bool acyclic;
array_ModDepGraphNode nodes;
}; 
struct DepSet {
array_string items;
}; 
struct Var {
string typ;
string name;
bool is_arg;
bool is_const;
bool is_import_const;
array_Var args;
string attr;
bool is_mut;
bool is_alloc;
bool ptr;
bool ref;
string parent_fn;
string mod;
int line_nr;
AccessMod access_mod;
bool is_global;
bool is_used;
bool is_changed;
int scope_level;
}; 
struct Parser {
string file_path;
string file_name;
string file_platform;
string file_pcguard;
V* v;
Scanner* scanner;
int token_idx;
Token tok;
Token prev_tok;
Token prev_tok2;
string lit;
CGen* cgen;
Table* table;
FileImportTable* import_table;
Pass pass;
OS os;
string mod;
bool inside_const;
Var expr_var;
string assigned_type;
string expected_type;
int tmp_cnt;
bool is_script;
Preferences* pref;
bool builtin_mod;
array_string vh_lines;
bool inside_if_expr;
bool is_struct_init;
int if_expr_cnt;
int for_expr_cnt;
bool ptr_cast;
bool calling_c;
Fn* cur_fn;
bool returns;
string vroot;
bool is_c_struct_init;
bool can_chash;
string attr;
bool v_script;
string var_decl_name;
bool building_v;
bool is_alloc;
string cur_gen_type;
bool is_vweb;
}; 
struct Scanner {
string file_path;
string text;
int pos;
int line_nr;
bool inside_string;
bool dollar_start;
bool dollar_end;
bool debug;
string line_comment;
bool started;
strings__Builder fmt_out;
int fmt_indent;
bool fmt_line_empty;
Token prev_tok;
}; 
struct ScanRes {
Token tok;
string lit;
}; 
struct Table {
array_Type types;
array_Var consts;
map_Fn fns;
array_GenTable generic_fns;
map_int obf_ids;
array_string modules;
array_string imports;
array_FileImportTable file_imports;
array_string flags;
_Atomic 
int fn_cnt;
bool obfuscate;
}; 
struct GenTable {
string fn_name;
array_string types;
}; 
struct FileImportTable {
string module_name;
string file_path;
map_string imports;
}; 
struct Type {
string mod;
string name;
array_Var fields;
array_Fn methods;
string parent;
Fn func;
bool is_c;
bool is_interface;
bool is_enum;
array_string enum_vals;
array_string gen_types;
bool is_placeholder;
}; 

string _STR(const char*, ...);


string _STR_TMP(const char*, ...);

array new_array(int mylen, int cap, int elm_size);
array _make(int len, int cap, int elm_size);
array new_array_from_c_array(int len, int cap, int elm_size, void* c_array);
array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array);
array array_repeat(void* val, int nr_repeats, int elm_size);
void array_sort_with_compare(array* a, void* compare);
void array_insert(array* a, int i, void* val);
void array_prepend(array* a, void* val);
void array_delete(array* a, int idx);
void* array__get(array a, int i);
void* array_first(array a);
void* array_last(array a);
array array_left(array s, int n);
array array_right(array s, int n);
array array_slice(array s, int start, int _end);
void array_set(array* a, int idx, void* val);
void array__push(array* arr, void* val);
void array__push_many(array* arr, void* val, int size);
array array_reverse(array a);
string array_int_str(array_int a);
string array_u64_str(array_u64 a);
void v_array_free(array a);
string array_string_str(array_string a);
string array_byte_hex(array_byte b);
int copy(array_byte dst, array_byte src);
string tos(byte* s, int len);
string tos_clone(byte* s);
string tos2(byte* s);
string string_clone(string a);
string string_replace(string s, string rep, string with);
int string_int(string s);
i32 string_i32(string s);
i64 string_i64(string s);
f32 string_f32(string s);
f64 string_f64(string s);
u32 string_u32(string s);
u64 string_u64(string s);
bool string_eq(string s, string a);
bool string_ne(string s, string a);
bool string_lt(string s, string a);
bool string_le(string s, string a);
bool string_gt(string s, string a);
bool string_ge(string s, string a);
string string_add(string s, string a);
array_string string_split(string s, string delim);
array_string string_split_single(string s, byte delim);
array_string string_split_into_lines(string s);
string string_left(string s, int n);
string string_right(string s, int n);
string string_substr(string s, int start, int end);
int string_index(string s, string p);
int string_index_any(string s, string chars);
int string_last_index(string s, string p);
int string_index_after(string s, string p, int start);
int string_count(string s, string substr);
bool string_contains(string s, string p);
bool string_starts_with(string s, string p);
bool string_ends_with(string s, string p);
string string_to_lower(string s);
string string_to_upper(string s);
string string_find_between(string s, string start, string end);
bool array_string_contains(array_string ar, string val);
bool array_int_contains(array_int ar, int val);
bool is_space(byte c);
bool byte_is_space(byte c);
string string_trim_space(string s);
string string_trim(string s, byte c);
string string_trim_left(string s, string cutset);
string string_trim_right(string s, string cutset);
int compare_strings(string* a, string* b);
int compare_strings_by_len(string* a, string* b);
int compare_lower_strings(string* a, string* b);
void array_string_sort(array_string* s);
void array_string_sort_ignore_case(array_string* s);
void array_string_sort_by_len(array_string* s);
ustring string_ustring(string s);
ustring string_ustring_tmp(string s);
string ustring_substr(ustring u, int _start, int _end);
string ustring_left(ustring u, int pos);
string ustring_right(ustring u, int pos);
byte string_at(string s, int idx);
string ustring_at(ustring u, int idx);
void v_ustring_free(ustring u);
int abs(int a);
bool byte_is_digit(byte c);
bool byte_is_hex_digit(byte c);
bool byte_is_oct_digit(byte c);
bool byte_is_letter(byte c);
void v_string_free(string s);
string string_all_before(string s, string dot);
string string_all_before_last(string s, string dot);
string string_all_after(string s, string dot);
string array_string_join(array_string a, string del);
string array_string_join_lines(array_string s);
string string_reverse(string s);
string string_limit(string s, int max);
bool byte_is_white(byte c);
int string_hash(string s);
array_byte string_bytes(string s);
void v_exit(int code);
bool isnil(void* v);
void on_panic(int (*f)( int  /*FFF*/ ));
void print_backtrace();
void _panic_debug(int line_no, string file, string mod, string fn_name, string s);
void v_panic(string s);
void println(string s);
void eprintln(string s);
void v_print(string s);
byte* v_malloc(int n);
byte* v_calloc(int n);
void v_free(void* ptr);
void* memdup(void* src, int sz);
string double_str(double d);
string f64_str(f64 d);
string f32_str(f32 d);
string ptr_str(void* ptr);
bool f64_eq(f64 a, f64 b);
string int_str(int nn);
string u8_str(u8 nn);
string i64_str(i64 nn);
string bool_str(bool b);
string int_hex(int n);
string i64_hex(i64 n);
bool array_byte_contains(array_byte a, byte val);
string rune_str(rune c);
string byte_str(byte c);
bool byte_is_capital(byte c);
array_byte array_byte_clone(array_byte b);
int utf8_char_len(byte b);
string utf32_to_str(u32 code);
string utf32_to_str_no_malloc(u32 code, void* buf);
int string_utf32_code(string _rune);
u16* string_to_wide(string _str);
string string_from_wide(u16* _wstr);
string string_from_wide2(u16* _wstr, int len);
map new_map(int cap, int elm_size);
map new_map_init(int cap, int elm_size, string* keys, void* vals);
Node* new_node(string key, void* val, int element_size);
void map_insert(map* m, Node* n, string key, void* val);
bool Node_find(Node* n, string key, void* out, int element_size);
bool Node_find2(Node* n, string key, int element_size);
void map__set(map* m, string key, void* val);
void map_preorder_keys(map* m, Node* node);
array_string map_keys(map* m);
bool map_get(map m, string key, void* out);
void Node_delete(Node* n, string key, int element_size);
void map_delete(map* m, string key);
bool map_exists(map m, string key);
bool map__exists(map m, string key);
void v_map_print(map m);
void v_map_free(map m);
string map_string_str(map_string m);
Option opt_ok(void* data, int size);
Option v_error(string s);
strings__Builder strings__new_builder(int initial_size);
void strings__Builder_write(strings__Builder* b, string s);
void strings__Builder_writeln(strings__Builder* b, string s);
string strings__Builder_str(strings__Builder b);
void strings__Builder_cut(strings__Builder* b, int n);
void strings__Builder_free(strings__Builder* b);
string strings__repeat(byte c, int n);
void os__todo_remove();
array_string os__init_os_args(int argc, byteptr* argv);
array_string os__parse_windows_cmd_line(byte* cmd);
Option_string os__read_file(string path);
int os__file_size(string path);
void os__mv(string old, string new);
array_string os__read_lines(string path);
array_ustring os__read_ulines(string path);
Option_os__File os__open(string path);
Option_os__File os__create(string path);
Option_os__File os__open_append(string path);
void os__File_write(os__File f, string s);
void os__File_write_bytes(os__File f, void* data, int size);
void os__File_write_bytes_at(os__File f, void* data, int size, int pos);
void os__File_writeln(os__File f, string s);
void os__File_flush(os__File f);
void os__File_close(os__File f);
int os__system(string cmd);
FILE* os__popen(string path);
string os__exec(string _cmd);
string os__getenv(string key);
int os__setenv(string name, string value, bool overwrite);
int os__unsetenv(string name);
bool os__file_exists(string _path);
bool os__dir_exists(string path);
void os__mkdir(string path);
void os__rm(string path);
void os__rmdir(string path);
void os__print_c_errno();
string os__ext(string path);
string os__dir(string path);
string os__path_sans_ext(string path);
string os__basedir(string path);
string os__filename(string path);
string os__get_line();
string os__get_raw_line();
array_string os__get_lines();
string os__get_lines_joined();
string os__user_os();
string os__home_dir();
void os__write_file(string path, string text);
void os__clear();
void os__on_segfault(void* f);
string os__executable();
bool os__is_dir(string path);
void os__chdir(string path);
string os__getwd();
array_string os__ls(string path);
void os__signal(int signum, void* handler);
int os__fork();
int os__wait();
int os__file_last_mod_unix(string path);
void os__log(string s);
void os__flush_stdout();
void os__print_backtrace();
string os__get_error_msg(int code);
f64 math__abs(f64 a);
f64 math__acos(f64 a);
f64 math__asin(f64 a);
f64 math__atan(f64 a);
f64 math__atan2(f64 a, f64 b);
f64 math__cbrt(f64 a);
int math__ceil(f64 a);
f64 math__cos(f64 a);
f64 math__cosh(f64 a);
f64 math__degrees(f64 radians);
f64 math__exp(f64 a);
array_int math__digits(int _n, int base);
f64 math__erf(f64 a);
f64 math__erfc(f64 a);
f64 math__exp2(f64 a);
int math__recursive_product(int n, int* current_number_ptr);
i64 math__factorial(int n);
f64 math__floor(f64 a);
f64 math__fmod(f64 a, f64 b);
f64 math__gamma(f64 a);
i64 math__gcd(i64 a, i64 b);
f64 math__hypot(f64 a, f64 b);
i64 math__lcm(i64 a, i64 b);
f64 math__log(f64 a);
f64 math__log2(f64 a);
f64 math__log10(f64 a);
f64 math__log_gamma(f64 a);
f64 math__log_n(f64 a, f64 b);
f64 math__max(f64 a, f64 b);
f64 math__min(f64 a, f64 b);
f64 math__pow(f64 a, f64 b);
f64 math__radians(f64 degrees);
f64 math__round(f64 f);
f64 math__sin(f64 a);
f64 math__sinh(f64 a);
f64 math__sqrt(f64 a);
f64 math__tan(f64 a);
f64 math__tanh(f64 a);
f64 math__trunc(f64 a);
void rand__seed(int s);
int rand__next(int max);
string vweb_dot_tmpl__compile_template(string path);
time__Time time__now();
time__Time time__random();
time__Time time__unix(int abs);
time__Time time__convert_ctime(struct /*TM*/ tm t);
string time__Time_format_ss(time__Time t);
string time__Time_format(time__Time t);
string time__Time_smonth(time__Time t);
string time__Time_hhmm(time__Time t);
string time__Time_hhmm12(time__Time t);
string time__Time_hhmmss(time__Time t);
string time__Time_ymmdd(time__Time t);
string time__Time_md(time__Time t);
string time__Time_clean(time__Time t);
string time__Time_clean12(time__Time t);
time__Time time__parse(string s);
time__Time time__new_time(time__Time t);
int time__Time_calc_unix(time__Time* t);
time__Time time__Time_add_seconds(time__Time t, int seconds);
int time__since(time__Time t);
string time__Time_relative(time__Time t);
int time__day_of_week(int y, int m, int d);
int time__Time_day_of_week(time__Time t);
string time__Time_weekday_str(time__Time t);
i64 time__ticks();
void time__sleep(int seconds);
void time__usleep(int n);
void time__sleep_ms(int n);
bool time__is_leap_year(int year);
Option_int time__days_in_month(int month, int year);
CGen* new_cgen(string out_name_c);
void CGen_genln(CGen* g, string s);
void CGen_gen(CGen* g, string s);
void CGen_resetln(CGen* g, string s);
void CGen_save(CGen* g);
void CGen_start_tmp(CGen* g);
string CGen_end_tmp(CGen* g);
int CGen_add_placeholder(CGen* g);
void CGen_set_placeholder(CGen* g, int pos, string val);
int CGen_add_placeholder2(CGen* g);
void CGen_set_placeholder2(CGen* g, int pos, string val);
void CGen_insert_before(CGen* g, string val);
void CGen_register_thread_fn(CGen* g, string wrapper_name, string wrapper_text, string struct_text);
string V_prof_counters(V* c);
string Parser_print_prof_counters(Parser* p);
void Parser_gen_type(Parser* p, string s);
void Parser_gen_typedef(Parser* p, string s);
void Parser_gen_type_alias(Parser* p, string s);
void CGen_add_to_main(CGen* g, string s);
void build_thirdparty_obj_file(string flag);
void Parser_comp_time(Parser* p);
void Parser_chash(Parser* p);
void Parser_comptime_method_call(Parser* p, Type typ);
Var Fn_find_var(Fn* f, string name);
void Fn_open_scope(Fn* f);
void Fn_mark_var_used(Fn* f, Var v);
void Fn_mark_var_changed(Fn* f, Var v);
bool Fn_known_var(Fn* f, string name);
void Fn_register_var(Fn* f, Var v);
void Fn_clear_vars(Fn* f);
bool Parser_is_sig(Parser* p);
Fn* new_fn(string mod, bool is_public);
void Parser_fn_decl(Parser* p);
void Parser_check_unused_variables(Parser* p);
void Parser_async_fn_call(Parser* p, Fn f, int method_ph, string receiver_var, string receiver_type);
void Parser_fn_call(Parser* p, Fn f, int method_ph, string receiver_var, string receiver_type);
void Parser_fn_args(Parser* p, Fn* f);
Fn* Parser_fn_call_args(Parser* p, Fn* f);
string Fn_typ_str(Fn f);
string Fn_str_args(Fn* f, Table* table);
void Parser_gen_json_for_type(Parser* p, Type typ);
bool is_js_prim(string typ);
string Parser_decode_array(Parser* p, string typ);
string js_enc_name(string typ);
string js_dec_name(string typ);
string Parser_encode_array(Parser* p, string typ);
string modules_path();
void V_compile(V* v);
void V_cc_windows_cross(V* c);
void V_cc(V* v);
array_string V_v_files_from_dir(V* v, string dir);
void V_add_v_files_to_compile(V* v);
string get_arg(string joined_args, string arg, string def);
string V_module_path(V* v, string mod);
void V_log(V* v, string s);
V* new_v(array_string args);
array_string run_repl();
array_string env_vflags_and_os_args();
void update_v();
void DepSet_add(DepSet* dset, string item);
DepSet DepSet_diff(DepSet* dset, DepSet otherset);
int DepSet_size(DepSet* dset);
ModDepGraph* new_mod_dep_graph();
void ModDepGraph_from_import_tables(ModDepGraph* graph, array_FileImportTable import_tables);
void ModDepGraph_add(ModDepGraph* graph, string mod, array_string deps);
ModDepGraph* ModDepGraph_resolve(ModDepGraph* graph);
array_string ModDepGraph_imports(ModDepGraph* graph);
ModDepGraphNode ModDepGraph_last_node(ModDepGraph* graph);
string ModDepGraph_last_cycle(ModDepGraph* graph);
void ModDepGraph_display(ModDepGraph* graph);
string V_find_module_path(V* v, string mod);
void cc_msvc(V* v);
void build_thirdparty_obj_file_with_msvc(string flag);
string platform_postfix_to_ifdefguard(string name);
Parser V_new_parser(V* v, string path, Pass pass);
void Parser_next(Parser* p);
void Parser_log(Parser* p, string s);
void Parser_parse(Parser* p);
void Parser_imports(Parser* p);
void Parser_import_statement(Parser* p);
void Parser_const_decl(Parser* p);
void Parser_type_decl(Parser* p);
Fn* Parser_interface_method(Parser* p, string field_name, string receiver);
void Parser_struct_decl(Parser* p);
void Parser_enum_decl(Parser* p, string _enum_name);
string Parser_check_name(Parser* p);
string Parser_check_string(Parser* p);
string Parser_strtok(Parser* p);
void Parser_check_space(Parser* p, Token expected);
void Parser_check(Parser* p, Token expected);
void Parser_error(Parser* p, string s);
bool Parser_first_pass(Parser* p);
string Parser_get_type(Parser* p);
void Parser_print_tok(Parser* p);
string Parser_statements(Parser* p);
string Parser_statements_no_rcbr(Parser* p);
void Parser_close_scope(Parser* p);
void Parser_genln(Parser* p, string s);
void Parser_gen(Parser* p, string s);
void Parser_vh_genln(Parser* p, string s);
string Parser_statement(Parser* p, bool add_semi);
void Parser_assign_statement(Parser* p, Var v, int ph, bool is_map);
void Parser_var_decl(Parser* p);
string Parser_bool_expression(Parser* p);
string Parser_bterm(Parser* p);
string Parser_name_expr(Parser* p);
string Parser_var_expr(Parser* p, Var v);
bool Parser_fileis(Parser* p, string s);
string Parser_dot(Parser* p, string str_typ, int method_ph);
string Parser_index_expr(Parser* p, string typ, int fn_ph);
string Parser_expression(Parser* p);
string Parser_term(Parser* p);
string Parser_unary(Parser* p);
string Parser_factor(Parser* p);
string Parser_assoc(Parser* p);
void Parser_char_expr(Parser* p);
string format_str(string str);
void Parser_string_expr(Parser* p);
string Parser_map_init(Parser* p);
string Parser_array_init(Parser* p);
string Parser_struct_init(Parser* p, string typ, bool is_c_struct_init);
string Parser_cast(Parser* p, string typ);
string Parser_get_tmp(Parser* p);
int Parser_get_tmp_counter(Parser* p);
string os_name_to_ifdef(string name);
string Parser_if_st(Parser* p, bool is_expr, int elif_depth);
void Parser_for_st(Parser* p);
void Parser_switch_statement(Parser* p);
void Parser_assert_statement(Parser* p);
void Parser_return_st(Parser* p);
string prepend_mod(string mod, string name);
string Parser_prepend_mod(Parser* p, string name);
void Parser_go_statement(Parser* p);
void Parser_register_var(Parser* p, Var v);
string Parser_js_decode(Parser* p);
void Parser_attribute(Parser* p);
void Parser_defer_st(Parser* p);
Scanner* new_scanner(string file_path);
ScanRes scan_res(Token tok, string lit);
string Scanner_ident_name(Scanner* s);
string Scanner_ident_hex_number(Scanner* s);
string Scanner_ident_oct_number(Scanner* s);
string Scanner_ident_dec_number(Scanner* s);
string Scanner_ident_number(Scanner* s);
bool Scanner_has_gone_over_line_end(Scanner s);
void Scanner_skip_whitespace(Scanner* s);
ScanRes Scanner_scan(Scanner* s);
void Scanner_error(Scanner* s, string msg);
string Scanner_ident_string(Scanner* s);
string Scanner_ident_char(Scanner* s);
Token Scanner_peek(Scanner* s);
bool Scanner_expect(Scanner* s, string want, int start_pos);
void Scanner_debug_tokens(Scanner* s);
bool is_name_char(byte c);
bool is_nl(byte c);
int Scanner_get_opening_bracket(Scanner* s);
void Scanner_create_type_string(Scanner* s, Type T, string name);
bool contains_capital(string s);
bool good_type_name(string s);
string Type_str(Type t);
string Fn_str(Fn f);
string Table_debug_fns(Table* t);
bool is_number_type(string typ);
bool is_float_type(string typ);
bool is_primitive_type(string typ);
Table* new_table(bool obfuscate);
string Table_var_cgen_name(Table* t, string name);
void Table_register_module(Table* t, string mod);
void Parser_register_array(Parser* p, string typ);
void Parser_register_map(Parser* p, string typ);
bool Table_known_mod(Table* table, string mod);
void Table_register_const(Table* t, string name, string typ, string mod, bool is_imported);
void Parser_register_global(Parser* p, string name, string typ);
void Table_register_fn(Table* t, Fn new_fn);
bool Table_known_type(Table* table, string typ);
Fn Table_find_fn(Table* t, string name);
bool Table_known_fn(Table* t, string name);
bool Table_known_const(Table* t, string name);
void Table_register_type(Table* t, string typ);
void Parser_register_type_with_parent(Parser* p, string strtyp, string parent);
void Table_register_type_with_parent(Table* t, string typ, string parent);
void Table_register_type2(Table* t, Type typ);
void Type_add_field(Type* t, string name, string typ, bool is_mut, string attr, AccessMod access_mod);
bool Type_has_field(Type* t, string name);
bool Type_has_enum_val(Type* t, string name);
Var Type_find_field(Type* t, string name);
bool Table_type_has_field(Table* table, Type* typ, string name);
Var Table_find_field(Table* table, Type* typ, string name);
void Type_add_method(Type* t, Fn f);
bool Type_has_method(Type* t, string name);
bool Table_type_has_method(Table* table, Type* typ, string name);
Fn Table_find_method(Table* table, Type* typ, string name);
Fn Type_find_method(Type* t, string name);
Type* Parser_find_type(Parser* p, string name);
Type* Table_find_type(Table* t, string name);
bool Parser__check_types(Parser* p, string got, string expected, bool throw);
bool Parser_check_types(Parser* p, string got, string expected);
bool Parser_check_types_no_throw(Parser* p, string got, string expected);
bool Parser_satisfies_interface(Parser* p, string interface_name, string _typ, bool throw);
string type_default(string typ);
bool Table_is_interface(Table* t, string name);
bool Table_main_exists(Table* t);
Var Table_find_const(Table* t, string name);
string Table_cgen_name(Table* table, Fn* f);
string Table_cgen_name_type_pair(Table* table, string name, string typ);
bool is_valid_int_const(string val, string typ);
void Table_register_generic_fn(Table* t, string fn_name);
array_string Table_fn_gen_types(Table* t, string fn_name);
void Table_register_generic_fn_type(Table* t, string fn_name, string typ);
string Parser_typ_to_fmt(Parser* p, string typ, int level);
bool is_compile_time_const(string s);
string Table_qualify_module(Table* table, string mod, string file_path);
FileImportTable* new_file_import_table(string file_path);
bool FileImportTable_known_import(FileImportTable* fit, string mod);
void FileImportTable_register_import(FileImportTable* fit, string mod);
void FileImportTable_register_alias(FileImportTable* fit, string alias, string mod);
bool FileImportTable_known_alias(FileImportTable* fit, string alias);
bool FileImportTable_is_aliased(FileImportTable* fit, string mod);
string FileImportTable_resolve_alias(FileImportTable* fit, string alias);
map_int build_keys();
array_string build_token_str();
Token key_to_token(string key);
bool is_key(string key);
string Token_str(Token t);
bool Token_is_decl(Token t);
bool Token_is_assign(Token t);
bool array_Token_contains(array_Token t, Token val);
void Scanner_fgen(Scanner* scanner, string s);
void Scanner_fgenln(Scanner* scanner, string s);
void Parser_fgen(Parser* p, string s);
void Parser_fspace(Parser* p);
void Parser_fgenln(Parser* p, string s);
Token Parser_peek(Parser* p);
void Parser_fmt_inc(Parser* p);
void Parser_fmt_dec(Parser* p);
array_int g_ustring_runes; // global
i64 total_m =  0; // global
#define builtin__CP_UTF8  65001
#define os__SUCCESS  0
#define os__ERROR_INSUFFICIENT_BUFFER  130
#define os__FILE_SHARE_READ  1
#define os__FILE_SHARE_WRITE  2
#define os__FILE_SHARE_DELETE  4
#define os__FILE_NOTIFY_CHANGE_FILE_NAME  1
#define os__FILE_NOTIFY_CHANGE_DIR_NAME  2
#define os__FILE_NOTIFY_CHANGE_ATTRIBUTES  4
#define os__FILE_NOTIFY_CHANGE_SIZE  8
#define os__FILE_NOTIFY_CHANGE_LAST_WRITE  16
#define os__FILE_NOTIFY_CHANGE_LAST_ACCESS  32
#define os__FILE_NOTIFY_CHANGE_CREATION  64
#define os__FILE_NOTIFY_CHANGE_SECURITY  128
#define os__FILE_ACTION_ADDED  1
#define os__FILE_ACTION_REMOVED  2
#define os__FILE_ACTION_MODIFIED  3
#define os__FILE_ACTION_RENAMED_OLD_NAME  4
#define os__FILE_ACTION_RENAMED_NEW_NAME  5
int os__FILE_ATTR_READONLY;
int os__FILE_ATTR_HIDDEN;
int os__FILE_ATTR_SYSTEM;
int os__FILE_ATTR_DIRECTORY;
int os__FILE_ATTR_ARCHIVE;
int os__FILE_ATTR_DEVICE;
int os__FILE_ATTR_NORMAL;
int os__FILE_ATTR_TEMPORARY;
int os__FILE_ATTR_SPARSE_FILE;
int os__FILE_ATTR_REPARSE_POINT;
int os__FILE_ATTR_COMPRESSED;
int os__FILE_ATTR_OFFLINE;
int os__FILE_ATTR_NOT_CONTENT_INDEXED;
int os__FILE_ATTR_ENCRYPTED;
int os__FILE_ATTR_INTEGRITY_STREAM;
int os__FILE_ATTR_VIRTUAL;
int os__FILE_ATTR_NO_SCRUB_DATA;
int os__FILE_TYPE_DISK;
int os__FILE_TYPE_CHAR;
int os__FILE_TYPE_PIPE;
int os__FILE_TYPE_UNKNOWN;
int os__FILE_INVALID_FILE_ID;
#define os__O_RDONLY  1
#define os__O_WRONLY  2
#define os__O_RDWR  3
#define os__O_APPEND  8
#define os__O_CREATE  16
#define os__O_EXCL  32
#define os__O_SYNC  64
#define os__O_TRUNC  128
int os__S_IFMT;
int os__S_IFDIR;
int os__INVALID_HANDLE_VALUE;
int os__STD_INPUT_HANDLE;
int os__STD_OUTPUT_HANDLE;
int os__STD_ERROR_HANDLE;
int os__ENABLE_ECHO_INPUT;
int os__ENABLE_EXTENDED_FLAGS;
int os__ENABLE_INSERT_MODE;
int os__ENABLE_LINE_INPUT;
int os__ENABLE_MOUSE_INPUT;
int os__ENABLE_PROCESSED_INPUT;
int os__ENABLE_QUICK_EDIT_MODE;
int os__ENABLE_WINDOW_INPUT;
int os__ENABLE_VIRTUAL_TERMINAL_INPUT;
int os__ENABLE_PROCESSED_OUTPUT;
int os__ENABLE_WRAP_AT_EOL_OUTPUT;
int os__ENABLE_VIRTUAL_TERMINAL_PROCESSING;
int os__DISABLE_NEWLINE_AUTO_RETURN;
int os__ENABLE_LVB_GRID_WORLDWIDE;
array_string os__args;
#define os__MAX_PATH  4096
string os__PathSeparator;
#define math__E  2.71828182845904523536028747135266249775724709369995957496696763
#define math__Pi  3.14159265358979323846264338327950288419716939937510582097494459
#define math__Phi  1.61803398874989484820458683436563811772030917980576286213544862
#define math__Tau  6.28318530717958647692528676655900576839433879875021164194988918
#define math__Sqrt2  1.41421356237309504880168872420969807856967187537694807317667974
#define math__SqrtE  1.64872127070012814684865078781416357165377610071014801157507931
#define math__SqrtPi  1.77245385090551602729816748334114518279754945612238712821380779
#define math__SqrtTau  2.50662827463100050241576528481104525300698674060993831662992357
#define math__SqrtPhi  1.27201964951406896425242246173749149171560804184009624861664038
#define math__Ln2  0.693147180559945309417232121458176568075500134360255254120680009
f32 math__Log2E;
#define math__Ln10  2.30258509299404568401799145468436420760110148862877297603332790
f32 math__Log10E;
int math__MaxI8;
int math__MinI8;
int math__MaxI16;
int math__MinI16;
int math__MaxI32;
int math__MinI32;
int math__MaxU8;
int math__MaxU16;
int math__MaxU32;
int math__MaxU64;
#define vweb_dot_tmpl__STR_START  tos2((byte*)"sb.write(\'")
#define vweb_dot_tmpl__STR_END  tos2((byte*)"\' ) ")
array_int time__MonthDays;
i64 time__absoluteZeroYear;
#define time__secondsPerMinute  60
int time__secondsPerHour;
int time__secondsPerDay;
int time__secondsPerWeek;
int time__daysPer400Years;
int time__daysPer100Years;
int time__daysPer4Years;
array_int time__daysBefore;
string time__Months;
string time__Days;
#define main__MaxLocalVars  50
string main__Version;
#define main__BuildMode_default_mode 0
#define main__BuildMode_embed_vlib 1
#define main__BuildMode_build 2
array_string main__SupportedPlatforms;
string main__ModPath;
#define main__OS_mac 0
#define main__OS_linux 1
#define main__OS_windows 2
#define main__OS_freebsd 3
#define main__OS_openbsd 4
#define main__OS_netbsd 5
#define main__OS_dragonfly 6
#define main__OS_msvc 7
#define main__Pass_imports 0
#define main__Pass_decl 1
#define main__Pass_main 2
string main__HelpText;
Fn* main__EmptyFn;
Fn* main__MainFn;
#define main__MaxModuleDepth  4
string main__and_or_error;
#define main__AccessMod_private 0
#define main__AccessMod_private_mut 1
#define main__AccessMod_public 2
#define main__AccessMod_public_mut 3
#define main__AccessMod_public_mut_mut 4
array_string main__CReserved;
array_string main__number_types;
array_string main__float_types;
#define main__Token_eof 0
#define main__Token_name 1
#define main__Token_number 2
#define main__Token_str 3
#define main__Token_str_inter 4
#define main__Token_chartoken 5
#define main__Token_plus 6
#define main__Token_minus 7
#define main__Token_mul 8
#define main__Token_div 9
#define main__Token_mod 10
#define main__Token_xor 11
#define main__Token_pipe 12
#define main__Token_inc 13
#define main__Token_dec 14
#define main__Token_and 15
#define main__Token_logical_or 16
#define main__Token_not 17
#define main__Token_bit_not 18
#define main__Token_question 19
#define main__Token_comma 20
#define main__Token_semicolon 21
#define main__Token_colon 22
#define main__Token_arrow 23
#define main__Token_amp 24
#define main__Token_hash 25
#define main__Token_dollar 26
#define main__Token_left_shift 27
#define main__Token_righ_shift 28
#define main__Token_assign 29
#define main__Token_decl_assign 30
#define main__Token_plus_assign 31
#define main__Token_minus_assign 32
#define main__Token_div_assign 33
#define main__Token_mult_assign 34
#define main__Token_xor_assign 35
#define main__Token_mod_assign 36
#define main__Token_or_assign 37
#define main__Token_and_assign 38
#define main__Token_righ_shift_assign 39
#define main__Token_left_shift_assign 40
#define main__Token_lcbr 41
#define main__Token_rcbr 42
#define main__Token_lpar 43
#define main__Token_rpar 44
#define main__Token_lsbr 45
#define main__Token_rsbr 46
#define main__Token_eq 47
#define main__Token_ne 48
#define main__Token_gt 49
#define main__Token_lt 50
#define main__Token_ge 51
#define main__Token_le 52
#define main__Token_nl 53
#define main__Token_dot 54
#define main__Token_dotdot 55
#define main__Token_keyword_beg 56
#define main__Token_key_as 57
#define main__Token_key_assert 58
#define main__Token_key_atomic 59
#define main__Token_key_break 60
#define main__Token_key_case 61
#define main__Token_key_const 62
#define main__Token_key_continue 63
#define main__Token_key_default 64
#define main__Token_key_defer 65
#define main__Token_key_else 66
#define main__Token_key_embed 67
#define main__Token_key_enum 68
#define main__Token_key_false 69
#define main__Token_key_for 70
#define main__Token_func 71
#define main__Token_key_global 72
#define main__Token_key_go 73
#define main__Token_key_goto 74
#define main__Token_key_if 75
#define main__Token_key_import 76
#define main__Token_key_import_const 77
#define main__Token_key_in 78
#define main__Token_key_interface 79
#define main__Token_key_match 80
#define main__Token_key_module 81
#define main__Token_key_mut 82
#define main__Token_key_return 83
#define main__Token_key_sizeof 84
#define main__Token_key_struct 85
#define main__Token_key_switch 86
#define main__Token_key_true 87
#define main__Token_key_type 88
#define main__Token_key_orelse 89
#define main__Token_key_union 90
#define main__Token_key_pub 91
#define main__Token_key_static 92
#define main__Token_keyword_end 93
#define main__NrTokens  140
array_string main__TokenStr;
map_int main__KEYWORDS;
array_Token main__AssignTokens;


 array new_array(int mylen, int cap, int elm_size) {
 
array arr= (array) { .len =  mylen , .cap =  cap , .element_size =  elm_size , .data =  v_malloc ( cap * elm_size ) } ;
 
return  arr ;
 
 
 }
 array _make(int len, int cap, int elm_size) {
 
return  new_array ( len , cap , elm_size ) ;
 
 
 }
 array new_array_from_c_array(int len, int cap, int elm_size, void* c_array) {
 
array arr= (array) { .len =  len , .cap =  cap , .element_size =  elm_size , .data =  v_malloc ( cap * elm_size ) } ;
 
 memcpy ( arr .data ,  c_array ,  len * elm_size ) ;
 
return  arr ;
 
 
 }
 array new_array_from_c_array_no_alloc(int len, int cap, int elm_size, void* c_array) {
 
array arr= (array) { .len =  len , .cap =  cap , .element_size =  elm_size , .data =  c_array } ;
 
return  arr ;
 
 
 }
 array array_repeat(void* val, int nr_repeats, int elm_size) {
 
array arr= (array) { .len =  nr_repeats , .cap =  nr_repeats , .element_size =  elm_size , .data =  v_malloc ( nr_repeats * elm_size ) } ;
 
 for (
int i= 0  ;  i < nr_repeats  ;  i ++ ) { 
 
 
 memcpy ((byte*) arr .data + i * elm_size ,  val ,  elm_size ) ;
 
 }
 ;
 
return  arr ;
 
 
 }
 void array_sort_with_compare(array* a, void* compare) {
 
 qsort ( a ->data ,  a ->len ,  a ->element_size ,  compare ) ;
 
 
 }
 void array_insert(array* a, int i, void* val) {
 
 if ( i >= a ->len ) {
 
 v_panic ( tos2((byte*)"array.insert: index larger than length") ) ;
 
 return ;
 
 }
 ;
 
 array__push( a , val ) ;
 
int size= a ->element_size ;
 
 memmove ((byte*) a ->data + ( i + 1 ) * size , (byte*) a ->data + i * size ,  ( a ->len - i ) * size ) ;
 
 array_set( a , i , val ) ;
 
 
 }
 void array_prepend(array* a, void* val) {
 
 array_insert( a , 0 , val ) ;
 
 
 }
 void array_delete(array* a, int idx) {
 
int size= a ->element_size ;
 
 memmove ((byte*) a ->data + idx * size , (byte*) a ->data + ( idx + 1 ) * size ,  ( a ->len - idx ) * size ) ;
 
 a ->len -- ;
 
 a ->cap -- ;
 
 
 }
 void* array__get(array a, int i) {
 
 if ( i < 0  ||  i >= a .len ) {
 
 v_panic ( _STR("array index out of range: %d/%d", i, a .len) ) ;
 
 }
 ;
 
return (byte*) a .data + i * a .element_size ;
 
 
 }
 void* array_first(array a) {
 
 if ( a .len == 0 ) {
 
 v_panic ( tos2((byte*)"array.first: empty array") ) ;
 
 }
 ;
 
return (byte*) a .data + 0 ;
 
 
 }
 void* array_last(array a) {
 
 if ( a .len == 0 ) {
 
 v_panic ( tos2((byte*)"array.last: empty array") ) ;
 
 }
 ;
 
return (byte*) a .data + ( a .len - 1 ) * a .element_size ;
 
 
 }
 array array_left(array s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  array_slice( s , 0 , n ) ;
 
 
 }
 array array_right(array s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  array_slice( s , n , s .len ) ;
 
 
 }
 array array_slice(array s, int start, int _end) {
 
int end= _end ;
 
 if ( start > end ) {
 
 v_panic ( _STR("invalid slice index: %d > %d", start, end) ) ;
 
 }
 ;
 
 if ( end > s .len ) {
 
 v_panic ( _STR("runtime error: slice bounds out of range (%d >= %d)", end, s .len) ) ;
 
 }
 ;
 
 if ( start < 0 ) {
 
 v_panic ( _STR("runtime error: slice bounds out of range (%d < 0)", start) ) ;
 
 }
 ;
 
int l= end - start ;
 
array res= (array) { .element_size =  s .element_size , .data = (byte*) s .data + start * s .element_size , .len =  l , .cap =  l } ;
 
return  res ;
 
 
 }
 void array_set(array* a, int idx, void* val) {
 
 if ( idx < 0  ||  idx >= a ->len ) {
 
 v_panic ( _STR("array index out of range: %d / %d", idx, a ->len) ) ;
 
 }
 ;
 
 memcpy ((byte*) a ->data + a ->element_size * idx ,  val ,  a ->element_size ) ;
 
 
 }
 void array__push(array* arr, void* val) {
 
 if ( arr ->len >= arr ->cap - 1 ) {
 
int cap= ( arr ->len + 1 ) * 2 ;
 
 if ( arr ->cap == 0 ) {
 
 arr ->data  =  v_malloc ( cap * arr ->element_size ) ;
 
 }
  else { 
 
 arr ->data  =  realloc ( arr ->data ,  cap * arr ->element_size ) ;
 
 }
 ;
 
 arr ->cap  =  cap ;
 
 }
 ;
 
 memcpy ((byte*) arr ->data + arr ->element_size * arr ->len ,  val ,  arr ->element_size ) ;
 
 arr ->len ++ ;
 
 
 }
 void array__push_many(array* arr, void* val, int size) {
 
 if ( arr ->len >= arr ->cap - size ) {
 
int cap= ( arr ->len + size ) * 2 ;
 
 if ( arr ->cap == 0 ) {
 
 arr ->data  =  v_malloc ( cap * arr ->element_size ) ;
 
 }
  else { 
 
 arr ->data  =  realloc ( arr ->data ,  cap * arr ->element_size ) ;
 
 }
 ;
 
 arr ->cap  =  cap ;
 
 }
 ;
 
 memcpy ((byte*) arr ->data + arr ->element_size * arr ->len ,  val ,  arr ->element_size * size ) ;
 
 arr ->len  +=  size ;
 
 
 }
 array array_reverse(array a) {
 
array arr= (array) { .len =  a .len , .cap =  a .cap , .element_size =  a .element_size , .data =  v_malloc ( a .cap * a .element_size ) } ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
 memcpy ((byte*) arr .data + i * arr .element_size ,  & /*vvar*/  ( *(void**) array__get( a , a .len - 1 - i) ) ,  arr .element_size ) ;
 
 }
 ;
 
return  arr ;
 
 
 }
 string array_int_str(array_int a) {
 
string res= tos2((byte*)"[") ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
int val= ( *(int*) array__get( a , i) ) ;
 
 res = string_add(res,  _STR("%d", val) ) ;
 
 if ( i < a .len - 1 ) {
 
 res = string_add(res,  tos2((byte*)", ") ) ;
 
 }
 ;
 
 }
 ;
 
 res = string_add(res,  tos2((byte*)"]") ) ;
 
return  res ;
 
 
 }
 string array_u64_str(array_u64 a) {
 
string res= tos2((byte*)"[") ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
u64 val= ( *(u64*) array__get( a , i) ) ;
 
 res = string_add(res,  _STR("%lld", val) ) ;
 
 if ( i < a .len - 1 ) {
 
 res = string_add(res,  tos2((byte*)", ") ) ;
 
 }
 ;
 
 }
 ;
 
 res = string_add(res,  tos2((byte*)"]") ) ;
 
return  res ;
 
 
 }
 void v_array_free(array a) {
 
 free ( a .data ) ;
 
 
 }
 string array_string_str(array_string a) {
 
string res= tos2((byte*)"[") ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
string val= ( *(string*) array__get( a , i) ) ;
 
 res = string_add(res,  _STR("\"%.*s\"", val.len, val.str) ) ;
 
 if ( i < a .len - 1 ) {
 
 res = string_add(res,  tos2((byte*)", ") ) ;
 
 }
 ;
 
 }
 ;
 
 res = string_add(res,  tos2((byte*)"]") ) ;
 
return  res ;
 
 
 }
 string array_byte_hex(array_byte b) {
 
byte* hex= v_malloc ( b .len * 2 + 1 ) ;
 
byte* ptr= & /*vvar*/  hex [/*ptr*/ 0 ]/*rbyte 1*/ ;
 
 for (
int i= 0  ;  i < b .len  ;  i ++ ) { 
 
 
 ptr  +=  sprintf ( ptr ,  "%02x" ,  ( *(byte*) array__get( b , i) ) ) ;
 
 }
 ;
 
return  (tos2( hex ) ) ;
 
 
 }
 int copy(array_byte dst, array_byte src) {
 
 if ( dst .len > 0  &&  src .len > 0 ) {
 
int min= ( dst .len < src .len ) ? ( dst .len ) : ( src .len ) ;
 
 memcpy ( dst .data ,  array_left( src , min ) .data ,  dst .element_size * min ) ;
 
return  min ;
 
 }
 ;
 
return  0 ;
 
 
 }
 void todo() {
 
 
 }
 string tos(byte* s, int len) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2((byte*)"tos(): nil string") ) ;
 
 }
 ;
 
return  (string) { .str =  s , .len =  len } ;
 
 
 }
 string tos_clone(byte* s) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2((byte*)"tos: nil string") ) ;
 
return  (string) { .str = 0 , .len = 0 } ;
 
 }
 ;
 
int len= strlen ( s ) ;
 
string res= tos ( s , len ) ;
 
return  string_clone( res ) ;
 
 
 }
 string tos2(byte* s) {
 
 if ( isnil ( s ) ) {
 
 v_panic ( tos2((byte*)"tos2: nil string") ) ;
 
return  (string) { .str = 0 , .len = 0 } ;
 
 }
 ;
 
int len= strlen ( s ) ;
 
string res= tos ( s , len ) ;
 
return  res ;
 
 
 }
 string string_clone(string a) {
 
string b= (string) { .len =  a .len , .str =  v_malloc ( a .len + 1 ) } ;
 
 for (
int i= 0  ;  i < a .len  ;  i ++ ) { 
 
 
 b .str[ i ]/*rbyte 1*/  =  a .str[ i ]/*rbyte 0*/ ;
 
 }
 ;
 
 b .str[ a .len ]/*rbyte 1*/  =  '\0' ;
 
return  b ;
 
 
 }
 string string_replace(string s, string rep, string with) {
 
 if ( s .len == 0  ||  rep .len == 0 ) {
 
return  s ;
 
 }
 ;
 
array_int idxs=new_array_from_c_array(0, 0, sizeof(int), (int[]) {EMPTY_STRUCT_INIT   }) ;
 
 {
 
 }
 
string rem= s ;
 
int rstart= 0 ;
 
 while (1) { 
 
int i= string_index( rem , rep ) ;
 
 if ( i < 0 ) {
 
 break
 ;
 
 }
 ;
 
_PUSH(& idxs , ( rstart + i ), tmp11, int) ;
 
 i  +=  rep .len ;
 
 rstart  +=  i ;
 
 rem  =  string_substr( rem , i , rem .len ) ;
 
 }
 ;
 
 if ( idxs .len == 0 ) {
 
return  s ;
 
 }
 ;
 
int new_len= s .len + idxs .len * ( with .len - rep .len ) ;
 
byte* b= v_malloc ( new_len + 1 ) ;
 
int idx_pos= 0 ;
 
int cur_idx= ( *(int*) array__get( idxs , idx_pos) ) ;
 
int b_i= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( i == cur_idx ) {
 
 for (
int j= 0  ;  j < with .len  ;  j ++ ) { 
 
 
 b [/*ptr*/ b_i ]/*rbyte 1*/  =  with .str[ j ]/*rbyte 0*/ ;
 
 b_i ++ ;
 
 }
 ;
 
 i  +=  rep .len - 1 ;
 
 idx_pos ++ ;
 
 if ( idx_pos < idxs .len ) {
 
 cur_idx  =  ( *(int*) array__get( idxs , idx_pos) ) ;
 
 }
 ;
 
 }
  else { 
 
 b [/*ptr*/ b_i ]/*rbyte 1*/  =  s .str[ i ]/*rbyte 0*/ ;
 
 b_i ++ ;
 
 }
 ;
 
 }
 ;
 
 b [/*ptr*/ new_len ]/*rbyte 1*/  =  '\0' ;
 
return  tos ( b , new_len ) ;
 
 
 }
 int string_int(string s) {
 
return  atoi ( s .str ) ;
 
 
 }
 i32 string_i32(string s) {
 
return  atol ( s .str ) ;
 
 
 }
 i64 string_i64(string s) {
 
return  atoll ( s .str ) ;
 
 
 }
 f32 string_f32(string s) {
 
return  atof ( s .str ) ;
 
 
 }
 f64 string_f64(string s) {
 
return  atof ( s .str ) ;
 
 
 }
 u32 string_u32(string s) {
 
return  strtoul ( s .str ,  0 ,  0 ) ;
 
 
 }
 u64 string_u64(string s) {
 
return  strtoull ( s .str ,  0 ,  0 ) ;
 
 
 }
 bool string_eq(string s, string a) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2((byte*)"string.eq(): nil string") ) ;
 
 }
 ;
 
 if ( s .len != a .len ) {
 
return  0 ;
 
 }
 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( s .str[ i ]/*rbyte 0*/ != a .str[ i ]/*rbyte 0*/ ) {
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 bool string_ne(string s, string a) {
 
return  ! string_eq( s , a ) ;
 
 
 }
 bool string_lt(string s, string a) {
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 if ( i >= a .len  ||  s .str[ i ]/*rbyte 0*/ > a .str[ i ]/*rbyte 0*/ ) {
 
return  0 ;
 
 }
  else  if ( s .str[ i ]/*rbyte 0*/ < a .str[ i ]/*rbyte 0*/ ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
 if ( s .len < a .len ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool string_le(string s, string a) {
 
return  string_lt( s , a )  ||  string_eq( s , a ) ;
 
 
 }
 bool string_gt(string s, string a) {
 
return  ! string_le( s , a ) ;
 
 
 }
 bool string_ge(string s, string a) {
 
return  ! string_lt( s , a ) ;
 
 
 }
 string string_add(string s, string a) {
 
int new_len= a .len + s .len ;
 
string res= (string) { .len =  new_len , .str =  v_malloc ( new_len + 1 ) } ;
 
 for (
int j= 0  ;  j < s .len  ;  j ++ ) { 
 
 
 res .str[ j ]/*rbyte 1*/  =  s .str[ j ]/*rbyte 0*/ ;
 
 }
 ;
 
 for (
int j= 0  ;  j < a .len  ;  j ++ ) { 
 
 
 res .str[ s .len + j ]/*rbyte 1*/  =  a .str[ j ]/*rbyte 0*/ ;
 
 }
 ;
 
 res .str[ new_len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 array_string string_split(string s, string delim) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( delim .len == 0 ) {
 
_PUSH(& res , ( s ), tmp30, string) ;
 
return  res ;
 
 }
 ;
 
 if ( delim .len == 1 ) {
 
return  string_split_single( s , delim .str[ 0 ]/*rbyte 0*/ ) ;
 
 }
 ;
 
int i= 0 ;
 
int start= 0 ;
 
 while ( i < s .len ) {
 
 
bool a= s .str[ i ]/*rbyte 0*/ == delim .str[ 0 ]/*rbyte 0*/ ;
 
int j= 1 ;
 
 while ( j < delim .len  &&  a ) {
 
 
 a  =  a  &&  s .str[ i + j ]/*rbyte 0*/ == delim .str[ j ]/*rbyte 0*/ ;
 
 j ++ ;
 
 }
 ;
 
bool last= i == s .len - 1 ;
 
 if ( a  ||  last ) {
 
 if ( last ) {
 
 i ++ ;
 
 }
 ;
 
string val= string_substr( s , start , i ) ;
 
 if ( val .len > 0 ) {
 
 if ( string_starts_with( val , delim ) ) {
 
 val  =  string_right( val , delim .len ) ;
 
 }
 ;
 
_PUSH(& res , ( string_trim_space( val ) ), tmp37, string) ;
 
 }
 ;
 
 start  =  i ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 array_string string_split_single(string s, byte delim) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( ((int)( delim ) ) == 0 ) {
 
_PUSH(& res , ( s ), tmp39, string) ;
 
return  res ;
 
 }
 ;
 
int i= 0 ;
 
int start= 0 ;
 
 while ( i < s .len ) {
 
 
bool is_delim= s .str[ i ]/*rbyte 0*/ == delim ;
 
bool last= i == s .len - 1 ;
 
 if ( is_delim  ||  last ) {
 
 if ( ! is_delim  &&  i == s .len - 1 ) {
 
 i ++ ;
 
 }
 ;
 
string val= string_substr( s , start , i ) ;
 
 if ( val .len > 0 ) {
 
_PUSH(& res , ( val ), tmp45, string) ;
 
 }
 ;
 
 start  =  i + 1 ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 array_string string_split_into_lines(string s) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( s .len == 0 ) {
 
return  res ;
 
 }
 ;
 
int start= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
bool last= i == s .len - 1 ;
 
 if ( ((int)( s .str[ i ]/*rbyte 0*/ ) ) == 10  ||  last ) {
 
 if ( last ) {
 
 i ++ ;
 
 }
 ;
 
string line= string_substr( s , start , i ) ;
 
_PUSH(& res , ( line ), tmp51, string) ;
 
 start  =  i + 1 ;
 
 }
 ;
 
 }
 ;
 
return  res ;
 
 
 }
 string string_left(string s, int n) {
 
 if ( n >= s .len ) {
 
return  s ;
 
 }
 ;
 
return  string_substr( s , 0 , n ) ;
 
 
 }
 string string_right(string s, int n) {
 
 if ( n >= s .len ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  string_substr( s , n , s .len ) ;
 
 
 }
 string string_substr(string s, int start, int end) {
 
 if ( start > end  ||  start > s .len  ||  end > s .len  ||  start < 0  ||  end < 0 ) {
 
 v_panic ( _STR("substr(%d, %d) out of bounds (len=%d)", start, end, s .len) ) ;
 
return  tos2((byte*)"") ;
 
 }
 ;
 
int len= end - start ;
 
string res= (string) { .len =  len , .str =  v_malloc ( len + 1 ) } ;
 
 for (
int i= 0  ;  i < len  ;  i ++ ) { 
 
 
 res .str [/*ptr*/ i ]/*rbyte 1*/  =  s .str [/*ptr*/ start + i ]/*rbyte 0*/ ;
 
 }
 ;
 
 res .str [/*ptr*/ len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 int string_index(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
  
 int tmp55 =  0; 

array_int prefix= array_repeat(&tmp55,  p .len , sizeof(int) ) ;
 
int j= 0 ;
 
 for (
int i= 1  ;  i < p .len  ;  i ++ ) { 
 
 
 while ( p .str[ j ]/*rbyte 0*/ != p .str[ i ]/*rbyte 0*/  &&  j > 0 ) {
 
 
 j  =  ( *(int*) array__get( prefix , j - 1) ) ;
 
 }
 ;
 
 if ( p .str[ j ]/*rbyte 0*/ == p .str[ i ]/*rbyte 0*/ ) {
 
 j ++ ;
 
 }
 ;
  
 int tmp61 =  j; 

array_set(&/*q*/ prefix , i , & tmp61) ;
 
 }
 ;
 
 j  =  0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 while ( p .str[ j ]/*rbyte 0*/ != s .str[ i ]/*rbyte 0*/  &&  j > 0 ) {
 
 
 j  =  ( *(int*) array__get( prefix , j - 1) ) ;
 
 }
 ;
 
 if ( p .str[ j ]/*rbyte 0*/ == s .str[ i ]/*rbyte 0*/ ) {
 
 j ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
 v_array_free( prefix ) ;
 
return  i - p .len + 1 ;
 
 }
 ;
 
 }
 ;
 
 v_array_free( prefix ) ;
 
return  - 1 ;
 
 
 }
 int string_index_any(string s, string chars) {
 
 string tmp65 =  chars;
 ;
for (int tmp66 = 0; tmp66 < tmp65 .len; tmp66 ++) {
 byte c = ((byte *) tmp65.str)[tmp66];
 
 
int index= string_index( s , byte_str( c ) ) ;
 
 if ( index != - 1 ) {
 
return  index ;
 
 }
 ;
 
 }
 ;
 
return  - 1 ;
 
 
 }
 int string_last_index(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int i= s .len - p .len ;
 
 while ( i >= 0 ) {
 
 
int j= 0 ;
 
 while ( j < p .len  &&  s .str[ i + j ]/*rbyte 0*/ == p .str[ j ]/*rbyte 0*/ ) {
 
 
 j ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
return  i ;
 
 }
 ;
 
 i -- ;
 
 }
 ;
 
return  - 1 ;
 
 
 }
 int string_index_after(string s, string p, int start) {
 
 if ( p .len > s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int strt= start ;
 
 if ( start < 0 ) {
 
 strt  =  0 ;
 
 }
 ;
 
 if ( start >= s .len ) {
 
return  - 1 ;
 
 }
 ;
 
int i= strt ;
 
 while ( i < s .len ) {
 
 
int j= 0 ;
 
int ii= i ;
 
 while ( j < p .len  &&  s .str[ ii ]/*rbyte 0*/ == p .str[ j ]/*rbyte 0*/ ) {
 
 
 j ++ ;
 
 ii ++ ;
 
 }
 ;
 
 if ( j == p .len ) {
 
return  i ;
 
 }
 ;
 
 i ++ ;
 
 }
 ;
 
return  - 1 ;
 
 
 }
 int string_count(string s, string substr) {
 
 if ( s .len == 0  ||  substr .len == 0 ) {
 
return  0 ;
 
 }
 ;
 
int n= 0 ;
 
int i= 0 ;
 
 while (1) { 
 
 i  =  string_index_after( s , substr , i ) ;
 
 if ( i == - 1 ) {
 
return  n ;
 
 }
 ;
 
 i  +=  substr .len ;
 
 n ++ ;
 
 }
 ;
 
 
 }
 bool string_contains(string s, string p) {
 
bool res= string_index( s , p ) > 0 - 1 ;
 
return  res ;
 
 
 }
 bool string_starts_with(string s, string p) {
 
bool res= string_index( s , p ) == 0 ;
 
return  res ;
 
 
 }
 bool string_ends_with(string s, string p) {
 
 if ( p .len > s .len ) {
 
return  0 ;
 
 }
 ;
 
bool res= string_last_index( s , p ) == s .len - p .len ;
 
return  res ;
 
 
 }
 string string_to_lower(string s) {
 
byte* b= v_malloc ( s .len ) ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 b [/*ptr*/ i ]/*rbyte 1*/  =  tolower ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
 }
 ;
 
return  tos ( b , s .len ) ;
 
 
 }
 string string_to_upper(string s) {
 
byte* b= v_malloc ( s .len ) ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
 b [/*ptr*/ i ]/*rbyte 1*/  =  toupper ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
 }
 ;
 
return  tos ( b , s .len ) ;
 
 
 }
 string string_find_between(string s, string start, string end) {
 
int start_pos= string_index( s , start ) ;
 
 if ( start_pos == - 1 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
string val= string_right( s , start_pos + start .len ) ;
 
int end_pos= string_index( val , end ) ;
 
 if ( end_pos == - 1 ) {
 
return  val ;
 
 }
 ;
 
return  string_left( val , end_pos ) ;
 
 
 }
 bool array_string_contains(array_string ar, string val) {
 
 array_string tmp86 =  ar;
 ;
for (int tmp87 = 0; tmp87 < tmp86 .len; tmp87 ++) {
 string s = ((string *) tmp86.data)[tmp87];
 
 
 if (string_eq( s , val ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool array_int_contains(array_int ar, int val) {
 
 array_int tmp88 =  ar ;
 ;
for (int i = 0; i < tmp88 .len; i ++) {
 int s = ((int *) tmp88 . data)[i];
 
 
 if ( s == val ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool is_space(byte c) {
 
return  isspace ( c ) ;
 
 
 }
 bool byte_is_space(byte c) {
 
return  is_space ( c ) ;
 
 
 }
 string string_trim_space(string s) {
 
 if (string_eq( s , tos2((byte*)"") ) ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
int i= 0 ;
 
 while ( i < s .len  &&  is_space ( s .str[ i ]/*rbyte 0*/ ) ) {
 
 
 i ++ ;
 
 }
 ;
 
int end= s .len - 1 ;
 
 while ( end >= 0  &&  is_space ( s .str[ end ]/*rbyte 0*/ ) ) {
 
 
 end -- ;
 
 }
 ;
 
 if ( i > end + 1 ) {
 
return  s ;
 
 }
 ;
 
string res= string_substr( s , i , end + 1 ) ;
 
return  res ;
 
 
 }
 string string_trim(string s, byte c) {
 
 if (string_eq( s , tos2((byte*)"") ) ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
int i= 0 ;
 
 while ( i < s .len  &&  c == s .str[ i ]/*rbyte 0*/ ) {
 
 
 i ++ ;
 
 }
 ;
 
string res= string_right( s , i ) ;
 
int end= res .len - 1 ;
 
 while ( end >= 0  &&  c == res .str[ end ]/*rbyte 1*/ ) {
 
 
 end -- ;
 
 }
 ;
 
 res  =  string_left( res , end + 1 ) ;
 
return  res ;
 
 
 }
 string string_trim_left(string s, string cutset) {
 
int start= string_index( s , cutset ) ;
 
 if ( start != 0 ) {
 
return  s ;
 
 }
 ;
 
 while ( start < s .len - 1  &&  s .str[ start ]/*rbyte 0*/ == cutset .str[ 0 ]/*rbyte 0*/ ) {
 
 
 start ++ ;
 
 }
 ;
 
return  string_right( s , start ) ;
 
 
 }
 string string_trim_right(string s, string cutset) {
 
int pos= string_last_index( s , cutset ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 int compare_strings(string* a, string* b) {
 
 if ( string_lt(* a ,* b ) ) {
 
return  - 1 ;
 
 }
 ;
 
 if ( string_gt(* a ,* b ) ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 int compare_strings_by_len(string* a, string* b) {
 
 if ( a ->len < b ->len ) {
 
return  - 1 ;
 
 }
 ;
 
 if ( a ->len > b ->len ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 int compare_lower_strings(string* a, string* b) {
 
string aa= string_to_lower(* a ) ;
 
string bb= string_to_lower(* b ) ;
 
return  compare_strings (& /*11 EXP:"string*" GOT:"string" */ aa ,& /*11 EXP:"string*" GOT:"string" */ bb ) ;
 
 
 }
 void array_string_sort(array_string* s) {
 
 array_sort_with_compare( s , compare_strings ) ;
 
 
 }
 void array_string_sort_ignore_case(array_string* s) {
 
 array_sort_with_compare( s , compare_lower_strings ) ;
 
 
 }
 void array_string_sort_by_len(array_string* s) {
 
 array_sort_with_compare( s , compare_strings_by_len ) ;
 
 
 }
 ustring string_ustring(string s) {
 
ustring res= (ustring) { .s =  s , .runes =  new_array ( 0 , s .len , sizeof( int) ) , .len = 0 } ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
int char_len= utf8_char_len ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
 
_PUSH(& res .runes , ( i ), tmp102, int) ;
 
 i  +=  char_len - 1 ;
 
 res .len ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 ustring string_ustring_tmp(string s) {
 
 if ( g_ustring_runes .len == 0 ) {
 
 g_ustring_runes  =  new_array ( 0 , 128 , sizeof( int) ) ;
 
 }
 ;
 
ustring res= (ustring) { .s =  s , .runes = new_array(0, 1, sizeof(int)) , .len = 0 } ;
 
 res .runes  =  g_ustring_runes ;
 
 res .runes .len  =  s .len ;
 
int j= 0 ;
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
int char_len= utf8_char_len ( s .str [/*ptr*/ i ]/*rbyte 0*/ ) ;
  
 int tmp107 =  i; 

array_set(&/*q*/ res .runes , j , & tmp107) ;
 
 j ++ ;
 
 i  +=  char_len - 1 ;
 
 res .len ++ ;
 
 }
 ;
 
return  res ;
 
 
 }
 string ustring_substr(ustring u, int _start, int _end) {
 
int start= ( *(int*) array__get( u .runes , _start) ) ;
 
int end= ( _end >= u .runes .len ) ? ( u .s .len ) : ( ( *(int*) array__get( u .runes , _end) ) ) ;
 
return  string_substr( u .s , start , end ) ;
 
 
 }
 string ustring_left(ustring u, int pos) {
 
return  ustring_substr( u , 0 , pos ) ;
 
 
 }
 string ustring_right(ustring u, int pos) {
 
return  ustring_substr( u , pos , u .len ) ;
 
 
 }
 byte string_at(string s, int idx) {
 
 if ( idx < 0  ||  idx >= s .len ) {
 
 v_panic ( _STR("string index out of range: %d / %d", idx, s .len) ) ;
 
 }
 ;
 
return  s .str [/*ptr*/ idx ]/*rbyte 0*/ ;
 
 
 }
 string ustring_at(ustring u, int idx) {
 
return  ustring_substr( u , idx , idx + 1 ) ;
 
 
 }
 void v_ustring_free(ustring u) {
 
 v_array_free( u .runes ) ;
 
 
 }
 int abs(int a) {
 
 if ( a >= 0 ) {
 
return  a ;
 
 }
 ;
 
return  - a ;
 
 
 }
 bool byte_is_digit(byte c) {
 
return  c >= '0'  &&  c <= '9' ;
 
 
 }
 bool byte_is_hex_digit(byte c) {
 
return  byte_is_digit( c )  ||  ( c >= 'a'  &&  c <= 'f' )  ||  ( c >= 'A'  &&  c <= 'F' ) ;
 
 
 }
 bool byte_is_oct_digit(byte c) {
 
return  c >= '0'  &&  c <= '7' ;
 
 
 }
 bool byte_is_letter(byte c) {
 
return  ( c >= 'a'  &&  c <= 'z' )  ||  ( c >= 'A'  &&  c <= 'Z' ) ;
 
 
 }
 void v_string_free(string s) {
 
 v_free ( s .str ) ;
 
 
 }
 string string_all_before(string s, string dot) {
 
int pos= string_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 string string_all_before_last(string s, string dot) {
 
int pos= string_last_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_left( s , pos ) ;
 
 
 }
 string string_all_after(string s, string dot) {
 
int pos= string_last_index( s , dot ) ;
 
 if ( pos == - 1 ) {
 
return  s ;
 
 }
 ;
 
return  string_right( s , pos + dot .len ) ;
 
 
 }
 string array_string_join(array_string a, string del) {
 
 if ( a .len == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
int len= 0 ;
 
 array_string tmp118 =  a ;
 ;
for (int i = 0; i < tmp118 .len; i ++) {
 string val = ((string *) tmp118 . data)[i];
 
 
 len  +=  val .len + del .len ;
 
 }
 ;
 
 len  -=  del .len ;
 
string res= tos2((byte*)"") ;
 
 res .len  =  len ;
 
 res .str  =  v_malloc ( res .len + 1 ) ;
 
int idx= 0 ;
 
 array_string tmp121 =  a ;
 ;
for (int i = 0; i < tmp121 .len; i ++) {
 string val = ((string *) tmp121 . data)[i];
 
 
 for (
int j= 0  ;  j < val .len  ;  j ++ ) { 
 
 
byte c= val .str[ j ]/*rbyte 0*/ ;
 
 res .str [/*ptr*/ idx ]/*rbyte 1*/  =  val .str [/*ptr*/ j ]/*rbyte 0*/ ;
 
 idx ++ ;
 
 }
 ;
 
 if ( i != a .len - 1 ) {
 
 for (
int k= 0  ;  k < del .len  ;  k ++ ) { 
 
 
 res .str [/*ptr*/ idx ]/*rbyte 1*/  =  del .str [/*ptr*/ k ]/*rbyte 0*/ ;
 
 idx ++ ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 res .str [/*ptr*/ res .len ]/*rbyte 1*/  =  '\0' ;
 
return  res ;
 
 
 }
 string array_string_join_lines(array_string s) {
 
return  array_string_join( s , tos2((byte*)"\n") ) ;
 
 
 }
 string string_reverse(string s) {
 
string res= (string) { .len =  s .len , .str =  v_malloc ( s .len ) } ;
 
 for (
int i= s .len - 1  ;  i >= 0  ;  i -- ) { 
 
 
 res .str[ s .len - i - 1 ]/*rbyte 1*/  =  s .str[ i ]/*rbyte 0*/ ;
 
 }
 ;
 
return  res ;
 
 
 }
 string string_limit(string s, int max) {
 
ustring u= string_ustring( s ) ;
 
 if ( u .len <= max ) {
 
return  s ;
 
 }
 ;
 
return  ustring_substr( u , 0 , max ) ;
 
 
 }
 bool byte_is_white(byte c) {
 
int i= ((int)( c ) ) ;
 
return  i == 10  ||  i == 32  ||  i == 9  ||  i == 13  ||  c == '\r' ;
 
 
 }
 int string_hash(string s) {
 
int h= 0 ;
 
 if ( h == 0  &&  s .len > 0 ) {
 
 string tmp130 =  s;
 ;
for (int tmp131 = 0; tmp131 < tmp130 .len; tmp131 ++) {
 byte c = ((byte *) tmp130.str)[tmp131];
 
 
 h  =  h * 31 + ((int)( c ) ) ;
 
 }
 ;
 
 }
 ;
 
return  h ;
 
 
 }
 array_byte string_bytes(string s) {
 
 if ( s .len == 0 ) {
 
return new_array_from_c_array(0, 0, sizeof(byte), (byte[]) {EMPTY_STRUCT_INIT   }) ;
 
 }
 ;
  
 byte tmp132 =  ((byte)( 0 ) ); 

array_byte buf= array_repeat(&tmp132,  s .len , sizeof(byte) ) ;
 
 memcpy ( buf .data ,  s .str ,  s .len ) ;
 
return  buf ;
 
 
 }
 void v_exit(int code) {
 
 exit ( code ) ;
 
 
 }
 bool isnil(void* v) {
 
return  v == 0 ;
 
 
 }
 void on_panic(int (*f)( int  /*FFF*/ )) {
 
 
 }
 void print_backtrace() {
 
 return ;
 
 #ifdef __APPLE__
 
voidptr buffer  [100 ]= STRUCT_DEFAULT_VALUE ;
 
void* nr_ptrs= backtrace ( buffer ,  100 ) ;
 
 backtrace_symbols_fd ( buffer ,  nr_ptrs ,  1 ) ;
 
 #endif
 ;
 
 
 }
 void _panic_debug(int line_no, string file, string mod, string fn_name, string s) {
 
 println ( tos2((byte*)"================ V panic ================") ) ;
 
printf( "   module: %.*s\n", mod.len, mod.str ) ;
 
printf( " function: %.*s()\n", fn_name.len, fn_name.str ) ;
 
printf( "     file: %.*s\n", file.len, file.str ) ;
 
 println (string_add( tos2((byte*)"     line: ") , int_str( line_no ) ) ) ;
 
printf( "  message: %.*s\n", s.len, s.str ) ;
 
 println ( tos2((byte*)"=========================================") ) ;
 
 print_backtrace ( ) ;
 
 exit ( 1 ) ;
 
 
 }
 void v_panic(string s) {
 
printf( "V panic: %.*s\n", s.len, s.str ) ;
 
 print_backtrace ( ) ;
 
 exit ( 1 ) ;
 
 
 }
 void println(string s) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2((byte*)"println(NIL)") ) ;
 
 }
 ;
 
 #ifdef _WIN32
 
 _putws ( string_to_wide( s ) ) ;
 
 ;
 
 #else
 
 printf ( "%.*s\n" ,  s .len ,  s .str ) ;
 
 #endif
 ;
 
 
 }
 void eprintln(string s) {
 
 if ( isnil ( s .str ) ) {
 
 v_panic ( tos2((byte*)"eprintln(NIL)") ) ;
 
 }
 ;
 
 #ifdef __APPLE__
 
 fprintf ( stderr ,  "%.*s\n" ,  s .len ,  s .str ) ;
 
 ;
 
 #else
 
 println ( s ) ;
 
 #endif
 ;
 
 
 }
 void v_print(string s) {
 
 #ifdef _WIN32
 
 wprintf ( string_to_wide( s ) ) ;
 
 ;
 
 #else
 
 printf ( "%.*s" ,  s .len ,  s .str ) ;
 
 #endif
 ;
 
 
 }
 byte* v_malloc(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2((byte*)"malloc(<0)") ) ;
 
 }
 ;
 
byte* ptr= malloc ( n ) ;
 
 if ( isnil ( ptr ) ) {
 
 v_panic ( _STR("malloc(%d) failed", n) ) ;
 
 }
 ;
 
return  ptr ;
 
 
 }
 byte* v_calloc(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2((byte*)"calloc(<0)") ) ;
 
 }
 ;
 
return  calloc ( n ,  1 ) ;
 
 
 }
 void v_free(void* ptr) {
 
 free ( ptr ) ;
 
 
 }
 void* memdup(void* src, int sz) {
 
byte* mem= v_malloc ( sz ) ;
 
return  memcpy ( mem ,  src ,  sz ) ;
 
 
 }
 string double_str(double d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string f64_str(f64 d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string f32_str(f32 d) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%f" ,  d ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 string ptr_str(void* ptr) {
 
byte* buf= v_malloc ( sizeof( double) * 5 + 1 ) ;
 
 sprintf ( buf ,  "%p" ,  ptr ) ;
 
return  tos ( buf , strlen ( buf ) ) ;
 
 
 }
 bool f64_eq(f64 a, f64 b) {
 
return  fabs ( a - b ) <= DBL_EPSILON ;
 
 
 }
 string int_str(int nn) {
 
int n= nn ;
 
 if ( n == 0 ) {
 
return  tos2((byte*)"0") ;
 
 }
 ;
 
int max= 16 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < 0 ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > 0 ) {
 
 
int d= n % 10 ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((int)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / 10 ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string u8_str(u8 nn) {
 
u8 n= nn ;
 
 if ( n == ((u8)( 0 ) ) ) {
 
return  tos2((byte*)"0") ;
 
 }
 ;
 
int max= 5 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < ((u8)( 0 ) ) ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > ((u8)( 0 ) ) ) {
 
 
u8 d= n % ((u8)( 10 ) ) ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((u8)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / ((u8)( 10 ) ) ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string i64_str(i64 nn) {
 
i64 n= nn ;
 
 if ( n == ((i64)( 0 ) ) ) {
 
return  tos2((byte*)"0") ;
 
 }
 ;
 
int max= 32 ;
 
byte* buf= v_malloc ( max ) ;
 
int len= 0 ;
 
bool is_neg= 0 ;
 
 if ( n < ((i64)( 0 ) ) ) {
 
 n  =  - n ;
 
 is_neg  =  1 ;
 
 }
 ;
 
 while ( n > ((i64)( 0 ) ) ) {
 
 
int d= ((int)( n % ((i64)( 10 ) ) ) ) ;
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  d + ((int)( '0' ) ) ;
 
 len ++ ;
 
 n  =  n / ((i64)( 10 ) ) ;
 
 }
 ;
 
 if ( is_neg ) {
 
 buf [/*ptr*/ max - len - 1 ]/*rbyte 1*/  =  '-' ;
 
 len ++ ;
 
 }
 ;
 
return  tos ( buf + max - len , len ) ;
 
 
 }
 string bool_str(bool b) {
 
 if ( b ) {
 
return  tos2((byte*)"true") ;
 
 }
 ;
 
return  tos2((byte*)"false") ;
 
 
 }
 string int_hex(int n) {
 
int len= ( n >= 0 ) ? ( int_str( n ) .len + 3 ) : ( 11 ) ;
 
byte* hex= v_malloc ( len ) ;
 
int count= ((int)( sprintf ( hex ,  "0x%x" ,  n ) ) ) ;
 
return  tos ( hex , count ) ;
 
 
 }
 string i64_hex(i64 n) {
 
int len= ( n >= ((i64)( 0 ) ) ) ? ( i64_str( n ) .len + 3 ) : ( 19 ) ;
 
byte* hex= v_malloc ( len ) ;
 
int count= ((int)( sprintf ( hex ,  "0x%x" ,  n ) ) ) ;
 
return  tos ( hex , count ) ;
 
 
 }
 bool array_byte_contains(array_byte a, byte val) {
 
 array_byte tmp29 =  a;
 ;
for (int tmp30 = 0; tmp30 < tmp29 .len; tmp30 ++) {
 byte aa = ((byte *) tmp29.data)[tmp30];
 
 
 if ( aa == val ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 string rune_str(rune c) {
 
int fst_byte= ((int)( c ) )  >>  8 * 3 & 0xff ;
 
int len= utf8_char_len ( fst_byte ) ;
 
string str= (string) { .len =  len , .str =  v_malloc ( len + 1 ) } ;
 
 for (
int i= 0  ;  i < len  ;  i ++ ) { 
 
 
 str .str [/*ptr*/ i ]/*rbyte 1*/  =  ((int)( c ) )  >>  8 * ( 3 - i ) & 0xff ;
 
 }
 ;
 
 str .str[ len ]/*rbyte 1*/  =  '\0' ;
 
return  str ;
 
 
 }
 string byte_str(byte c) {
 
string str= (string) { .len =  1 , .str =  v_malloc ( 2 ) } ;
 
 str .str [/*ptr*/ 0 ]/*rbyte 1*/  =  c ;
 
 str .str [/*ptr*/ 1 ]/*rbyte 1*/  =  '\0' ;
 
return  str ;
 
 
 }
 bool byte_is_capital(byte c) {
 
return  c >= 'A'  &&  c <= 'Z' ;
 
 
 }
 array_byte array_byte_clone(array_byte b) {
  
 byte tmp36 =  ((byte)( 0 ) ); 

array_byte res= array_repeat(&tmp36,  b .len , sizeof(byte) ) ;
 
 for (
int i= 0  ;  i < b .len  ;  i ++ ) { 
 
  
 byte tmp41 =  ( *(byte*) array__get( b , i) ); 

array_set(&/*q*/ res , i , & tmp41) ;
 
 }
 ;
 
return  res ;
 
 
 }
 int utf8_char_len(byte b) {
 
return  ( ( 0xe5000000  >>  ( ( b  >>  3 ) & 0x1e ) ) & 3 ) + 1 ;
 
 
 }
 string utf32_to_str(u32 code) {
 
int icode= ((int)( code ) ) ;
 
byte* buffer= v_malloc ( 5 ) ;
 
 if ( icode <= 127 ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  icode ;
 
return  tos ( buffer , 1 ) ;
 
 }
 ;
 
 if ( ( icode <= 2047 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  192 | ( icode  >>  6 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 2 ) ;
 
 }
 ;
 
 if ( ( icode <= 65535 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  224 | ( icode  >>  12 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 3 ) ;
 
 }
 ;
 
 if ( ( icode <= 1114111 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyte 1*/  =  240 | ( icode  >>  18 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyte 1*/  =  128 | ( ( icode  >>  12 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyte 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 3 ]/*rbyte 1*/  =  128 | ( icode & 63 ) ;
 
return  tos ( buffer , 4 ) ;
 
 }
 ;
 
return  tos2((byte*)"") ;
 
 
 }
 string utf32_to_str_no_malloc(u32 code, void* buf) {
 
int icode= ((int)( code ) ) ;
 
byteptr buffer= ((byteptr)( buf ) ) ;
 
 if ( icode <= 127 ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  icode ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 1 ) ;
 
 }
 ;
 
 if ( ( icode <= 2047 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  192 | ( icode  >>  6 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 2 ) ;
 
 }
 ;
 
 if ( ( icode <= 65535 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  224 | ( icode  >>  12 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 3 ) ;
 
 }
 ;
 
 if ( ( icode <= 1114111 ) ) {
 
 buffer [/*ptr*/ 0 ]/*rbyteptr 1*/  =  240 | ( icode  >>  18 ) ;
 
 buffer [/*ptr*/ 1 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  12 ) & 63 ) ;
 
 buffer [/*ptr*/ 2 ]/*rbyteptr 1*/  =  128 | ( ( icode  >>  6 ) & 63 ) ;
 
 buffer [/*ptr*/ 3 ]/*rbyteptr 1*/  =  128 | ( icode & 63 ) ;
 
return  tos (& /*11 EXP:"byte*" GOT:"byteptr" */ buffer , 4 ) ;
 
 }
 ;
 
return  tos2((byte*)"") ;
 
 
 }
 int string_utf32_code(string _rune) {
 
 if ( _rune .len == 0 ) {
 
return  0 ;
 
 }
 ;
 
 if ( _rune .len == 1 ) {
 
return  ((int)( _rune .str[ 0 ]/*rbyte 0*/ ) ) ;
 
 }
 ;
 
byte b= ((byte)( ((int)( _rune .str[ 0 ]/*rbyte 0*/ ) ) ) ) ;
 
 b  =  b  <<  _rune .len ;
 
int res= ((int)( b ) ) ;
 
int shift= 6 - _rune .len ;
 
 for (
int i= 1  ;  i < _rune .len  ;  i ++ ) { 
 
 
int c= ((int)( _rune .str[ i ]/*rbyte 0*/ ) ) ;
 
 res  =  res  <<  shift ;
 
 res  |=  c & 63 ;
 
 shift  =  6 ;
 
 }
 ;
 
return  res ;
 
 
 }
 u16* string_to_wide(string _str) {
 
 #ifdef _WIN32
 
int num_chars= ((int)( MultiByteToWideChar ( builtin__CP_UTF8 ,  0 ,  _str .str ,  _str .len ,  0 ,  0 ) ) ) ;
 
u16* wstr= ((u16*)( v_malloc ( ( num_chars + 1 ) * 2 ) ) ) ;
 
 if ( wstr > 0 ) {
 
 MultiByteToWideChar ( builtin__CP_UTF8 ,  0 ,  _str .str ,  _str .len ,  wstr ,  num_chars ) ;
 
 memset ( ((byte*)( wstr ) ) + num_chars * 2 ,  0 ,  2 ) ;
 
 }
 ;
 
return  wstr ;
 
 ;
 
 #else
 
return  0 ;
 
 #endif
 ;
 
 
 }
 string string_from_wide(u16* _wstr) {
 
 #ifdef _WIN32
 
int wstr_len= ((int)( wcslen ( _wstr ) ) ) ;
 
return  string_from_wide2 ( _wstr , wstr_len ) ;
 
 ;
 
 #else
 
return  tos2((byte*)"") ;
 
 #endif
 ;
 
 
 }
 string string_from_wide2(u16* _wstr, int len) {
 
 #ifdef _WIN32
 
int num_chars= ((int)( WideCharToMultiByte ( builtin__CP_UTF8 ,  0 ,  _wstr ,  len ,  0 ,  0 ,  0 ,  0 ) ) ) ;
 
byte* str_to= ((byte*)( v_malloc ( num_chars + 1 ) ) ) ;
 
 if ( str_to > 0 ) {
 
 WideCharToMultiByte ( builtin__CP_UTF8 ,  0 ,  _wstr ,  len ,  str_to ,  num_chars ,  0 ,  0 ) ;
 
 memset ( ((byte*)( str_to ) ) + num_chars ,  0 ,  1 ) ;
 
 }
 ;
 
return  tos2 ( str_to ) ;
 
 ;
 
 #else
 
return  tos2((byte*)"") ;
 
 #endif
 ;
 
 
 }
 map new_map(int cap, int elm_size) {
 
map res= (map) { .element_size =  elm_size , .root =  0 , ._keys = new_array(0, 1, sizeof(string)) , .key_i = 0 , .size = 0 } ;
 
return  res ;
 
 
 }
 map new_map_init(int cap, int elm_size, string* keys, void* vals) {
 
map res= (map) { .element_size =  elm_size , .root =  0 , ._keys = new_array(0, 1, sizeof(string)) , .key_i = 0 , .size = 0 } ;
 
 int tmp3 =  0;
 ;
for (int tmp4 = tmp3; tmp4 <  cap; tmp4++) {
 int i = tmp4;
 
 
 map__set(& /* ? */ res , keys [/*ptr*/ i ]/*rstring 0*/ ,(byte*) vals + i * elm_size ) ;
 
 }
 ;
 
return  res ;
 
 
 }
 Node* new_node(string key, void* val, int element_size) {
 
Node* new_e= ALLOC_INIT(Node, { .key =  key , .val =  v_malloc ( element_size ) , .left =  0 , .right =  0 , .is_empty = 0 , } ) ;
 
 memcpy ( new_e ->val ,  val ,  element_size ) ;
 
return  new_e ;
 
 
 }
 void map_insert(map* m, Node* n, string key, void* val) {
 
 if (string_eq( n ->key , key ) ) {
 
 memcpy ( n ->val ,  val ,  m ->element_size ) ;
 
 return ;
 
 }
 ;
 
 if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
 n ->left  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 }
  else { 
 
 map_insert( m , n ->left , key , val ) ;
 
 }
 ;
 
 return ;
 
 }
 ;
 
 if ( isnil ( n ->right ) ) {
 
 n ->right  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 }
  else { 
 
 map_insert( m , n ->right , key , val ) ;
 
 }
 ;
 
 
 }
 bool Node_find(Node* n, string key, void* out, int element_size) {
 
 if (string_eq( n ->key , key ) ) {
 
 memcpy ( out ,  n ->val ,  element_size ) ;
 
return  1 ;
 
 }
  else  if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find(& /* ? */* n ->left , key , out , element_size ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( isnil ( n ->right ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find(& /* ? */* n ->right , key , out , element_size ) ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool Node_find2(Node* n, string key, int element_size) {
 
 if (string_eq( n ->key , key ) ) {
 
return  1 ;
 
 }
  else  if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find2(& /* ? */* n ->left , key , element_size ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( isnil ( n ->right ) ) {
 
return  0 ;
 
 }
  else { 
 
return  Node_find2(& /* ? */* n ->right , key , element_size ) ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 void map__set(map* m, string key, void* val) {
 
 if ( isnil ( m ->root ) ) {
 
 m ->root  =  new_node ( key , val , m ->element_size ) ;
 
 m ->size ++ ;
 
 return ;
 
 }
 ;
 
 map_insert( m , m ->root , key , val ) ;
 
 
 }
 void map_preorder_keys(map* m, Node* node) {
 
 if ( ! node ->is_empty ) {
  
 string tmp6 =  node ->key; 

array_set(&/*q*/ m ->_keys , m ->key_i , & tmp6) ;
 
 m ->key_i ++ ;
 
 }
 ;
 
 if ( ! isnil ( node ->left ) ) {
 
 map_preorder_keys( m , node ->left ) ;
 
 }
 ;
 
 if ( ! isnil ( node ->right ) ) {
 
 map_preorder_keys( m , node ->right ) ;
 
 }
 ;
 
 
 }
 array_string map_keys(map* m) {
  
 string tmp7 =  tos2((byte*)""); 

 m ->_keys  =  array_repeat(&tmp7,  m ->size , sizeof(string) ) ;
 
 m ->key_i  =  0 ;
 
 if ( isnil ( m ->root ) ) {
 
return  m ->_keys ;
 
 }
 ;
 
 map_preorder_keys( m , m ->root ) ;
 
return  m ->_keys ;
 
 
 }
 bool map_get(map m, string key, void* out) {
 
 if ( isnil ( m .root ) ) {
 
return  0 ;
 
 }
 ;
 
return  Node_find(& /* ? */* m .root , key , out , m .element_size ) ;
 
 
 }
 void Node_delete(Node* n, string key, int element_size) {
 
 if (string_eq( n ->key , key ) ) {
 
 memset ( n ->val ,  0 ,  element_size ) ;
 
 n ->is_empty  =  1 ;
 
 return ;
 
 }
  else  if (string_gt( n ->key , key ) ) {
 
 if ( isnil ( n ->left ) ) {
 
 return ;
 
 }
  else { 
 
 Node_delete( n ->left , key , element_size ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( isnil ( n ->right ) ) {
 
 return ;
 
 }
  else { 
 
 Node_delete( n ->right , key , element_size ) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void map_delete(map* m, string key) {
 
 Node_delete( m ->root , key , m ->element_size ) ;
 
 m ->size -- ;
 
 
 }
 bool map_exists(map m, string key) {
 
 v_panic ( tos2((byte*)"map.exists(key) was removed from the language. Use `key in map` instead.") ) ;
 
return  0 ;
 
 
 }
 bool map__exists(map m, string key) {
 
return  ! isnil ( m .root )  &&  Node_find2(& /* ? */* m .root , key , m .element_size ) ;
 
 
 }
 void v_map_print(map m) {
 
 println ( tos2((byte*)"<<<<<<<<") ) ;
 
 println ( tos2((byte*)">>>>>>>>>>") ) ;
 
 
 }
 void v_map_free(map m) {
 
 
 }
 string map_string_str(map_string m) {
 
 if ( m .size == 0 ) {
 
return  tos2((byte*)"{}") ;
 
 }
 ;
 
strings__Builder sb= strings__new_builder ( 50 ) ;
 
 strings__Builder_writeln(& /* ? */ sb , tos2((byte*)"{") ) ;
 
 map_string tmp9 =  m ;
 array_string keys_tmp9 = map_keys(& tmp9 ); 
 for (int l = 0; l < keys_tmp9 .len; l++) {
   string key = ((string*)keys_tmp9 .data)[l];
 string val = {0}; map_get(tmp9, key, & val);
 
 
 strings__Builder_writeln(& /* ? */ sb , _STR("  \"%.*s\" => \"%.*s\"", key.len, key.str, val.len, val.str) ) ;
 
 }
 ;
 
 strings__Builder_writeln(& /* ? */ sb , tos2((byte*)"}") ) ;
 
return  strings__Builder_str( sb ) ;
 
 
 }
 Option opt_ok(void* data, int size) {
 
 if ( size >= 500 ) {
 
 v_panic ( _STR("option size too big: %d (max is 500), this is a temporary limit", size) ) ;
 
 }
 ;
 
Option res= (Option) { .ok =  1 , .error = tos("", 0) , } ;
 
 memcpy ( res .data ,  data ,  size ) ;
 
return  res ;
 
 
 }
 Option v_error(string s) {
 
return  (Option) { .error =  s , .ok = 0 } ;
 
 
 }
 strings__Builder strings__new_builder(int initial_size) {
 
return  (strings__Builder) { .buf =  _make ( 0 , initial_size , sizeof( byte) ) , .len = 0 } ;
 
 
 }
 void strings__Builder_write(strings__Builder* b, string s) {
 
 array__push_many(& /* ? */ b ->buf , s .str , s .len ) ;
 
 b ->len  +=  s .len ;
 
 
 }
 void strings__Builder_writeln(strings__Builder* b, string s) {
 
 array__push_many(& /* ? */ b ->buf , s .str , s .len ) ;
 
_PUSH(& b ->buf , ( '\n' ), tmp1, byte) ;
 
 b ->len  +=  s .len + 1 ;
 
 
 }
 string strings__Builder_str(strings__Builder b) {
 
return  (tos( b .buf .data ,  b .len ) ) ;
 
 
 }
 void strings__Builder_cut(strings__Builder* b, int n) {
 
 b ->len  -=  n ;
 
 
 }
 void strings__Builder_free(strings__Builder* b) {
 
 v_free ( b ->buf .data ) ;
 
 
 }
 string strings__repeat(byte c, int n) {
 
 if ( n <= 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
byte* arr= v_malloc ( n + 1 ) ;
 
 for (
int i= 0  ;  i < n  ;  i ++ ) { 
 
 
 arr [/*ptr*/ i ]/*rbyte 1*/  =  c ;
 
 }
 ;
 
 arr [/*ptr*/ n ]/*rbyte 1*/  =  '\0' ;
 
return  (tos( arr ,  n ) ) ;
 
 
 }
 void os__todo_remove() {
 
 
 }
 array_string os__init_os_args(int argc, byteptr* argv) {
 
array_string args=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 #ifdef _WIN32
 
voidptr* args_list= ((voidptr*)( 0 ) ) ;
 
int args_count= 0 ;
 
 args_list  =  CommandLineToArgvW ( GetCommandLine ( ) ,  & /*vvar*/  args_count ) ;
 
 for (
int i= 0  ;  i < args_count  ;  i ++ ) { 
 
 
_PUSH(& args , ( string_from_wide ( ((u16*)( args_list [/*ptr*/ i ]/*rvoidptr 1*/ ) ) ) ), tmp5, string) ;
 
 }
 ;
 
 LocalFree ( args_list ) ;
 
 ;
 
 #else
 
 for (
int i= 0  ;  i < argc  ;  i ++ ) { 
 
 
_PUSH(& args , ( (tos2( argv [/*ptr*/ i ]/*rbyteptr 0*/ ) ) ), tmp7, string) ;
 
 }
 ;
 
 #endif
 ;
 
return  args ;
 
 
 }
 array_string os__parse_windows_cmd_line(byte* cmd) {
 
string s= (tos2( cmd ) ) ;
 
return  string_split( s , tos2((byte*)" ") ) ;
 
 
 }
 Option_string os__read_file(string path) {
 
string mode= tos2((byte*)"rb") ;
  
 struct /*c struct init*/ 

FILE* fp= ALLOC_INIT(FILE, { EMPTY_STRUCT_INIT } ) ;
 
 #ifdef _WIN32
 
 fp  =  _wfopen ( string_to_wide( path ) ,  string_to_wide( mode ) ) ;
 
 ;
 
 #else
 
byte* cpath= path .str ;
 
 fp  =  fopen ( cpath ,  mode .str ) ;
 
 #endif
 ;
 
 if ( isnil ( fp ) ) {
 
return  v_error ( _STR("failed to open file \"%.*s\"", path.len, path.str) ) ;
 
 }
 ;
 
 fseek ( fp ,  0 ,  SEEK_END ) ;
 
int fsize= ftell ( fp ) ;
 
 rewind ( fp ) ;
 
byte* str= v_malloc ( fsize + 1 ) ;
 
 fread ( str ,  fsize ,  1 ,  fp ) ;
 
 fclose ( fp ) ;
 
 str [/*ptr*/ fsize ]/*rbyte 1*/  =  0 ;
 
string tmp14 = OPTION_CAST(string)( (tos( str ,  fsize ) )); return opt_ok(&tmp14, sizeof(string)) ;
 
 
 }
 int os__file_size(string path) {
  
 struct /*c struct init*/ 

stat s= (struct stat) { .st_size = 0 , .st_mode = 0 , .st_mtime = 0 } ;
 
 #ifdef _WIN32
 
 _wstat ( string_to_wide( path ) ,  & /*vvar*/  s ) ;
 
 ;
 
 #else
 
 stat ( path .str ,  & /*vvar*/  s ) ;
 
 #endif
 ;
 
return  s .st_size ;
 
 
 }
 void os__mv(string old, string new) {
 
 #ifdef _WIN32
 
 _wrename ( string_to_wide( old ) ,  string_to_wide( new ) ) ;
 
 ;
 
 #else
 
 rename ( old .str ,  new .str ) ;
 
 #endif
 ;
 
 
 }
 array_string os__read_lines(string path) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
int buf_len= 1024 ;
 
byte* buf= v_malloc ( buf_len ) ;
 
string mode= tos2((byte*)"rb") ;
  
 struct /*c struct init*/ 

FILE* fp= ALLOC_INIT(FILE, { EMPTY_STRUCT_INIT } ) ;
 
 #ifdef _WIN32
 
 fp  =  _wfopen ( string_to_wide( path ) ,  string_to_wide( mode ) ) ;
 
 ;
 
 #else
 
 fp  =  fopen ( path .str ,  mode .str ) ;
 
 #endif
 ;
 
 if ( isnil ( fp ) ) {
 
return  res ;
 
 }
 ;
 
int buf_index= 0 ;
 
 while ( fgets ( buf + buf_index ,  buf_len - buf_index ,  fp ) != 0 ) {
 
 
int len= strlen ( buf ) ;
 
 if ( len == buf_len - 1  &&  buf [/*ptr*/ len - 1 ]/*rbyte 1*/ != 10 ) {
 
 buf_len  *=  2 ;
 
 buf  =  realloc ( buf ,  buf_len ) ;
 
 if ( isnil ( buf ) ) {
 
 v_panic ( tos2((byte*)"Could not reallocate the read buffer") ) ;
 
 }
 ;
 
 buf_index  =  len ;
 
 continue
 ;
 
 }
 ;
 
 if ( buf [/*ptr*/ len - 1 ]/*rbyte 1*/ == 10  ||  buf [/*ptr*/ len - 1 ]/*rbyte 1*/ == 13 ) {
 
 buf [/*ptr*/ len - 1 ]/*rbyte 1*/  =  '\0' ;
 
 }
 ;
 
 if ( len > 1  &&  buf [/*ptr*/ len - 2 ]/*rbyte 1*/ == 13 ) {
 
 buf [/*ptr*/ len - 2 ]/*rbyte 1*/  =  '\0' ;
 
 }
 ;
 
_PUSH(& res , ( tos_clone ( buf ) ), tmp23, string) ;
 
 buf_index  =  0 ;
 
 }
 ;
 
 fclose ( fp ) ;
 
return  res ;
 
 
 }
 array_ustring os__read_ulines(string path) {
 
array_string lines= os__read_lines ( path ) ;
 
array_ustring ulines=new_array_from_c_array(0, 0, sizeof(ustring), (ustring[]) {EMPTY_STRUCT_INIT   }) ;
 
 array_string tmp26 =  lines;
 ;
for (int tmp27 = 0; tmp27 < tmp26 .len; tmp27 ++) {
 string myline = ((string *) tmp26.data)[tmp27];
 
 
_PUSH(& ulines , ( string_ustring( myline ) ), tmp28, ustring) ;
 
 }
 ;
 
return  ulines ;
 
 
 }
 Option_os__File os__open(string path) {
 
os__File file= (struct os__File) { .cfile = 0 } ;
 
 #ifdef _WIN32
 
u16* wpath= string_to_wide( path ) ;
 
string mode= tos2((byte*)"rb") ;
 
 file  =  (os__File) { .cfile =  _wfopen ( wpath ,  string_to_wide( mode ) ) } ;
 
 ;
 
 #else
 
byte* cpath= path .str ;
 
 file  =  (os__File) { .cfile =  fopen ( cpath ,  "rb" ) } ;
 
 #endif
 ;
 
 if ( isnil ( file .cfile ) ) {
 
return  v_error ( _STR("failed to open file \"%.*s\"", path.len, path.str) ) ;
 
 }
 ;
 
os__File tmp33 = OPTION_CAST(os__File)( file); return opt_ok(&tmp33, sizeof(os__File)) ;
 
 
 }
 Option_os__File os__create(string path) {
 
os__File file= (os__File) { .cfile = 0 } ;
 
 #ifdef _WIN32
 
u16* wpath= string_to_wide( string_replace( path , tos2((byte*)"/") , tos2((byte*)"\\") ) ) ;
 
string mode= tos2((byte*)"wb") ;
 
 file  =  (os__File) { .cfile =  _wfopen ( wpath ,  string_to_wide( mode ) ) } ;
 
 ;
 
 #else
 
byte* cpath= path .str ;
 
 file  =  (os__File) { .cfile =  fopen ( cpath ,  "wb" ) } ;
 
 #endif
 ;
 
 if ( isnil ( file .cfile ) ) {
 
return  v_error ( _STR("failed to create file \"%.*s\"", path.len, path.str) ) ;
 
 }
 ;
 
os__File tmp38 = OPTION_CAST(os__File)( file); return opt_ok(&tmp38, sizeof(os__File)) ;
 
 
 }
 Option_os__File os__open_append(string path) {
 
os__File file= (os__File) { .cfile = 0 } ;
 
 #ifdef _WIN32
 
u16* wpath= string_to_wide( string_replace( path , tos2((byte*)"/") , tos2((byte*)"\\") ) ) ;
 
string mode= tos2((byte*)"ab") ;
 
 file  =  (os__File) { .cfile =  _wfopen ( wpath ,  string_to_wide( mode ) ) } ;
 
 ;
 
 #else
 
byte* cpath= path .str ;
 
 file  =  (os__File) { .cfile =  fopen ( cpath ,  "ab" ) } ;
 
 #endif
 ;
 
 if ( isnil ( file .cfile ) ) {
 
return  v_error ( _STR("failed to create(append) file \"%.*s\"", path.len, path.str) ) ;
 
 }
 ;
 
os__File tmp43 = OPTION_CAST(os__File)( file); return opt_ok(&tmp43, sizeof(os__File)) ;
 
 
 }
 void os__File_write(os__File f, string s) {
 
 fputs ( s .str ,  f .cfile ) ;
 
 
 }
 void os__File_write_bytes(os__File f, void* data, int size) {
 
 fwrite ( data ,  1 ,  size ,  f .cfile ) ;
 
 
 }
 void os__File_write_bytes_at(os__File f, void* data, int size, int pos) {
 
 fseek ( f .cfile ,  pos ,  SEEK_SET ) ;
 
 fwrite ( data ,  1 ,  size ,  f .cfile ) ;
 
 fseek ( f .cfile ,  0 ,  SEEK_END ) ;
 
 
 }
 void os__File_writeln(os__File f, string s) {
 
 fputs ( s .str ,  f .cfile ) ;
 
 fputs ( "\n" ,  f .cfile ) ;
 
 
 }
 void os__File_flush(os__File f) {
 
 fflush ( f .cfile ) ;
 
 
 }
 void os__File_close(os__File f) {
 
 fclose ( f .cfile ) ;
 
 
 }
 int os__system(string cmd) {
 
int ret= ((int)( 0 ) ) ;
 
 #ifdef _WIN32
 
 ret  =  _wsystem ( string_to_wide( cmd ) ) ;
 
 ;
 
 #else
 
 ret  =  system ( cmd .str ) ;
 
 #endif
 ;
 
 if ( ret == - 1 ) {
 
 os__print_c_errno ( ) ;
 
 }
 ;
 
return  ret ;
 
 
 }
 FILE* os__popen(string path) {
 
 #ifdef _WIN32
 
string mode= tos2((byte*)"rb") ;
 
u16* wpath= string_to_wide( path ) ;
 
return  _wpopen ( wpath ,  string_to_wide( mode ) ) ;
 
 ;
 
 #else
 
byte* cpath= path .str ;
 
return  popen ( cpath ,  "r" ) ;
 
 #endif
 ;
 
 
 }
 string os__exec(string _cmd) {
 
string cmd= _STR("%.*s 2>&1", _cmd.len, _cmd.str) ;
 
FILE* f= os__popen ( cmd ) ;
 
 if ( isnil ( f ) ) {
 
printf( "popen %.*s failed\n", cmd.len, cmd.str ) ;
 
return  tos2((byte*)"") ;
 
 }
 ;
 
byte buf  [1000 ]= STRUCT_DEFAULT_VALUE ;
 
string res= tos2((byte*)"") ;
 
 while ( fgets ( buf ,  1000 ,  f ) != 0 ) {
 
 
 res = string_add(res,  tos ( buf , strlen ( buf ) ) ) ;
 
 }
 ;
 
return  string_trim_space( res ) ;
 
 
 }
 string os__getenv(string key) {
 
 #ifdef _WIN32
 
void* s= _wgetenv ( string_to_wide( key ) ) ;
 
 if ( isnil ( s ) ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  string_from_wide ( s ) ;
 
 ;
 
 #else
 
byte* s= getenv ( key .str ) ;
 
 if ( isnil ( s ) ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  (tos2( s ) ) ;
 
 #endif
 ;
 
 
 }
 int os__setenv(string name, string value, bool overwrite) {
 
 #ifdef _WIN32
 
string format= _STR("%.*s=%.*s", name.len, name.str, value.len, value.str) ;
 
 if ( overwrite ) {
 
return  _putenv ( format .str ) ;
 
 }
 ;
 
return  - 1 ;
 
 ;
 
 #else
 
return  setenv ( name .str ,  value .str ,  overwrite ) ;
 
 #endif
 ;
 
 
 }
 int os__unsetenv(string name) {
 
 #ifdef _WIN32
 
string format= _STR("%.*s=", name.len, name.str) ;
 
return  _putenv ( format .str ) ;
 
 ;
 
 #else
 
return  unsetenv ( name .str ) ;
 
 #endif
 ;
 
 
 }
 bool os__file_exists(string _path) {
 
 #ifdef _WIN32
 
string path= string_replace( _path , tos2((byte*)"/") , tos2((byte*)"\\") ) ;
 
return  _waccess ( string_to_wide( path ) ,  0 ) != - 1 ;
 
 ;
 
 #else
 
return  access ( _path .str ,  0 ) != - 1 ;
 
 #endif
 ;
 
 
 }
 bool os__dir_exists(string path) {
 
 #ifdef _WIN32
 
string _path= string_replace( path , tos2((byte*)"/") , tos2((byte*)"\\") ) ;
 
int attr= ((int)( GetFileAttributes ( string_to_wide( _path ) ) ) ) ;
 
 if ( attr == INVALID_FILE_ATTRIBUTES ) {
 
return  0 ;
 
 }
 ;
 
 if ( ( attr & FILE_ATTRIBUTE_DIRECTORY ) != 0 ) {
 
return  1 ;
 
 }
 ;
 
return  0 ;
 
 ;
 
 #else
 
void* dir= opendir ( path .str ) ;
 
bool res= ! isnil ( dir ) ;
 
 if ( res ) {
 
 closedir ( dir ) ;
 
 }
 ;
 
return  res ;
 
 #endif
 ;
 
 
 }
 void os__mkdir(string path) {
 
 #ifdef _WIN32
 
string _path= string_replace( path , tos2((byte*)"/") , tos2((byte*)"\\") ) ;
 
 if ( string_last_index( _path , tos2((byte*)"\\") ) != - 1 ) {
 
 os__mkdir ( string_all_before_last( _path , tos2((byte*)"\\") ) ) ;
 
 }
 ;
 
 CreateDirectory ( string_to_wide( _path ) ,  0 ) ;
 
 ;
 
 #else
 
 mkdir ( path .str ,  511 ) ;
 
 #endif
 ;
 
 
 }
 void os__rm(string path) {
 
 #ifdef _WIN32
 
 _wremove ( string_to_wide( path ) ) ;
 
 ;
 
 #else
 
 remove ( path .str ) ;
 
 #endif
 ;
 
 
 }
 void os__rmdir(string path) {
 
 #ifndef _WIN32
 
 rmdir ( path .str ) ;
 
 ;
 
 #else
 
 RemoveDirectory ( string_to_wide( path ) ) ;
 
 #endif
 ;
 
 
 }
 void os__print_c_errno() {
 
 
 }
 string os__ext(string path) {
 
int pos= string_last_index( path , tos2((byte*)".") ) ;
 
 if ( pos == - 1 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  string_right( path , pos ) ;
 
 
 }
 string os__dir(string path) {
 
 if (string_eq( path , tos2((byte*)".") ) ) {
 
return  os__getwd ( ) ;
 
 }
 ;
 
int pos= - 1 ;
 
 #ifdef _WIN32
 
 pos  =  string_last_index( path , tos2((byte*)"\\") ) ;
 
 ;
 
 #else
 
 pos  =  string_last_index( path , os__PathSeparator ) ;
 
 #endif
 ;
 
 if ( pos == - 1 ) {
 
return  tos2((byte*)".") ;
 
 }
 ;
 
return  string_left( path , pos ) ;
 
 
 }
 string os__path_sans_ext(string path) {
 
int pos= string_last_index( path , tos2((byte*)".") ) ;
 
 if ( pos == - 1 ) {
 
return  path ;
 
 }
 ;
 
return  string_left( path , pos ) ;
 
 
 }
 string os__basedir(string path) {
 
int pos= string_last_index( path , tos2((byte*)"/") ) ;
 
 if ( pos == - 1 ) {
 
return  path ;
 
 }
 ;
 
return  string_left( path , pos + 1 ) ;
 
 
 }
 string os__filename(string path) {
 
return  string_all_after( path , tos2((byte*)"/") ) ;
 
 
 }
 string os__get_line() {
 
string str= os__get_raw_line ( ) ;
 
 #ifdef _WIN32
 
return  string_trim_right( str , tos2((byte*)"\r\n") ) ;
 
 ;
 
 #else
 
return  string_trim_right( str , tos2((byte*)"\n") ) ;
 
 #endif
 ;
 
 
 }
 string os__get_raw_line() {
 
 #ifdef _WIN32
 
int max= 512 ;
 
u16* buf= ((u16*)( v_malloc ( max * 2 ) ) ) ;
 
void* h_input= GetStdHandle ( os__STD_INPUT_HANDLE ) ;
 
 if ( h_input == os__INVALID_HANDLE_VALUE ) {
 
 v_panic ( tos2((byte*)"get_raw_line() error getting input handle.") ) ;
 
 }
 ;
 
int nr_chars= 0 ;
 
 ReadConsole ( h_input ,  buf ,  max ,  & /*vvar*/  nr_chars ,  0 ) ;
 
 if ( nr_chars == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  string_from_wide2 ( buf , nr_chars ) ;
 
 ;
 
 #else
 
u64 max= ((u64)( 256 ) ) ;
 
byte* buf= v_malloc ( ((int)( max ) ) ) ;
 
int nr_chars= getline ( & /*vvar*/  buf ,  & /*vvar*/  max ,  stdin ) ;
 
 if ( nr_chars == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  (tos( buf ,  nr_chars ) ) ;
 
 #endif
 ;
 
 
 }
 array_string os__get_lines() {
 
string line= tos2((byte*)"") ;
 
array_string inputstr=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 while (1) { 
 
 line  =  os__get_line ( ) ;
 
 if ( ( line .len <= 0 ) ) {
 
 break
 ;
 
 }
 ;
 
 line  =  string_trim_space( line ) ;
 
_PUSH(& inputstr , ( line ), tmp76, string) ;
 
 }
 ;
 
return  inputstr ;
 
 
 }
 string os__get_lines_joined() {
 
string line= tos2((byte*)"") ;
 
string inputstr= tos2((byte*)"") ;
 
 while (1) { 
 
 line  =  os__get_line ( ) ;
 
 if ( ( line .len <= 0 ) ) {
 
 break
 ;
 
 }
 ;
 
 line  =  string_trim_space( line ) ;
 
 inputstr = string_add(inputstr,  line ) ;
 
 }
 ;
 
return  inputstr ;
 
 
 }
 string os__user_os() {
 
 #ifdef __linux__
 
return  tos2((byte*)"linux") ;
 
 #endif
 ;
 
 #ifdef __APPLE__
 
return  tos2((byte*)"mac") ;
 
 #endif
 ;
 
 #ifdef _WIN32
 
return  tos2((byte*)"windows") ;
 
 #endif
 ;
 
 #ifdef __FreeBSD__
 
return  tos2((byte*)"freebsd") ;
 
 #endif
 ;
 
 #ifdef __OpenBSD__
 
return  tos2((byte*)"openbsd") ;
 
 #endif
 ;
 
 #ifdef __NetBSD__
 
return  tos2((byte*)"netbsd") ;
 
 #endif
 ;
 
 #ifdef __DragonFly__
 
return  tos2((byte*)"dragonfly") ;
 
 #endif
 ;
 
 #ifdef _MSC_VER
 
return  tos2((byte*)"windows") ;
 
 #endif
 ;
 
return  tos2((byte*)"unknown") ;
 
 
 }
 string os__home_dir() {
 
string home= os__getenv ( tos2((byte*)"HOME") ) ;
 
 #ifdef _WIN32
 
 home  =  os__getenv ( tos2((byte*)"HOMEDRIVE") ) ;
 
 if ( home .len == 0 ) {
 
 home  =  os__getenv ( tos2((byte*)"SYSTEMDRIVE") ) ;
 
 }
 ;
 
string homepath= os__getenv ( tos2((byte*)"HOMEPATH") ) ;
 
 if ( homepath .len == 0 ) {
 
 homepath  = string_add( tos2((byte*)"\\Users\\") , os__getenv ( tos2((byte*)"USERNAME") ) ) ;
 
 }
 ;
 
 home = string_add(home,  homepath ) ;
 
 #endif
 ;
 
 home = string_add(home,  tos2((byte*)"/") ) ;
 
return  home ;
 
 
 }
 void os__write_file(string path, string text) {
 
Option_os__File tmp81 =  os__create ( path ) ;
 if (!tmp81 .ok) {
 string err = tmp81 . error;
 
 return ;
 
 }
 os__File f = *(os__File*) tmp81 . data;
 ;
 
 os__File_write( f , text ) ;
 
 os__File_close( f ) ;
 
 
 }
 void os__clear() {
 
 printf ( "\x1b[2J" ) ;
 
 printf ( "\x1b[H" ) ;
 
 
 }
 void os__on_segfault(void* f) {
 
 #ifdef _WIN32
 
 return ;
 
 #endif
 ;
 
 #ifdef __APPLE__
  
 struct /*c struct init*/ 

sigaction sa= (struct sigaction) { .sa_mask = 0 , .sa_sigaction = 0 , .sa_flags = 0 } ;
 
 memset ( & /*vvar*/  sa ,  0 ,  sizeof( sigaction) ) ;
 
 sigemptyset ( & /*vvar*/  sa .sa_mask ) ;
 
 sa .sa_sigaction  =  f ;
 
 sa .sa_flags  =  SA_SIGINFO ;
 
 sigaction ( SIGSEGV ,  & /*vvar*/  sa ,  0 ) ;
 
 #endif
 ;
 
 
 }
 string os__executable() {
 
 #ifdef __linux__
 
byte* result= v_malloc ( os__MAX_PATH ) ;
 
int count= ((int)( readlink ( "/proc/self/exe" ,  result ,  os__MAX_PATH ) ) ) ;
 
 if ( count < 0 ) {
 
 v_panic ( tos2((byte*)"error reading /proc/self/exe to get exe path") ) ;
 
 }
 ;
 
return  (tos( result ,  count ) ) ;
 
 #endif
 ;
 
 #ifdef _WIN32
 
int max= 512 ;
 
u16* result= ((u16*)( v_malloc ( max * 2 ) ) ) ;
 
int len= ((int)( GetModuleFileName ( 0 ,  result ,  max ) ) ) ;
 
return  string_from_wide2 ( result , len ) ;
 
 #endif
 ;
 
 #ifdef __APPLE__
 
byte* result= v_malloc ( os__MAX_PATH ) ;
 
void* pid= getpid ( ) ;
 
void* ret= proc_pidpath ( pid ,  result ,  os__MAX_PATH ) ;
 
 if ( ret <= 0 ) {
 
 println ( tos2((byte*)"os.executable() failed") ) ;
 
return  tos2((byte*)".") ;
 
 }
 ;
 
return  (tos2( result ) ) ;
 
 #endif
 ;
 
 #ifdef __FreeBSD__
 
byte* result= v_malloc ( os__MAX_PATH ) ;
 
array_int mib=new_array_from_c_array(4, 4, sizeof(int), (int[]) {  1 ,  14 ,  12 ,  - 1  }) ;
 
int size= os__MAX_PATH ;
 
 sysctl ( mib .data ,  4 ,  result ,  & /*vvar*/  size ,  0 ,  0 ) ;
 
return  (tos2( result ) ) ;
 
 #endif
 ;
 
 #ifdef __OpenBSD__
 
return  ( *(string*) array__get( os__args , 0) ) ;
 
 #endif
 ;
 
 #ifdef __NetBSD__
 
byte* result= v_malloc ( os__MAX_PATH ) ;
 
int count= ((int)( readlink ( "/proc/curproc/exe" ,  result ,  os__MAX_PATH ) ) ) ;
 
 if ( count < 0 ) {
 
 v_panic ( tos2((byte*)"error reading /proc/curproc/exe to get exe path") ) ;
 
 }
 ;
 
return  (tos( result ,  count ) ) ;
 
 #endif
 ;
 
 #ifdef __DragonFly__
 
byte* result= v_malloc ( os__MAX_PATH ) ;
 
int count= ((int)( readlink ( "/proc/curproc/file" ,  result ,  os__MAX_PATH ) ) ) ;
 
 if ( count < 0 ) {
 
 v_panic ( tos2((byte*)"error reading /proc/curproc/file to get exe path") ) ;
 
 }
 ;
 
return  (tos( result ,  count ) ) ;
 
 #endif
 ;
 
return  tos2((byte*)".") ;
 
 
 }
 bool os__is_dir(string path) {
 
 #ifdef _WIN32
 
return  os__dir_exists ( path ) ;
 
 ;
 
 #else
  
 struct /*c struct init*/ 

stat statbuf= (struct stat) { .st_size = 0 , .st_mode = 0 , .st_mtime = 0 } ;
 
byte* cstr= path .str ;
 
 if ( stat ( cstr ,  & /*vvar*/  statbuf ) != 0 ) {
 
return  0 ;
 
 }
 ;
 
return  ( statbuf .st_mode & S_IFMT ) == S_IFDIR ;
 
 #endif
 ;
 
 
 }
 void os__chdir(string path) {
 
 #ifdef _WIN32
 
 _wchdir ( string_to_wide( path ) ) ;
 
 ;
 
 #else
 
 chdir ( path .str ) ;
 
 #endif
 ;
 
 
 }
 string os__getwd() {
 
 #ifdef _WIN32
 
int max= 512 ;
 
u16* buf= ((u16*)( v_malloc ( max * 2 ) ) ) ;
 
 if ( _wgetcwd ( buf ,  max ) == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  string_from_wide ( buf ) ;
 
 ;
 
 #else
 
byte* buf= v_malloc ( 512 ) ;
 
 if ( getcwd ( buf ,  512 ) == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  (tos2( buf ) ) ;
 
 #endif
 ;
 
 
 }
 array_string os__ls(string path) {
 
 #ifdef _WIN32
 
os__win32finddata find_file_data= (os__win32finddata) { .dwFileAttributes = 0 , .nFileSizeHigh = 0 , .nFileSizeLow = 0 , .dwReserved0 = 0 , .dwReserved1 = 0 , .dwFileType = 0 , .dwCreatorType = 0 , .wFinderFlags = 0 } ;
 
array_string dir_files=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( ! os__dir_exists ( path ) ) {
 
printf( "ls() couldnt open dir \"%.*s\" (does not exist).\n", path.len, path.str ) ;
 
return  dir_files ;
 
 }
 ;
 
string path_files= _STR("%.*s\\*", path.len, path.str) ;
 
void* h_find_files= FindFirstFile ( string_to_wide( path_files ) ,  & /*vvar*/  find_file_data ) ;
 
string first_filename= string_from_wide ( ((u16*)( find_file_data .cFileName ) ) ) ;
 
 if (string_ne( first_filename , tos2((byte*)".") )  && string_ne( first_filename , tos2((byte*)"..") ) ) {
 
_PUSH(& dir_files , ( first_filename ), tmp110, string) ;
 
 }
 ;
 
 while ( FindNextFile ( h_find_files ,  & /*vvar*/  find_file_data ) ) {
 
 
string filename= string_from_wide ( ((u16*)( find_file_data .cFileName ) ) ) ;
 
 if (string_ne( filename , tos2((byte*)".") )  && string_ne( filename , tos2((byte*)"..") ) ) {
 
_PUSH(& dir_files , ( string_clone( filename ) ), tmp112, string) ;
 
 }
 ;
 
 }
 ;
 
 FindClose ( h_find_files ) ;
 
return  dir_files ;
 
 ;
 
 #else
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
void* dir= opendir ( path .str ) ;
 
 if ( isnil ( dir ) ) {
 
printf( "ls() couldnt open dir \"%.*s\"\n", path.len, path.str ) ;
 
 os__print_c_errno ( ) ;
 
return  res ;
 
 }
 ;
  
 struct /*c struct init*/ 

dirent* ent= 0 ;
 
 while (1) { 
 
 ent  =  readdir ( dir ) ;
 
 if ( isnil ( ent ) ) {
 
 break
 ;
 
 }
 ;
 
string name= tos_clone ( ent ->d_name ) ;
 
 if (string_ne( name , tos2((byte*)".") )  && string_ne( name , tos2((byte*)"..") )  && string_ne( name , tos2((byte*)"") ) ) {
 
_PUSH(& res , ( name ), tmp117, string) ;
 
 }
 ;
 
 }
 ;
 
 closedir ( dir ) ;
 
return  res ;
 
 #endif
 ;
 
 
 }
 void os__signal(int signum, void* handler) {
 
 signal ( signum ,  handler ) ;
 
 
 }
 int os__fork() {
 
 #ifndef _WIN32
 
void* pid= fork ( ) ;
 
return  pid ;
 
 #endif
 ;
 
 
 }
 int os__wait() {
 
 #ifndef _WIN32
 
void* pid= wait ( 0 ) ;
 
return  pid ;
 
 #endif
 ;
 
 
 }
 int os__file_last_mod_unix(string path) {
  
 struct /*c struct init*/ 

stat attr= (struct stat) { .st_size = 0 , .st_mode = 0 , .st_mtime = 0 } ;
 
 stat ( path .str ,  & /*vvar*/  attr ) ;
 
return  attr .st_mtime ;
 
 
 }
 void os__log(string s) {
 
 
 }
 void os__flush_stdout() {
 
 fflush ( stdout ) ;
 
 
 }
 void os__print_backtrace() {
 
 
 }
 string os__get_error_msg(int code) {
 
void* _ptr_text= strerror ( code ) ;
 
 if ( _ptr_text == 0 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  tos ( _ptr_text , strlen ( _ptr_text ) ) ;
 
 
 }
 f64 math__abs(f64 a) {
 
 if ( a < 0 ) {
 
return  - a ;
 
 }
 ;
 
return  a ;
 
 
 }
 f64 math__acos(f64 a) {
 
return  acos ( a ) ;
 
 
 }
 f64 math__asin(f64 a) {
 
return  asin ( a ) ;
 
 
 }
 f64 math__atan(f64 a) {
 
return  atan ( a ) ;
 
 
 }
 f64 math__atan2(f64 a, f64 b) {
 
return  atan2 ( a ,  b ) ;
 
 
 }
 f64 math__cbrt(f64 a) {
 
return  cbrt ( a ) ;
 
 
 }
 int math__ceil(f64 a) {
 
return  ceil ( a ) ;
 
 
 }
 f64 math__cos(f64 a) {
 
return  cos ( a ) ;
 
 
 }
 f64 math__cosh(f64 a) {
 
return  cosh ( a ) ;
 
 
 }
 f64 math__degrees(f64 radians) {
 
return  radians * ( 180.0 / math__Pi ) ;
 
 
 }
 f64 math__exp(f64 a) {
 
return  exp ( a ) ;
 
 
 }
 array_int math__digits(int _n, int base) {
 
int n= _n ;
 
int sign= 1 ;
 
 if ( n < 0 ) {
 
 sign  =  - 1 ;
 
 n  =  - n ;
 
 }
 ;
 
array_int res=new_array_from_c_array(0, 0, sizeof(int), (int[]) {EMPTY_STRUCT_INIT   }) ;
 
 while ( n != 0 ) {
 
 
_PUSH(& res , ( ( n % base ) * sign ), tmp4, int) ;
 
 n  /=  base ;
 
 }
 ;
 
return  res ;
 
 
 }
 f64 math__erf(f64 a) {
 
return  erf ( a ) ;
 
 
 }
 f64 math__erfc(f64 a) {
 
return  erfc ( a ) ;
 
 
 }
 f64 math__exp2(f64 a) {
 
return  exp2 ( a ) ;
 
 
 }
 int math__recursive_product(int n, int* current_number_ptr) {
 
int m= n / 2 ;
 
 if ( ( m == 0 ) ) {
 
return  * current_number_ptr  +=  2 ;
 
 }
 ;
 
 if ( ( n == 2 ) ) {
 
return  ( * current_number_ptr  +=  2 ) * ( * current_number_ptr  +=  2 ) ;
 
 }
 ;
 
return  math__recursive_product ( ( n - m ) ,& /*11 EXP:"int*" GOT:"int" */ * current_number_ptr ) * math__recursive_product ( m ,& /*11 EXP:"int*" GOT:"int" */ * current_number_ptr ) ;
 
 
 }
 i64 math__factorial(int n) {
 
 if ( n < 0 ) {
 
 v_panic ( tos2((byte*)"factorial: Cannot find factorial of negative number") ) ;
 
 }
 ;
 
 if ( n < 2 ) {
 
return  ((i64)( 1 ) ) ;
 
 }
 ;
 
int r= 1 ;
 
int p= 1 ;
 
int current_number= 1 ;
 
int h= 0 ;
 
int shift= 0 ;
 
int high= 1 ;
 
int len= high ;
 
int log2n= ((int)( math__floor ( math__log2 ( n ) ) ) ) ;
 
 for (
  ;  h != n  ;  ) { 
 
 
 shift  +=  h ;
 
 h  =  n  >>  log2n ;
 
 log2n  -=  1 ;
 
 len  =  high ;
 
 high  =  ( h - 1 ) | 1 ;
 
 len  =  ( high - len ) / 2 ;
 
 if ( ( len > 0 ) ) {
 
 p  *=  math__recursive_product ( len , & /*vvar*/  current_number ) ;
 
 r  *=  p ;
 
 }
 ;
 
 }
 ;
 
return  ((i64)( ( r  <<  shift ) ) ) ;
 
 
 }
 f64 math__floor(f64 a) {
 
return  floor ( a ) ;
 
 
 }
 f64 math__fmod(f64 a, f64 b) {
 
return  fmod ( a ,  b ) ;
 
 
 }
 f64 math__gamma(f64 a) {
 
return  tgamma ( a ) ;
 
 
 }
 i64 math__gcd(i64 a, i64 b) {
 
 if ( a < 0 ) {
 
 a  =  - a ;
 
 }
 ;
 
 if ( b < 0 ) {
 
 b  =  - b ;
 
 }
 ;
 
 while ( b != 0 ) {
 
 
 a  %=  b ;
 
 if ( a == 0 ) {
 
return  b ;
 
 }
 ;
 
 b  %=  a ;
 
 }
 ;
 
return  a ;
 
 
 }
 f64 math__hypot(f64 a, f64 b) {
 
return  hypot ( a ,  b ) ;
 
 
 }
 i64 math__lcm(i64 a, i64 b) {
 
 if ( a == 0 ) {
 
return  a ;
 
 }
 ;
 
i64 res= a * ( b / math__gcd ( b , a ) ) ;
 
 if ( res < 0 ) {
 
return  - res ;
 
 }
 ;
 
return  res ;
 
 
 }
 f64 math__log(f64 a) {
 
return  log ( a ) ;
 
 
 }
 f64 math__log2(f64 a) {
 
return  log2 ( a ) ;
 
 
 }
 f64 math__log10(f64 a) {
 
return  log10 ( a ) ;
 
 
 }
 f64 math__log_gamma(f64 a) {
 
return  lgamma ( a ) ;
 
 
 }
 f64 math__log_n(f64 a, f64 b) {
 
return  log ( a ) / log ( b ) ;
 
 
 }
 f64 math__max(f64 a, f64 b) {
 
 if ( a > b ) {
 
return  a ;
 
 }
 ;
 
return  b ;
 
 
 }
 f64 math__min(f64 a, f64 b) {
 
 if ( a < b ) {
 
return  a ;
 
 }
 ;
 
return  b ;
 
 
 }
 f64 math__pow(f64 a, f64 b) {
 
return  pow ( a ,  b ) ;
 
 
 }
 f64 math__radians(f64 degrees) {
 
return  degrees * ( math__Pi / 180.0 ) ;
 
 
 }
 f64 math__round(f64 f) {
 
return  round ( f ) ;
 
 
 }
 f64 math__sin(f64 a) {
 
return  sin ( a ) ;
 
 
 }
 f64 math__sinh(f64 a) {
 
return  sinh ( a ) ;
 
 
 }
 f64 math__sqrt(f64 a) {
 
return  sqrt ( a ) ;
 
 
 }
 f64 math__tan(f64 a) {
 
return  tan ( a ) ;
 
 
 }
 f64 math__tanh(f64 a) {
 
return  tanh ( a ) ;
 
 
 }
 f64 math__trunc(f64 a) {
 
return  trunc ( a ) ;
 
 
 }
 void rand__seed(int s) {
 
 srand ( s ) ;
 
 
 }
 int rand__next(int max) {
 
return  rand ( ) % max ;
 
 
 }
 string vweb_dot_tmpl__compile_template(string path) {
 
Option_string tmp1 =  os__read_file ( path ) ;
 if (!tmp1 .ok) {
 string err = tmp1 . error;
 
 v_panic ( tos2((byte*)"html failed") ) ;
 
return  tos2((byte*)"") ;
 
 }
 string html = *(string*) tmp1 . data;
 ;
 
string header= tos2((byte*)"") ;
 
 if ( os__file_exists ( tos2((byte*)"header.html") ) ) {
 
Option_string tmp3 =  os__read_file ( tos2((byte*)"header.html") ) ;
 if (!tmp3 .ok) {
 string err = tmp3 . error;
 
 v_panic ( tos2((byte*)"html failed") ) ;
 
return  tos2((byte*)"") ;
 
 }
 string h = *(string*) tmp3 . data;
 ;
 
 header  =  string_replace( h , tos2((byte*)"\'") , tos2((byte*)"\"") ) ;
 
 }
 ;
 
array_string lines= string_split_into_lines( html ) ;
 
strings__Builder s= strings__new_builder ( 1000 ) ;
 
string base= string_replace( string_all_after( path , tos2((byte*)"/") ) , tos2((byte*)".html") , tos2((byte*)"") ) ;
 
 strings__Builder_writeln(& /* ? */ s , _STR("module main import strings fn %.*s_view() string {   // this line will get removed becase only function body is embedded \nmut sb := strings.new_builder(%d)\nheader := \'%.*s\' \n_ := header \n//footer := \'footer\' \n", base.len, base.str, lines .len * 30, header.len, header.str) ) ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_START ) ;
 
bool in_css= 0 ;
 
 array_string tmp8 =  lines;
 ;
for (int tmp9 = 0; tmp9 < tmp8 .len; tmp9 ++) {
 string _line = ((string *) tmp8.data)[tmp9];
 
 
string line= string_trim_space( _line ) ;
 
 if (string_eq( line , tos2((byte*)"<style>") ) ) {
 
 in_css  =  1 ;
 
 }
  else  if (string_eq( line , tos2((byte*)"</style>") ) ) {
 
 in_css  =  0 ;
 
 }
 ;
 
 if ( string_contains( line , tos2((byte*)"@if ") ) ) {
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_END ) ;
 
int pos= string_index( line , tos2((byte*)"@if") ) ;
 
 strings__Builder_writeln(& /* ? */ s ,string_add(string_add( tos2((byte*)"if ") , string_right( line , pos + 4 ) ) , tos2((byte*)"{") ) ) ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_START ) ;
 
 }
  else  if ( string_contains( line , tos2((byte*)"@end") ) ) {
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_END ) ;
 
 strings__Builder_writeln(& /* ? */ s , tos2((byte*)"}") ) ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_START ) ;
 
 }
  else  if ( string_contains( line , tos2((byte*)"@else") ) ) {
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_END ) ;
 
 strings__Builder_writeln(& /* ? */ s , tos2((byte*)" } else { ") ) ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_START ) ;
 
 }
  else  if ( string_contains( line , tos2((byte*)"@for") ) ) {
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_END ) ;
 
int pos= string_index( line , tos2((byte*)"@for") ) ;
 
 strings__Builder_writeln(& /* ? */ s ,string_add(string_add( tos2((byte*)"for ") , string_right( line , pos + 4 ) ) , tos2((byte*)"{") ) ) ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_START ) ;
 
 }
  else  if ( ! in_css  &&  string_contains( line , tos2((byte*)".") )  &&  string_ends_with( line , tos2((byte*)"{") ) ) {
 
string class= string_find_between( line , tos2((byte*)".") , tos2((byte*)"{") ) ;
 
 strings__Builder_writeln(& /* ? */ s , _STR("<div class=\"%.*s\">", class.len, class.str) ) ;
 
 }
  else  if ( ! in_css  && string_eq( line , tos2((byte*)"}") ) ) {
 
 strings__Builder_writeln(& /* ? */ s , tos2((byte*)"</div>") ) ;
 
 }
  else { 
 
 strings__Builder_writeln(& /* ? */ s , string_replace( string_replace( line , tos2((byte*)"@") , tos2((byte*)"\x24") ) , tos2((byte*)"\'") , tos2((byte*)"\"") ) ) ;
 
 }
 ;
 
 }
 ;
 
 strings__Builder_writeln(& /* ? */ s , vweb_dot_tmpl__STR_END ) ;
 
 strings__Builder_writeln(& /* ? */ s , tos2((byte*)"tmpl_res := sb.str() ") ) ;
 
 strings__Builder_writeln(& /* ? */ s , tos2((byte*)"return tmpl_res }") ) ;
 
return  strings__Builder_str( s ) ;
 
 
 }
 void time__remove_me_when_c_bug_is_fixed() {
 
 
 }
 time__Time time__now() {
 
void* t= time ( 0 ) ;
  
 struct /*c struct init*/ 

tm* now= 0 ;
 
 now  =  localtime ( & /*vvar*/  t ) ;
 
return  time__convert_ctime (* now ) ;
 
 
 }
 time__Time time__random() {
 
int now_unix= time__now ( ) .uni ;
 
int rand_unix= rand__next ( now_unix ) ;
 
return  time__unix ( rand_unix ) ;
 
 
 }
 time__Time time__unix(int abs) {
 
int d= abs / time__secondsPerDay ;
 
int n= d / time__daysPer400Years ;
 
int y= 400 * n ;
 
 d  -=  time__daysPer400Years * n ;
 
 n  =  d / time__daysPer100Years ;
 
 n  -=  n  >>  2 ;
 
 y  +=  100 * n ;
 
 d  -=  time__daysPer100Years * n ;
 
 n  =  d / time__daysPer4Years ;
 
 y  +=  4 * n ;
 
 d  -=  time__daysPer4Years * n ;
 
 n  =  d / 365 ;
 
 n  -=  n  >>  2 ;
 
 y  +=  n ;
 
 d  -=  365 * n ;
 
int yday= ((int)( d ) ) ;
 
int day= yday ;
 
int year= abs / ((int)( 3.154e+7 ) ) + 1970 ;
 
int hour= ((int)( abs % time__secondsPerDay ) ) / time__secondsPerHour ;
 
int minute= ((int)( abs % time__secondsPerHour ) ) / time__secondsPerMinute ;
 
int second= ((int)( abs % time__secondsPerMinute ) ) ;
 
 if ( time__is_leap_year ( year ) ) {
 
 if ( day > 31 + 29 - 1 ) {
 
 day -- ;
 
 }
  else  if ( day == 31 + 29 - 1 ) {
 
 day  =  29 ;
 
return  (struct time__Time) { .year =  year , .month =  2 , .day =  day , .hour =  hour , .minute =  minute , .second =  second , .uni = 0 } ;
 
 }
 ;
 
 }
 ;
 
int month= day / 31 ;
 
int begin= 0 ;
 
int end= ((int)( ( *(int*) array__get( time__daysBefore , month + 1) ) ) ) ;
 
 if ( day >= end ) {
 
 month ++ ;
 
 begin  =  end ;
 
 }
  else { 
 
 begin  =  ((int)( ( *(int*) array__get( time__daysBefore , month) ) ) ) ;
 
 }
 ;
 
 month ++ ;
 
 day  =  day - begin + 1 ;
 
return  (time__Time) { .year =  year , .month =  month , .day =  day , .hour =  hour , .minute =  minute , .second =  second , .uni = 0 } ;
 
 
 }
 time__Time time__convert_ctime(struct /*TM*/ tm t) {
 
return  (time__Time) { .year =  t .tm_year + 1900 , .month =  t .tm_mon + 1 , .day =  t .tm_mday , .hour =  t .tm_hour , .minute =  t .tm_min , .second =  t .tm_sec , .uni =  mktime ( & /*vvar*/  t ) } ;
 
 
 }
 string time__Time_format_ss(time__Time t) {
 
return  _STR("%d-%02d-%02d %02d:%02d:%02d", t .year, t .month, t .day, t .hour, t .minute, t .second) ;
 
 
 }
 string time__Time_format(time__Time t) {
 
return  _STR("%d-%02d-%02d %02d:%02d", t .year, t .month, t .day, t .hour, t .minute) ;
 
 
 }
 string time__Time_smonth(time__Time t) {
 
int i= t .month - 1 ;
 
return  string_substr( time__Months , i * 3 , ( i + 1 ) * 3 ) ;
 
 
 }
 string time__Time_hhmm(time__Time t) {
 
return  _STR("%02d:%02d", t .hour, t .minute) ;
 
 
 }
 string time__Time_hhmm12(time__Time t) {
 
string am= tos2((byte*)"am") ;
 
int hour= t .hour ;
 
 if ( t .hour > 11 ) {
 
 am  =  tos2((byte*)"pm") ;
 
 }
 ;
 
 if ( t .hour > 12 ) {
 
 hour  =  hour - 12 ;
 
 }
 ;
 
 if ( t .hour == 0 ) {
 
 hour  =  12 ;
 
 }
 ;
 
return  _STR("%d:%02d %.*s", hour, t .minute, am.len, am.str) ;
 
 
 }
 string time__Time_hhmmss(time__Time t) {
 
return  _STR("%02d:%02d:%02d", t .hour, t .minute, t .second) ;
 
 
 }
 string time__Time_ymmdd(time__Time t) {
 
return  _STR("%d-%02d-%02d", t .year, t .month, t .day) ;
 
 
 }
 string time__Time_md(time__Time t) {
 
string s= _STR("%.*s %d", time__Time_smonth( t ).len, time__Time_smonth( t ).str, t .day) ;
 
return  s ;
 
 
 }
 string time__Time_clean(time__Time t) {
 
time__Time nowe= time__now ( ) ;
 
 if ( t .month == nowe .month  &&  t .year == nowe .year  &&  t .day == nowe .day ) {
 
return  time__Time_hhmm( t ) ;
 
 }
 ;
 
 if ( t .year == nowe .year ) {
 
return  _STR("%.*s %d %.*s", time__Time_smonth( t ).len, time__Time_smonth( t ).str, t .day, time__Time_hhmm( t ).len, time__Time_hhmm( t ).str) ;
 
 }
 ;
 
return  time__Time_format( t ) ;
 
 
 }
 string time__Time_clean12(time__Time t) {
 
time__Time nowe= time__now ( ) ;
 
 if ( t .month == nowe .month  &&  t .year == nowe .year  &&  t .day == nowe .day ) {
 
return  time__Time_hhmm12( t ) ;
 
 }
 ;
 
 if ( t .year == nowe .year ) {
 
return  _STR("%.*s %d %.*s", time__Time_smonth( t ).len, time__Time_smonth( t ).str, t .day, time__Time_hhmm12( t ).len, time__Time_hhmm12( t ).str) ;
 
 }
 ;
 
return  time__Time_format( t ) ;
 
 
 }
 time__Time time__parse(string s) {
 
int pos= string_index( s , tos2((byte*)" ") ) ;
 
 if ( pos <= 0 ) {
 
 println ( tos2((byte*)"bad time format") ) ;
 
return  time__now ( ) ;
 
 }
 ;
 
string symd= string_left( s , pos ) ;
 
array_string ymd= string_split( symd , tos2((byte*)"-") ) ;
 
 if ( ymd .len != 3 ) {
 
 println ( tos2((byte*)"bad time format") ) ;
 
return  time__now ( ) ;
 
 }
 ;
 
string shms= string_right( s , pos ) ;
 
array_string hms= string_split( shms , tos2((byte*)":") ) ;
 
string hour= ( *(string*) array__get( hms , 0) ) ;
 
string minute= ( *(string*) array__get( hms , 1) ) ;
 
string second= ( *(string*) array__get( hms , 2) ) ;
 
return  time__new_time ( (time__Time) { .year =  string_int( ( *(string*) array__get( ymd , 0) ) ) , .month =  string_int( ( *(string*) array__get( ymd , 1) ) ) , .day =  string_int( ( *(string*) array__get( ymd , 2) ) ) , .hour =  string_int( hour ) , .minute =  string_int( minute ) , .second =  string_int( second ) , .uni = 0 } ) ;
 
 
 }
 time__Time time__new_time(time__Time t) {
 
return  (time__Time){ .uni =  time__Time_calc_unix(& /* ? */ t ) , .year = t . year, .month = t . month, .day = t . day, .hour = t . hour, .minute = t . minute, .second = t . second, } ;
 
 
 }
 int time__Time_calc_unix(time__Time* t) {
 
 if ( t ->uni != 0 ) {
 
return  t ->uni ;
 
 }


struct /*TM*/ tm tt= (struct tm) { .tm_sec =  t ->second , .tm_min =  t ->minute , .tm_hour =  t ->hour , .tm_mday =  t ->day , .tm_mon =  t ->month - 1 , .tm_year =  t ->year - 1900 } ;
 
return  mktime ( & /*vvar*/  tt ) ;
 
 
 }
 time__Time time__Time_add_seconds(time__Time t, int seconds) {
 
return  time__unix ( t .uni + seconds ) ;
 
 
 }
 int time__since(time__Time t) {
 
return  0 ;
 
 
 }
 string time__Time_relative(time__Time t) {
 
time__Time now= time__now ( ) ;
 
int secs= now .uni - t .uni ;
 
 if ( secs <= 30 ) {
 
return  tos2((byte*)"now") ;
 
 }
 ;
 
 if ( secs < 60 ) {
 
return  tos2((byte*)"1m") ;
 
 }
 ;
 
 if ( secs < 3600 ) {
 
return  _STR("%dm", secs / 60) ;
 
 }
 ;
 
 if ( secs < 3600 * 24 ) {
 
return  _STR("%dh", secs / 3600) ;
 
 }
 ;
 
 if ( secs < 3600 * 24 * 5 ) {
 
return  _STR("%dd", secs / 3600 / 24) ;
 
 }
 ;
 
 if ( secs > 3600 * 24 * 10000 ) {
 
return  tos2((byte*)"") ;
 
 }
 ;
 
return  time__Time_md( t ) ;
 
 
 }
 int time__day_of_week(int y, int m, int d) {
 
return  0 ;
 
 
 }
 int time__Time_day_of_week(time__Time t) {
 
return  time__day_of_week ( t .year , t .month , t .day ) ;
 
 
 }
 string time__Time_weekday_str(time__Time t) {
 
int i= time__Time_day_of_week( t ) - 1 ;
 
return  string_substr( time__Days , i * 3 , ( i + 1 ) * 3 ) ;
 
 
 }
 i64 time__ticks() {
 
 #ifdef _WIN32
 
return  GetTickCount ( ) ;
 
 ;
 
 #else
  
 struct /*c struct init*/ 

timeval ts= (struct timeval) { .tv_sec = 0 , .tv_usec = 0 } ;
 
 gettimeofday ( & /*vvar*/  ts ,  0 ) ;
 
return  ts .tv_sec * 1000 + ( ts .tv_usec / 1000 ) ;
 
 #endif
 ;
 
 
 }
 void time__sleep(int seconds) {
 
 #ifdef _WIN32
 
 _sleep ( seconds * 1000 ) ;
 
 ;
 
 #else
 
 sleep ( seconds ) ;
 
 #endif
 ;
 
 
 }
 void time__usleep(int n) {
 
 #ifdef _WIN32
 
 ;
 
 #else
 
 usleep ( n ) ;
 
 #endif
 ;
 
 
 }
 void time__sleep_ms(int n) {
 
 #ifdef _WIN32
 
 Sleep ( n ) ;
 
 ;
 
 #else
 
 usleep ( n * 1000 ) ;
 
 #endif
 ;
 
 
 }
 bool time__is_leap_year(int year) {
 
return  ( year % 4 == 0 )  &&  ( year % 100 != 0  ||  year % 400 == 0 ) ;
 
 
 }
 Option_int time__days_in_month(int month, int year) {
 
 if ( month > 12  ||  month < 1 ) {
 
return  v_error ( _STR("Invalid month: %d", month) ) ;
 
 }
 ;
 
int extra= ( month == 2  &&  time__is_leap_year ( year ) ) ? ( 1 ) : ( 0 ) ;
 
int res= ( *(int*) array__get( time__MonthDays , month - 1) ) + extra ;
 
int tmp56 = OPTION_CAST(int)( res); return opt_ok(&tmp56, sizeof(int)) ;
 
 
 }
 CGen* new_cgen(string out_name_c) {
 
string path= _STR(".%.*s", out_name_c.len, out_name_c.str) ;
 
Option_os__File tmp2 =  os__create ( path ) ;
 if (!tmp2 .ok) {
 string err = tmp2 . error;
 
printf( "failed to create %.*s\n", path.len, path.str ) ;
 
return  ALLOC_INIT(CGen, { .out_path = tos("", 0) , .typedefs = new_array(0, 1, sizeof(string)) , .type_aliases = new_array(0, 1, sizeof(string)) , .includes = new_array(0, 1, sizeof(string)) , .types = new_array(0, 1, sizeof(string)) , .thread_args = new_array(0, 1, sizeof(string)) , .thread_fns = new_array(0, 1, sizeof(string)) , .consts = new_array(0, 1, sizeof(string)) , .fns = new_array(0, 1, sizeof(string)) , .so_fns = new_array(0, 1, sizeof(string)) , .consts_init = new_array(0, 1, sizeof(string)) , .is_user = 0 , .lines = new_array(0, 1, sizeof(string)) , .nogen = 0 , .tmp_line = tos("", 0) , .cur_line = tos("", 0) , .prev_line = tos("", 0) , .is_tmp = 0 , .fn_main = tos("", 0) , .stash = tos("", 0) , .file = tos("", 0) , .line = 0 , .line_directives = 0 } ) ;
 
 }
 os__File out = *(os__File*) tmp2 . data;
 ;
 
CGen* gen= ALLOC_INIT(CGen, { .out_path =  path , .out =  out , .lines =  _make ( 0 , 1000 , sizeof( string) ) , .typedefs = new_array(0, 1, sizeof(string)) , .type_aliases = new_array(0, 1, sizeof(string)) , .includes = new_array(0, 1, sizeof(string)) , .types = new_array(0, 1, sizeof(string)) , .thread_args = new_array(0, 1, sizeof(string)) , .thread_fns = new_array(0, 1, sizeof(string)) , .consts = new_array(0, 1, sizeof(string)) , .fns = new_array(0, 1, sizeof(string)) , .so_fns = new_array(0, 1, sizeof(string)) , .consts_init = new_array(0, 1, sizeof(string)) , .is_user = 0 , .nogen = 0 , .tmp_line = tos("", 0) , .cur_line = tos("", 0) , .prev_line = tos("", 0) , .is_tmp = 0 , .fn_main = tos("", 0) , .stash = tos("", 0) , .file = tos("", 0) , .line = 0 , .line_directives = 0 } ) ;
 
return  gen ;
 
 
 }
 void CGen_genln(CGen* g, string s) {
 
 if ( g ->nogen  ||  g ->pass != main__Pass_main ) {
 
 return ;
 
 }
 ;
 
 if ( g ->is_tmp ) {
 
 g ->tmp_line  =  _STR("%.*s %.*s\n", g ->tmp_line.len, g ->tmp_line.str, s.len, s.str) ;
 
 return ;
 
 }
 ;
 
 g ->cur_line  =  _STR("%.*s %.*s", g ->cur_line.len, g ->cur_line.str, s.len, s.str) ;
 
 if (string_ne( g ->cur_line , tos2((byte*)"") ) ) {
 
 if ( g ->line_directives  && string_ne( string_trim_space( g ->cur_line ) , tos2((byte*)"") ) ) {
 
_PUSH(& g ->lines , ( _STR("#line %d \"%.*s\"", g ->line, g ->file.len, g ->file.str) ), tmp4, string) ;
 
 }
 ;
 
_PUSH(& g ->lines , ( g ->cur_line ), tmp5, string) ;
 
 g ->prev_line  =  g ->cur_line ;
 
 g ->cur_line  =  tos2((byte*)"") ;
 
 }
 ;
 
 
 }
 void CGen_gen(CGen* g, string s) {
 
 if ( g ->nogen  ||  g ->pass != main__Pass_main ) {
 
 return ;
 
 }
 ;
 
 if ( g ->is_tmp ) {
 
 g ->tmp_line  =  _STR("%.*s %.*s", g ->tmp_line.len, g ->tmp_line.str, s.len, s.str) ;
 
 }
  else { 
 
 g ->cur_line  =  _STR("%.*s %.*s", g ->cur_line.len, g ->cur_line.str, s.len, s.str) ;
 
 }
 ;
 
 
 }
 void CGen_resetln(CGen* g, string s) {
 
 if ( g ->nogen  ||  g ->pass != main__Pass_main ) {
 
 return ;
 
 }
 ;
 
 if ( g ->is_tmp ) {
 
 g ->tmp_line  =  s ;
 
 }
  else { 
 
 g ->cur_line  =  s ;
 
 }
 ;
 
 
 }
 void CGen_save(CGen* g) {
 
string s= array_string_join( g ->lines , tos2((byte*)"\n") ) ;
 
 os__File_writeln( g ->out , s ) ;
 
 os__File_close( g ->out ) ;
 
 
 }
 void CGen_start_tmp(CGen* g) {
 
 if ( g ->is_tmp ) {
 
 println ( g ->tmp_line ) ;
 
printf( "start_tmp() already started. cur_line=\"%.*s\"\n", g ->cur_line.len, g ->cur_line.str ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 g ->tmp_line  =  tos2((byte*)"") ;
 
 g ->is_tmp  =  1 ;
 
 
 }
 string CGen_end_tmp(CGen* g) {
 
 g ->is_tmp  =  0 ;
 
string res= g ->tmp_line ;
 
 g ->tmp_line  =  tos2((byte*)"") ;
 
return  res ;
 
 
 }
 int CGen_add_placeholder(CGen* g) {
 
 if ( g ->is_tmp ) {
 
return  g ->tmp_line .len ;
 
 }
 ;
 
return  g ->cur_line .len ;
 
 
 }
 void CGen_set_placeholder(CGen* g, int pos, string val) {
 
 if ( g ->nogen  ||  g ->pass != main__Pass_main ) {
 
 return ;
 
 }
 ;
 
 if ( g ->is_tmp ) {
 
string left= string_left( g ->tmp_line , pos ) ;
 
string right= string_right( g ->tmp_line , pos ) ;
 
 g ->tmp_line  =  _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str, right.len, right.str) ;
 
 return ;
 
 }
 ;
 
string left= string_left( g ->cur_line , pos ) ;
 
string right= string_right( g ->cur_line , pos ) ;
 
 g ->cur_line  =  _STR("%.*s%.*s%.*s", left.len, left.str, val.len, val.str, right.len, right.str) ;
 
 
 }
 int CGen_add_placeholder2(CGen* g) {
 
 if ( g ->is_tmp ) {
 
 println ( tos2((byte*)"tmp in addp2") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
_PUSH(& g ->lines , ( tos2((byte*)"") ), tmp12, string) ;
 
return  g ->lines .len - 1 ;
 
 
 }
 void CGen_set_placeholder2(CGen* g, int pos, string val) {
 
 if ( g ->nogen  ||  g ->pass != main__Pass_main ) {
 
 return ;
 
 }
 ;
 
 if ( g ->is_tmp ) {
 
 println ( tos2((byte*)"tmp in setp2") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
  
 string tmp13 =  val; 

array_set(&/*q*/ g ->lines , pos , & tmp13) ;
 
 
 }
 void CGen_insert_before(CGen* g, string val) {
 
string prev= ( *(string*) array__get( g ->lines , g ->lines .len - 1) ) ;
  
 string tmp17 =  _STR("%.*s \n %.*s \n", prev.len, prev.str, val.len, val.str); 

array_set(&/*q*/ g ->lines , g ->lines .len - 1 , & tmp17) ;
 
 
 }
 void CGen_register_thread_fn(CGen* g, string wrapper_name, string wrapper_text, string struct_text) {
 
 array_string tmp18 =  g ->thread_args;
 ;
for (int tmp19 = 0; tmp19 < tmp18 .len; tmp19 ++) {
 string arg = ((string *) tmp18.data)[tmp19];
 
 
 if ( string_contains( arg , wrapper_name ) ) {
 
 return ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& g ->thread_args , ( struct_text ), tmp20, string) ;
 
_PUSH(& g ->thread_args , ( wrapper_text ), tmp21, string) ;
 
 
 }
 string V_prof_counters(V* c) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 array_Type tmp23 =  c ->table ->types;
 ;
for (int tmp24 = 0; tmp24 < tmp23 .len; tmp24 ++) {
 Type typ = ((Type *) tmp23.data)[tmp24];
 
 
 array_Fn tmp25 =  typ .methods;
 ;
for (int tmp26 = 0; tmp26 < tmp25 .len; tmp26 ++) {
 Fn f = ((Fn *) tmp25.data)[tmp26];
 
 
_PUSH(& res , ( _STR("double %.*s_time;", Table_cgen_name( c ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).len, Table_cgen_name( c ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).str) ), tmp27, string) ;
 
 }
 ;
 
 }
 ;
 
return  array_string_join( res , tos2((byte*)";\n") ) ;
 
 
 }
 string Parser_print_prof_counters(Parser* p) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 array_Type tmp29 =  p ->table ->types;
 ;
for (int tmp30 = 0; tmp30 < tmp29 .len; tmp30 ++) {
 Type typ = ((Type *) tmp29.data)[tmp30];
 
 
 array_Fn tmp31 =  typ .methods;
 ;
for (int tmp32 = 0; tmp32 < tmp31 .len; tmp32 ++) {
 Fn f = ((Fn *) tmp31.data)[tmp32];
 
 
string counter= _STR("%.*s_time", Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).len, Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).str) ;
 
_PUSH(& res , ( _STR("if (%.*s) printf(\"%%%%f : %.*s \\n\", %.*s);", counter.len, counter.str, Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).len, Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ).str, counter.len, counter.str) ), tmp34, string) ;
 
 }
 ;
 
 }
 ;
 
return  array_string_join( res , tos2((byte*)";\n") ) ;
 
 
 }
 void Parser_gen_type(Parser* p, string s) {
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 return ;
 
 }
 ;
 
_PUSH(& p ->cgen ->types , ( s ), tmp35, string) ;
 
 
 }
 void Parser_gen_typedef(Parser* p, string s) {
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 return ;
 
 }
 ;
 
_PUSH(& p ->cgen ->typedefs , ( s ), tmp36, string) ;
 
 
 }
 void Parser_gen_type_alias(Parser* p, string s) {
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 return ;
 
 }
 ;
 
_PUSH(& p ->cgen ->type_aliases , ( s ), tmp37, string) ;
 
 
 }
 void CGen_add_to_main(CGen* g, string s) {
 
 println ( tos2((byte*)"add to main") ) ;
 
 g ->fn_main  = string_add( g ->fn_main , s ) ;
 
 
 }
 void build_thirdparty_obj_file(string flag) {
 
string obj_path= string_all_after( flag , tos2((byte*)" ") ) ;
 
 if ( os__file_exists ( obj_path ) ) {
 
 return ;
 
 }
 ;
 
printf( "%.*s not found, building it...\n", obj_path.len, obj_path.str ) ;
 
string parent= string_trim_space( string_all_before_last( obj_path , tos2((byte*)"/") ) ) ;
 
array_string files= os__ls ( parent ) ;
 
string cfiles= tos2((byte*)"") ;
 
 array_string tmp42 =  files;
 ;
for (int tmp43 = 0; tmp43 < tmp42 .len; tmp43 ++) {
 string file = ((string *) tmp42.data)[tmp43];
 
 
 if ( string_ends_with( file , tos2((byte*)".c") ) ) {
 
 cfiles = string_add(cfiles, string_add(string_add(string_add( parent , tos2((byte*)"/") ) , file ) , tos2((byte*)" ") ) ) ;
 
 }
 ;
 
 }
 ;
 
string cc= (string_eq( os__user_os ( ) , tos2((byte*)"windows") ) ) ? ( tos2((byte*)"gcc") ) : ( tos2((byte*)"cc") ) ;
 
string res= os__exec ( _STR("%.*s -fPIC -c -o %.*s %.*s", cc.len, cc.str, obj_path.len, obj_path.str, cfiles.len, cfiles.str) ) ;
 
 println ( res ) ;
 
 
 }
 void Parser_comp_time(Parser* p) {
 
 Parser_check( p , main__Token_dollar ) ;
 
 if ( p ->tok == main__Token_key_if ) {
 
 Parser_check( p , main__Token_key_if ) ;
 
 Parser_fspace( p ) ;
 
bool not= p ->tok == main__Token_not ;
 
 if ( not ) {
 
 Parser_check( p , main__Token_not ) ;
 
 }
 ;
 
string name= Parser_check_name( p ) ;
 
 Parser_fspace( p ) ;
 
 if (_IN(string,  name ,  main__SupportedPlatforms ) ) {
 
string ifdef_name= os_name_to_ifdef ( name ) ;
 
 if ( not ) {
 
 Parser_genln( p , _STR("#ifndef %.*s", ifdef_name.len, ifdef_name.str) ) ;
 
 }
  else { 
 
 Parser_genln( p , _STR("#ifdef %.*s", ifdef_name.len, ifdef_name.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_statements_no_rcbr( p ) ;
 
 if ( ! ( p ->tok == main__Token_dollar  &&  Parser_peek( p ) == main__Token_key_else ) ) {
 
 Parser_genln( p , tos2((byte*)"#endif") ) ;
 
 }
 ;
 
 }
  else { 
 
 println ( tos2((byte*)"Supported platforms:") ) ;
 
 println (array_string_str( main__SupportedPlatforms ) ) ;
 
 Parser_error( p , _STR("unknown platform `%.*s`", name.len, name.str) ) ;
 
 }
 ;
 
 }
  else  if ( p ->tok == main__Token_key_for ) {
 
 Parser_next( p ) ;
 
string name= Parser_check_name( p ) ;
 
 if (string_ne( name , tos2((byte*)"field") ) ) {
 
 Parser_error( p , tos2((byte*)"for field only") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_key_in ) ;
 
 Parser_check_name( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 Parser_check_name( p ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
string res_name= Parser_check_name( p ) ;
 
 println ( res_name ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 Parser_check( p , main__Token_dollar ) ;
 
 Parser_check( p , main__Token_name ) ;
 
 Parser_check( p , main__Token_assign ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
 Parser_bool_expression( p ) ;
 
string val= CGen_end_tmp( p ->cgen ) ;
 
 println ( val ) ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
 }
  else  if ( p ->tok == main__Token_key_else ) {
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_genln( p , tos2((byte*)"#else") ) ;
 
 Parser_statements_no_rcbr( p ) ;
 
 Parser_genln( p , tos2((byte*)"#endif") ) ;
 
 }
  else  if ( p ->tok == main__Token_name  && string_eq( p ->lit , tos2((byte*)"vweb") ) ) {
 
string path=string_add( p ->cur_fn ->name , tos2((byte*)".html") ) ;
 
 if ( p ->pref ->is_debug ) {
 
printf( "compiling tmpl %.*s\n", path.len, path.str ) ;
 
 }
 ;
 
 if ( ! os__file_exists ( path ) ) {
 
 Parser_error( p , _STR("vweb HTML template \"%.*s\" not found", path.len, path.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_name ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 Parser_check( p , main__Token_name ) ;
 
 Parser_check( p , main__Token_lpar ) ;
 
 Parser_check( p , main__Token_rpar ) ;
 
string v_code= vweb_dot_tmpl__compile_template ( path ) ;
 
 if ( os__file_exists ( tos2((byte*)".vwebtmpl.v") ) ) {
 
 os__rm ( tos2((byte*)".vwebtmpl.v") ) ;
 
 }
 ;
 
 os__write_file ( tos2((byte*)".vwebtmpl.v") , string_clone( v_code ) ) ;
 
 Parser_genln( p , tos2((byte*)"") ) ;
 
int pos= p ->cgen ->lines .len - 1 ;
 
Parser pp= V_new_parser( p ->v , tos2((byte*)".vwebtmpl.v") , main__Pass_main ) ;
 
 if ( ! p ->pref ->is_debug ) {
 
 os__rm ( tos2((byte*)".vwebtmpl.v") ) ;
 
 }
 ;
 
 pp .is_vweb  =  1 ;
 
 pp .cur_fn  =  p ->cur_fn ;
 
 Parser_parse(& /* ? */ pp ) ;
 
string tmpl_fn_body= string_clone( array_string_join( array_slice( p ->cgen ->lines , pos + 2 , p ->cgen ->lines .len ) , tos2((byte*)"\n") ) ) ;
 
int end_pos= string_last_index( tmpl_fn_body , tos2((byte*)"Builder_str( sb )") ) + 19 ;
 
 p ->cgen ->lines  =  array_left( p ->cgen ->lines , pos ) ;
 
 Parser_genln( p , tos2((byte*)"/////////////////// tmpl start") ) ;
 
 Parser_genln( p , string_left( tmpl_fn_body , end_pos ) ) ;
 
 Parser_genln( p , tos2((byte*)"/////////////////// tmpl end") ) ;
 
Var receiver= ( *(Var*) array__get( p ->cur_fn ->args , 0) ) ;
 
string dot= ( receiver .is_mut ) ? ( tos2((byte*)"->") ) : ( tos2((byte*)".") ) ;
 
 Parser_genln( p , _STR("vweb__Context_html(%.*s %.*s vweb, tmpl_res)", receiver .name.len, receiver .name.str, dot.len, dot.str) ) ;
 
 }
  else { 
 
 Parser_error( p , tos2((byte*)"bad comptime expr") ) ;
 
 }
 ;
 
 
 }
 void Parser_chash(Parser* p) {
 
string hash= string_trim_space( p ->lit ) ;
 
 Parser_next( p ) ;
 
bool is_sig= Parser_is_sig( p ) ;
 
 if ( string_starts_with( hash , tos2((byte*)"flag ") ) ) {
 
string flag= string_right( hash , 5 ) ;
 
 if ( string_contains( hash , tos2((byte*)"linux") )  &&  p ->os != main__OS_linux ) {
 
 return ;
 
 }
  else  if ( string_contains( hash , tos2((byte*)"darwin") )  &&  p ->os != main__OS_mac ) {
 
 return ;
 
 }
  else  if ( string_contains( hash , tos2((byte*)"windows") )  &&  ( p ->os != main__OS_windows  &&  p ->os != main__OS_msvc ) ) {
 
 return ;
 
 }
 ;
 
 if ( string_contains( flag , tos2((byte*)"linux") )  ||  string_contains( flag , tos2((byte*)"darwin") )  ||  string_contains( flag , tos2((byte*)"windows") ) ) {
 
int pos= string_index( flag , tos2((byte*)" ") ) ;
 
 flag  =  string_right( flag , pos ) ;
 
 }
 ;
 
bool has_vroot= string_contains( flag , tos2((byte*)"@VROOT") ) ;
 
 flag  =  string_replace( string_trim_space( flag ) , tos2((byte*)"@VROOT") , p ->vroot ) ;
 
 if ( array_string_contains( p ->table ->flags , flag ) ) {
 
 return ;
 
 }
 ;
 
bool has_vmod= string_contains( flag , tos2((byte*)"@VMOD") ) ;
 
 flag  =  string_replace( string_trim_space( flag ) , tos2((byte*)"@VMOD") , main__ModPath ) ;
 
 if ( array_string_contains( p ->table ->flags , flag ) ) {
 
 return ;
 
 }
 ;
 
 Parser_log(& /* ? */* p , _STR("adding flag \"%.*s\"", flag.len, flag.str) ) ;
 
 if ( ( has_vroot  ||  has_vmod )  &&  string_contains( flag , tos2((byte*)".o") ) ) {
 
 if ( p ->os == main__OS_msvc ) {
 
 build_thirdparty_obj_file_with_msvc ( flag ) ;
 
 }
  else { 
 
 build_thirdparty_obj_file ( flag ) ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& p ->table ->flags , ( flag ), tmp23, string) ;
 
 return ;
 
 }
 ;
 
 if ( string_starts_with( hash , tos2((byte*)"include") ) ) {
 
 if ( Parser_first_pass(& /* ? */* p )  &&  ! is_sig ) {
 
 if ( p ->file_pcguard .len != 0 ) {
 
_PUSH(& p ->cgen ->includes , ( _STR("%.*s\n#%.*s\n#endif", p ->file_pcguard.len, p ->file_pcguard.str, hash.len, hash.str) ), tmp24, string) ;
 
 return ;
 
 }
 ;
 
_PUSH(& p ->cgen ->includes , ( _STR("#%.*s", hash.len, hash.str) ), tmp25, string) ;
 
 return ;
 
 }
 ;
 
 }
  else  if ( string_contains( hash , tos2((byte*)"embed") ) ) {
 
int pos= string_index( hash , tos2((byte*)"embed") ) + 5 ;
 
string file= string_right( hash , pos ) ;
 
 if ( p ->pref ->build_mode != main__BuildMode_default_mode ) {
 
 Parser_genln( p , _STR("#include %.*s", file.len, file.str) ) ;
 
 }
 ;
 
 }
  else  if ( string_contains( hash , tos2((byte*)"define") ) ) {
 
_PUSH(& p ->cgen ->includes , ( _STR("#%.*s", hash.len, hash.str) ), tmp28, string) ;
 
 }
  else  if (string_eq( hash , tos2((byte*)"v") ) ) {
 
 println ( tos2((byte*)"v script") ) ;
 
 }
  else { 
 
 if ( ! p ->can_chash ) {
 
 Parser_error( p , tos2((byte*)"bad token `#` (embedding C code is no longer supported)") ) ;
 
 }
 ;
 
 Parser_genln( p , hash ) ;
 
 }
 ;
 
 
 }
 void Parser_comptime_method_call(Parser* p, Type typ) {
 
 p ->cgen ->cur_line  =  tos2((byte*)"") ;
 
 Parser_check( p , main__Token_dollar ) ;
 
string var= Parser_check_name( p ) ;
 
 array_Fn tmp30 =  typ .methods ;
 ;
for (int i = 0; i < tmp30 .len; i ++) {
 Fn method = ((Fn *) tmp30 . data)[i];
 
 
 if (string_ne( method .typ , tos2((byte*)"void") ) ) {
 
 continue
 ;
 
 }
 ;
 
Var receiver= ( *(Var*) array__get( method .args , 0) ) ;
 
string amp= ( receiver .is_mut ) ? ( tos2((byte*)"&") ) : ( tos2((byte*)"") ) ;
 
 if ( i > 0 ) {
 
 Parser_gen( p , tos2((byte*)" else ") ) ;
 
 }
 ;
 
 Parser_gen( p , _STR("if ( string_eq(%.*s, _STR(\"%.*s\")) ) %.*s_%.*s(%.*s %.*s);", var.len, var.str, method .name.len, method .name.str, typ .name.len, typ .name.str, method .name.len, method .name.str, amp.len, amp.str, p ->expr_var .name.len, p ->expr_var .name.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lpar ) ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 if ( p ->tok == main__Token_key_orelse ) {
 
 Parser_check( p , main__Token_key_orelse ) ;
 
 Parser_genln( p , tos2((byte*)"else {") ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_statements( p ) ;
 
 }
 ;
 
 
 }
 Var Fn_find_var(Fn* f, string name) {
 
 int tmp1 =  0;
 ;
for (int tmp2 = tmp1; tmp2 <  f ->var_idx; tmp2++) {
 int i = tmp2;
 
 
 if (string_eq( ( *(Var*) array__get( f ->local_vars , i) ) .name , name ) ) {
 
return  ( *(Var*) array__get( f ->local_vars , i) ) ;
 
 }
 ;
 
 }
 ;
 
return  (Var) { .typ = tos("", 0) , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
 
 }
 void Fn_open_scope(Fn* f) {
 
 f ->scope_level ++ ;
 
 
 }
 void Fn_mark_var_used(Fn* f, Var v) {
 
 array_Var tmp7 =  f ->local_vars ;
 ;
for (int i = 0; i < tmp7 .len; i ++) {
 Var vv = ((Var *) tmp7 . data)[i];
 
 
 if (string_eq( vv .name , v .name ) ) {
 
 ( *(Var*) array__get( f ->local_vars , i) ) .is_used  =  1 ;
 
 return ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void Fn_mark_var_changed(Fn* f, Var v) {
 
 array_Var tmp10 =  f ->local_vars ;
 ;
for (int i = 0; i < tmp10 .len; i ++) {
 Var vv = ((Var *) tmp10 . data)[i];
 
 
 if (string_eq( vv .name , v .name ) ) {
 
 ( *(Var*) array__get( f ->local_vars , i) ) .is_changed  =  1 ;
 
 }
 ;
 
 }
 ;
 
 
 }
 bool Fn_known_var(Fn* f, string name) {
 
Var v= Fn_find_var(& /* ? */* f , name ) ;
 
return  v .name .len > 0 ;
 
 
 }
 void Fn_register_var(Fn* f, Var v) {
 
Var new_var= (Var){ .scope_level =  f ->scope_level , .typ = v . typ, .name = v . name, .is_arg = v . is_arg, .is_const = v . is_const, .is_import_const = v . is_import_const, .args = v . args, .attr = v . attr, .is_mut = v . is_mut, .is_alloc = v . is_alloc, .ptr = v . ptr, .ref = v . ref, .parent_fn = v . parent_fn, .mod = v . mod, .line_nr = v . line_nr, .access_mod = v . access_mod, .is_global = v . is_global, .is_used = v . is_used, .is_changed = v . is_changed, } ;
 
 if ( f ->var_idx >= f ->local_vars .len ) {
 
_PUSH(& f ->local_vars , ( new_var ), tmp15, Var) ;
 
 }
  else { 
  
 Var tmp16 =  new_var; 

array_set(&/*q*/ f ->local_vars , f ->var_idx , & tmp16) ;
 
 }
 ;
 
 f ->var_idx ++ ;
 
 
 }
 void Fn_clear_vars(Fn* f) {
 
 f ->var_idx  =  0 ;
 
 f ->local_vars  = new_array_from_c_array(0, 0, sizeof(Var), (Var[]) {EMPTY_STRUCT_INIT   }) ;
 
 
 }
 bool Parser_is_sig(Parser* p) {
 
return  ( p ->pref ->build_mode == main__BuildMode_default_mode  ||  p ->pref ->build_mode == main__BuildMode_build )  &&  ( string_contains( p ->file_path , main__ModPath ) ) ;
 
 
 }
 Fn* new_fn(string mod, bool is_public) {
  
 Var tmp17 =  (Var) { .typ = tos("", 0) , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 }; 

return  ALLOC_INIT(Fn, { .mod =  mod , .local_vars =  array_repeat(&tmp17,  main__MaxLocalVars , sizeof(Var) ) , .is_public =  is_public , .name = tos("", 0) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ) ;
 
 
 }
 void Parser_fn_decl(Parser* p) {
 
 Parser_fgen( p , tos2((byte*)"fn ") ) ;
 
 
bool is_pub= p ->tok == main__Token_key_pub ;
 
bool is_live=string_eq( p ->attr , tos2((byte*)"live") )  &&  ! p ->pref ->is_so  &&  p ->pref ->is_live ;
 
 if (string_eq( p ->attr , tos2((byte*)"live") )  &&  Parser_first_pass(& /* ? */* p )  &&  ! p ->pref ->is_live  &&  ! p ->pref ->is_so ) {
 
 println ( tos2((byte*)"INFO: run `v -live program.v` if you want to use [live] functions") ) ;
 
 }
 ;
 
 if ( is_pub ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 p ->returns  =  0 ;
 
 Parser_next( p ) ;
 
Fn* f= new_fn ( p ->mod , is_pub ) ;
 
string receiver_typ= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_lpar ) {
 
 f ->is_method  =  1 ;
 
 Parser_check( p , main__Token_lpar ) ;
 
string receiver_name= Parser_check_name( p ) ;
 
bool is_mut= p ->tok == main__Token_key_mut ;
 
bool is_amp= p ->tok == main__Token_amp ;
 
 if ( is_mut  ||  is_amp ) {
 
 Parser_check_space( p , p ->tok ) ;
 
 }
 ;
 
 receiver_typ  =  Parser_get_type( p ) ;
 
Type* T= Table_find_type(& /* ? */* p ->table , receiver_typ ) ;
 
 if ( T ->is_interface ) {
 
 Parser_error( p , _STR("invalid receiver type `%.*s` (`%.*s` is an interface)", receiver_typ.len, receiver_typ.str, receiver_typ.len, receiver_typ.str) ) ;
 
 }
 ;
 
 if ( ! Parser_first_pass(& /* ? */* p )  &&  ! p ->builtin_mod  && string_ne( T ->mod , p ->mod ) ) {
 
printf( "T.mod=%.*s\n", T ->mod.len, T ->mod.str ) ;
 
printf( "p.mod=%.*s\n", p ->mod.len, p ->mod.str ) ;
 
 Parser_error( p , _STR("cannot define new methods on non-local type `%.*s`", receiver_typ.len, receiver_typ.str) ) ;
 
 }
 ;
 
 if ( ! p ->builtin_mod  &&  string_contains( receiver_typ , tos2((byte*)"*") ) ) {
 
string t= string_replace( receiver_typ , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 Parser_error( p , _STR("use `(%.*s mut %.*s)` instead of `(%.*s *%.*s)`", receiver_name.len, receiver_name.str, t.len, t.str, receiver_name.len, receiver_name.str, t.len, t.str) ) ;
 
 }
 ;
 
 f ->receiver_typ  =  receiver_typ ;
 
 if ( is_mut  ||  is_amp ) {
 
 receiver_typ = string_add(receiver_typ,  tos2((byte*)"*") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 Parser_fspace( p ) ;
 
Var receiver= (Var) { .name =  receiver_name , .is_arg =  1 , .typ =  receiver_typ , .is_mut =  is_mut , .ref =  is_amp , .ptr =  is_mut , .line_nr =  p ->scanner ->line_nr , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& f ->args , ( receiver ), tmp28, Var) ;
 
 Fn_register_var( f , receiver ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_plus  ||  p ->tok == main__Token_minus  ||  p ->tok == main__Token_mul ) {
 
 f ->name  =  Token_str( p ->tok ) ;
 
 Parser_next( p ) ;
 
 }
  else { 
 
 f ->name  =  Parser_check_name( p ) ;
 
 }
 ;
 
bool is_c=string_eq( f ->name , tos2((byte*)"C") )  &&  p ->tok == main__Token_dot ;
 
bool is_sig= Parser_is_sig( p ) ;
 
 if ( is_c ) {
 
 Parser_check( p , main__Token_dot ) ;
 
 f ->name  =  Parser_check_name( p ) ;
 
 f ->is_c  =  1 ;
 
 }
  else  if ( ! p ->pref ->translated  &&  ! string_contains( p ->file_path , tos2((byte*)"view.v") ) ) {
 
 if ( contains_capital ( f ->name ) ) {
 
 Parser_error( p , tos2((byte*)"function names cannot contain uppercase letters, use snake_case instead") ) ;
 
 }
 ;
 
 if ( string_contains( f ->name , tos2((byte*)"__") ) ) {
 
 Parser_error( p , tos2((byte*)"function names cannot contain double underscores, use single underscores instead") ) ;
 
 }
 ;
 
 }
 ;
 
bool has_receiver= receiver_typ .len > 0 ;
 
 if (string_ne( receiver_typ , tos2((byte*)"") ) ) {
 
 }
 ;
 
 if ( ! is_c  &&  ! p ->builtin_mod  && string_ne( p ->mod , tos2((byte*)"main") )  &&  receiver_typ .len == 0 ) {
 
 f ->name  =  Parser_prepend_mod(& /* ? */* p , f ->name ) ;
 
 }
 ;
 
 if ( Parser_first_pass(& /* ? */* p )  &&  Table_known_fn(& /* ? */* p ->table , f ->name )  &&  receiver_typ .len == 0 ) {
 
Fn existing_fn= Table_find_fn(& /* ? */* p ->table , f ->name ) ;
 
 if ( ! existing_fn .is_decl ) {
 
 Parser_error( p , _STR("redefinition of `%.*s`", f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 }
 ;
 
bool is_generic= 0 ;
 
 if ( p ->tok == main__Token_lt ) {
 
 is_generic  =  1 ;
 
 Parser_next( p ) ;
 
string gen_type= Parser_check_name( p ) ;
 
 if (string_ne( gen_type , tos2((byte*)"T") ) ) {
 
 Parser_error( p , tos2((byte*)"only `T` is allowed as a generic type for now") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_gt ) ;
 
 if ( Parser_first_pass(& /* ? */* p ) ) {
 
 Table_register_generic_fn( p ->table , f ->name ) ;
 
 }
  else { 
 
 }
 ;
 
 }
 ;
 
 Parser_fn_args( p , f ) ;
 
 if ( p ->tok == main__Token_not ) {
 
 Parser_next( p ) ;
 
 f ->returns_error  =  1 ;
 
 }
 ;
 
string typ= tos2((byte*)"void") ;
 
 if ( p ->tok == main__Token_name  ||  p ->tok == main__Token_mul  ||  p ->tok == main__Token_amp  ||  p ->tok == main__Token_lsbr  ||  p ->tok == main__Token_question ) {
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 typ  =  Parser_get_type( p ) ;
 
 }
 ;
 
bool is_fn_header= ! is_c  &&  ! is_sig  &&  ( p ->pref ->translated  ||  p ->pref ->is_test )  &&  p ->tok != main__Token_lcbr ;
 
 if ( is_fn_header ) {
 
 f ->is_decl  =  1 ;
 
 }
 ;
 
 if ( ! is_c  &&  ! is_sig  &&  ! is_fn_header ) {
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 }
 ;
 
 if ( string_starts_with( typ , tos2((byte*)"Option_") ) ) {
 
_PUSH(& p ->cgen ->typedefs , ( _STR("typedef Option %.*s;", typ.len, typ.str) ), tmp37, string) ;
 
 }
 ;
 
 f ->typ  =  typ ;
 
string str_args= Fn_str_args(& /* ? */* f , p ->table ) ;
 
 if (string_eq( f ->name , tos2((byte*)"main") )  &&  ! has_receiver ) {
 
 if (string_ne( str_args , tos2((byte*)"") )  || string_ne( typ , tos2((byte*)"void") ) ) {
 
 Parser_error( p , tos2((byte*)"fn main must have no arguments and no return values") ) ;
 
 }
 ;
 
 typ  =  tos2((byte*)"int") ;
 
 str_args  =  tos2((byte*)"int argc, char** argv") ;
 
 }
 ;
 
string dll_export_linkage= ( p ->os == main__OS_msvc  && string_eq( p ->attr , tos2((byte*)"live") )  &&  p ->pref ->is_so ) ? ( tos2((byte*)"__declspec(dllexport) ") ) : ( tos2((byte*)"") ) ;
 
 if ( ! p ->is_vweb ) {
 
 p ->cur_fn  =  f ;
 
 }
 ;
 
string fn_name_cgen= Table_cgen_name( p ->table , f ) ;
 
bool skip_main_in_test=string_eq( f ->name , tos2((byte*)"main") )  &&  p ->pref ->is_test ;
 
 if ( ! is_c  &&  ! is_live  &&  ! is_sig  &&  ! is_fn_header  &&  ! skip_main_in_test ) {
 
 if ( p ->pref ->obfuscate ) {
 
 Parser_genln( p , _STR("; // %.*s", f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 if ( is_generic ) {
 
array_string gen_types= Table_fn_gen_types( p ->table , f ->name ) ;
 
int cur_pos= p ->scanner ->pos ;
 
Token cur_tok= p ->tok ;
 
string cur_lit= p ->lit ;
 
 array_string tmp46 =  gen_types;
 ;
for (int tmp47 = 0; tmp47 < tmp46 .len; tmp47 ++) {
 string gen_type = ((string *) tmp46.data)[tmp47];
 
 
 Parser_genln( p , _STR("%.*s%.*s %.*s_%.*s(%.*s) {", dll_export_linkage.len, dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len, fn_name_cgen.str, gen_type.len, gen_type.str, str_args.len, str_args.str) ) ;
 
 Parser_genln( p , _STR("// T start %d %.*s", p ->pass, Parser_strtok(& /* ? */* p ).len, Parser_strtok(& /* ? */* p ).str) ) ;
 
 p ->cur_gen_type  =  gen_type ;
 
 Parser_statements( p ) ;
 
 p ->scanner ->pos  =  cur_pos ;
 
 p ->tok  =  cur_tok ;
 
 p ->lit  =  cur_lit ;
 
 }
 ;
 
 }
  else { 
 
 Parser_genln( p , _STR("%.*s%.*s %.*s(%.*s) {", dll_export_linkage.len, dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len, fn_name_cgen.str, str_args.len, str_args.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_fn_header ) {
 
 Parser_genln( p , _STR("%.*s %.*s(%.*s);", typ.len, typ.str, fn_name_cgen.len, fn_name_cgen.str, str_args.len, str_args.str) ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( is_c ) {
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 }
 ;
 
 if (string_ne( receiver_typ , tos2((byte*)"") ) ) {
 
Type* receiver_t= Table_find_type(& /* ? */* p ->table , receiver_typ ) ;
 
 if ( Parser_first_pass(& /* ? */* p )  && string_eq( receiver_t ->name , tos2((byte*)"") ) ) {
 
 Table_register_type2( p ->table , (Type) { .name =  string_replace( receiver_typ , tos2((byte*)"*") , tos2((byte*)"") ) , .mod =  p ->mod , .is_placeholder =  1 , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .parent = tos("", 0) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , } ) ;
 
 }
 ;
 
 Type_add_method( receiver_t ,* f ) ;
 
 }
  else { 
 
 Table_register_fn( p ->table ,* f ) ;
 
 }
 ;
 
 if ( is_sig  ||  Parser_first_pass(& /* ? */* p )  ||  is_live  ||  is_fn_header  ||  skip_main_in_test ) {
 
 if ( ! is_sig  &&  ! is_fn_header ) {
 
int opened_scopes= 0 ;
 
int closed_scopes= 0 ;
 
 while (1) { 
 
 if ( p ->tok == main__Token_lcbr ) {
 
 opened_scopes ++ ;
 
 }
 ;
 
 if ( p ->tok == main__Token_rcbr ) {
 
 closed_scopes ++ ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 if ( p ->tok == main__Token_gt  &&  p ->prev_tok == main__Token_name  &&  p ->prev_tok2 == main__Token_lt  &&  string_at( p ->scanner ->text , p ->scanner ->pos - 1) != 'T' ) {
 
 p ->scanner ->pos  -=  3 ;
 
 while ( p ->scanner ->pos > 0  &&  ( is_name_char ( string_at( p ->scanner ->text , p ->scanner ->pos) )  ||  string_at( p ->scanner ->text , p ->scanner ->pos) == '.'  ||  string_at( p ->scanner ->text , p ->scanner ->pos) == '<' ) ) {
 
 
 p ->scanner ->pos -- ;
 
 }
 ;
 
 p ->scanner ->pos -- ;
 
 Parser_next( p ) ;
 
 Parser_name_expr( p ) ;
 
 }
 ;
 
 if ( Token_is_decl( p ->tok )  &&  ! ( p ->prev_tok == main__Token_dot  &&  p ->tok == main__Token_key_type ) ) {
 
 break
 ;
 
 }
 ;
 
 if ( closed_scopes > opened_scopes  &&  p ->prev_tok == main__Token_rcbr ) {
 
 if ( p ->tok == main__Token_lsbr ) {
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if ( is_live  &&  Parser_first_pass(& /* ? */* p )  && string_eq( p ->mod , tos2((byte*)"main") ) ) {
 
_PUSH(& p ->cgen ->so_fns , ( fn_name_cgen ), tmp59, string) ;
 
 fn_name_cgen  =  _STR("(* %.*s )", fn_name_cgen.len, fn_name_cgen.str) ;
 
 }
 ;
 
string fn_decl= _STR("%.*s%.*s %.*s(%.*s)", dll_export_linkage.len, dll_export_linkage.str, typ.len, typ.str, fn_name_cgen.len, fn_name_cgen.str, str_args.len, str_args.str) ;
 
 if ( p ->pref ->obfuscate ) {
 
 fn_decl = string_add(fn_decl,  _STR("; // %.*s", f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 if ( ! is_c  && string_ne( f ->name , tos2((byte*)"main") )  &&  Parser_first_pass(& /* ? */* p ) ) {
 
 if (string_eq( f ->name , tos2((byte*)"darwin__nsstring") )  &&  p ->pref ->build_mode == main__BuildMode_default_mode ) {
 
 return ;
 
 }
 ;
 
_PUSH(& p ->cgen ->fns , (string_add( fn_decl , tos2((byte*)";") ) ), tmp61, string) ;
 
 }
 ;
 
 return ;
 
 }
 ;
 
 if (string_eq( p ->attr , tos2((byte*)"live") )  &&  p ->pref ->is_so ) {
 
 Parser_genln( p , tos2((byte*)"pthread_mutex_lock(&live_fn_mutex);") ) ;
 
 }
 ;
 
 if (string_eq( f ->name , tos2((byte*)"main") )  || string_eq( f ->name , tos2((byte*)"WinMain") ) ) {
 
 Parser_genln( p , tos2((byte*)"init_consts();") ) ;
 
 if ( array_string_contains( p ->table ->imports , tos2((byte*)"os") ) ) {
 
 if (string_eq( f ->name , tos2((byte*)"main") ) ) {
 
 Parser_genln( p , tos2((byte*)"os__args = os__init_os_args(argc, argv);") ) ;
 
 }
  else  if (string_eq( f ->name , tos2((byte*)"WinMain") ) ) {
 
 Parser_genln( p , tos2((byte*)"os__args = os__parse_windows_cmd_line(pCmdLine);") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->pref ->is_live ) {
 
string file_base= string_replace( p ->file_path , tos2((byte*)".v") , tos2((byte*)"") ) ;
 
 if ( p ->os != main__OS_windows  &&  p ->os != main__OS_msvc ) {
 
string so_name=string_add( file_base , tos2((byte*)".so") ) ;
 
 Parser_genln( p , _STR(" \nload_so(\"%.*s\"); \npthread_t _thread_so;\npthread_create(&_thread_so , NULL, &reload_so, NULL); ", so_name.len, so_name.str) ) ;
 
 }
  else { 
 
string so_name=string_add( file_base , ( p ->os == main__OS_msvc ) ? ( tos2((byte*)".dll") ) : ( tos2((byte*)".so") ) ) ;
 
 Parser_genln( p , _STR("\nlive_fn_mutex = CreateMutexA(0, 0, 0);\nload_so(\"%.*s\");\nunsigned long _thread_so;\n_thread_so = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&reload_so, 0, 0, 0);\n				", so_name.len, so_name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->pref ->is_test  &&  ! string_contains( p ->scanner ->file_path , tos2((byte*)"/volt") ) ) {
 
 Parser_error( p , tos2((byte*)"tests cannot have function `main`") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_c  ||  is_sig  ||  is_fn_header ) {
 
 return ;
 
 }
 ;
 
 if ( p ->pref ->is_prof  && string_ne( f ->name , tos2((byte*)"main") )  && string_ne( f ->name , tos2((byte*)"time__ticks") ) ) {
 
 Parser_genln( p , _STR("double _PROF_START = time__ticks();//%.*s", f ->name.len, f ->name.str) ) ;
 
string cgen_name= Table_cgen_name( p ->table , f ) ;
 
 f ->defer_text  =  _STR("  %.*s_time += time__ticks() - _PROF_START;", cgen_name.len, cgen_name.str) ;
 
 }
 ;
 
 if ( is_generic ) {
 
 p ->cgen ->nogen  =  1 ;
 
 }
 ;
 
 Parser_statements_no_rcbr( p ) ;
 
 p ->cgen ->nogen  =  0 ;
 
 if ( p ->pref ->is_prof  && string_eq( f ->name , tos2((byte*)"main") ) ) {
 
 Parser_genln( p , Parser_print_prof_counters( p ) ) ;
 
 }
 ;
 
 Parser_genln( p , f ->defer_text ) ;
 
 if (string_ne( typ , tos2((byte*)"void") )  &&  ! p ->returns  && string_ne( f ->name , tos2((byte*)"main") )  && string_ne( f ->name , tos2((byte*)"WinMain") ) ) {
 
 Parser_error( p , _STR("%.*s must return \"%.*s\"", f ->name.len, f ->name.str, typ.len, typ.str) ) ;
 
 }
 ;
 
 if (string_eq( p ->attr , tos2((byte*)"live") )  &&  p ->pref ->is_so ) {
 
 Parser_genln( p , tos2((byte*)"pthread_mutex_unlock(&live_fn_mutex);") ) ;
 
 }
 ;
 
 if (string_eq( p ->mod , tos2((byte*)"main") ) ) {
 
 }
 ;
 
 if ( p ->cur_fn ->scope_level > 2 ) {
 
 }
 ;
 
 if (string_ne( p ->mod , tos2((byte*)"main") ) ) {
 
 if ( ! is_generic ) {
 
 Parser_genln( p , tos2((byte*)"}") ) ;
 
 }
 ;
 
 return ;
 
 }
 ;
 
 Parser_check_unused_variables( p ) ;
 
 p ->cur_fn  =  main__EmptyFn ;
 
 if ( ! is_generic ) {
 
 Parser_genln( p , tos2((byte*)"}") ) ;
 
 }
 ;
 
  {
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 }
 }
 void Parser_check_unused_variables(Parser* p) {
 
 array_Var tmp66 =  p ->cur_fn ->local_vars;
 ;
for (int tmp67 = 0; tmp67 < tmp66 .len; tmp67 ++) {
 Var var = ((Var *) tmp66.data)[tmp67];
 
 
 if (string_eq( var .name , tos2((byte*)"") ) ) {
 
 break
 ;
 
 }
 ;
 
 if ( ! var .is_used  &&  ! p ->pref ->is_repl  &&  ! var .is_arg  &&  ! p ->pref ->translated  && string_ne( var .name , tos2((byte*)"_") ) ) {
 
 p ->scanner ->line_nr  =  var .line_nr - 1 ;
 
 Parser_error( p , _STR("`%.*s` declared and not used", var .name.len, var .name.str) ) ;
 
 }
 ;
 
 if ( ! var .is_changed  &&  var .is_mut  &&  ! p ->pref ->is_repl  &&  ! var .is_arg  &&  ! p ->pref ->translated  && string_ne( var .name , tos2((byte*)"_") ) ) {
 
 p ->scanner ->line_nr  =  var .line_nr - 1 ;
 
 Parser_error( p , _STR("`%.*s` is declared as mutable, but it was never changed", var .name.len, var .name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void Parser_async_fn_call(Parser* p, Fn f, int method_ph, string receiver_var, string receiver_type) {
 
string thread_name= tos2((byte*)"") ;
 
string fn_name= f .name ;
 
 if ( f .is_method ) {
 
 receiver_type  =  string_replace( receiver_type , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 fn_name  =  _STR("%.*s_%.*s", receiver_type.len, receiver_type.str, f .name.len, f .name.str) ;
 
 }
 ;
 
string arg_struct_name= _STR("thread_arg_%.*s", fn_name.len, fn_name.str) ;
 
string tmp_struct= Parser_get_tmp( p ) ;
 
 Parser_genln( p , _STR("%.*s * %.*s = malloc(sizeof(%.*s));", arg_struct_name.len, arg_struct_name.str, tmp_struct.len, tmp_struct.str, arg_struct_name.len, arg_struct_name.str) ) ;
 
string arg_struct= _STR("typedef struct  %.*s   { ", arg_struct_name.len, arg_struct_name.str) ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lpar ) ;
 
string str_args= tos2((byte*)"") ;
 
bool did_gen_something= 0 ;
 
 array_Var tmp75 =  f .args ;
 ;
for (int i = 0; i < tmp75 .len; i ++) {
 Var arg = ((Var *) tmp75 . data)[i];
 
 
 arg_struct = string_add(arg_struct,  _STR("%.*s %.*s ;", arg .typ.len, arg .typ.str, arg .name.len, arg .name.str) ) ;
 
 str_args = string_add(str_args,  _STR("arg->%.*s", arg .name.len, arg .name.str) ) ;
 
 if ( i == 0  &&  f .is_method ) {
 
 Parser_genln( p , _STR("%.*s -> %.*s =  %.*s ;", tmp_struct.len, tmp_struct.str, arg .name.len, arg .name.str, receiver_var.len, receiver_var.str) ) ;
 
 if ( i < f .args .len - 1 ) {
 
 str_args = string_add(str_args,  tos2((byte*)",") ) ;
 
 }
 ;
 
 continue
 ;
 
 }
 ;
 
 Parser_genln( p , _STR("%.*s -> %.*s =  ", tmp_struct.len, tmp_struct.str, arg .name.len, arg .name.str) ) ;
 
 Parser_expression( p ) ;
 
 Parser_genln( p , tos2((byte*)";") ) ;
 
 if ( i < f .args .len - 1 ) {
 
 Parser_check( p , main__Token_comma ) ;
 
 str_args = string_add(str_args,  tos2((byte*)",") ) ;
 
 }
 ;
 
 did_gen_something  =  1 ;
 
 }
 ;
 
 if ( ! did_gen_something ) {
 
 arg_struct = string_add(arg_struct,  tos2((byte*)"EMPTY_STRUCT_DECLARATION") ) ;
 
 }
 ;
 
 arg_struct = string_add(arg_struct,  _STR("} %.*s ;", arg_struct_name.len, arg_struct_name.str) ) ;
 
 fn_name  =  Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ) ;
 
string wrapper_name= _STR("%.*s_thread_wrapper", fn_name.len, fn_name.str) ;
 
string wrapper_text= _STR("void* %.*s(%.*s * arg) {%.*s( /*f*/%.*s );  }", wrapper_name.len, wrapper_name.str, arg_struct_name.len, arg_struct_name.str, fn_name.len, fn_name.str, str_args.len, str_args.str) ;
 
 CGen_register_thread_fn( p ->cgen , wrapper_name , wrapper_text , arg_struct ) ;
 
int tmp_nr= Parser_get_tmp_counter( p ) ;
 
 thread_name  =  _STR("_thread%d", tmp_nr) ;
 
 if ( p ->os != main__OS_windows  &&  p ->os != main__OS_msvc ) {
 
 Parser_genln( p , _STR("pthread_t %.*s;", thread_name.len, thread_name.str) ) ;
 
 }
 ;
 
string tmp2= Parser_get_tmp( p ) ;
 
string parg= tos2((byte*)"NULL") ;
 
 if ( f .args .len > 0 ) {
 
 parg  =  _STR(" %.*s", tmp_struct.len, tmp_struct.str) ;
 
 }
 ;
 
 if ( p ->os == main__OS_windows  ||  p ->os == main__OS_msvc ) {
 
 Parser_genln( p , _STR(" CreateThread(0,0, %.*s, %.*s, 0,0);", wrapper_name.len, wrapper_name.str, parg.len, parg.str) ) ;
 
 }
  else { 
 
 Parser_genln( p , _STR("int %.*s = pthread_create(& %.*s, NULL, %.*s, %.*s);", tmp2.len, tmp2.str, thread_name.len, thread_name.str, wrapper_name.len, wrapper_name.str, parg.len, parg.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 
 }
 void Parser_fn_call(Parser* p, Fn f, int method_ph, string receiver_var, string receiver_type) {
 
 if ( ! f .is_public  &&  ! f .is_c  &&  ! p ->pref ->is_test  &&  ! f .is_interface  && string_ne( f .mod , p ->mod ) ) {
 
 Parser_error( p , _STR("function `%.*s` is private", f .name.len, f .name.str) ) ;
 
 }
 ;
 
 p ->calling_c  =  f .is_c ;
 
 if ( f .is_c  &&  ! p ->builtin_mod ) {
 
 if (string_eq( f .name , tos2((byte*)"free") ) ) {
 
 Parser_error( p , tos2((byte*)"use `free()` instead of `C.free()`") ) ;
 
 }
  else  if (string_eq( f .name , tos2((byte*)"malloc") ) ) {
 
 Parser_error( p , tos2((byte*)"use `malloc()` instead of `C.malloc()`") ) ;
 
 }
 ;
 
 }
 ;
 
string cgen_name= Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ) ;
 
 Parser_next( p ) ;
 
string gen_type= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_lt ) {
 
 Parser_check( p , main__Token_lt ) ;
 
 gen_type  =  Parser_check_name( p ) ;
 
 if ( Parser_first_pass(& /* ? */* p ) ) {
 
 Table_register_generic_fn_type( p ->table , f .name , gen_type ) ;
 
 return ;
 
 }
 ;
 
 cgen_name = string_add(cgen_name, string_add( tos2((byte*)"_") , gen_type ) ) ;
 
 Parser_check( p , main__Token_gt ) ;
 
 }
 ;
 
 if ( ! f .is_method ) {
 
 Parser_gen( p , cgen_name ) ;
 
 Parser_gen( p , tos2((byte*)"(") ) ;
 
 }
  else { 
 
string method_call= _STR("%.*s(", cgen_name.len, cgen_name.str) ;
 
Var receiver=*(Var*)  array_first( f .args ) ;
 
 if ( receiver .is_mut  &&  ! p ->expr_var .is_mut ) {
 
printf( "%.*s  recv=%.*s recv_mut=%d\n", method_call.len, method_call.str, receiver .name.len, receiver .name.str, receiver .is_mut ) ;
 
 Parser_error( p , _STR("`%.*s` is immutable", p ->expr_var .name.len, p ->expr_var .name.str) ) ;
 
 }
 ;
 
 if ( ! p ->expr_var .is_changed ) {
 
 Fn_mark_var_changed(& /* ? */* p ->cur_fn , p ->expr_var ) ;
 
 }
 ;
 
 if ( receiver .ref  ||  ( receiver .is_mut  &&  ! string_contains( receiver_type , tos2((byte*)"*") ) ) ) {
 
 method_call = string_add(method_call,  tos2((byte*)"& /* ? */") ) ;
 
 }
 ;
 
 if ( ! receiver .is_mut  &&  string_contains( receiver_type , tos2((byte*)"*") ) ) {
 
 method_call = string_add(method_call,  tos2((byte*)"*") ) ;
 
 }
 ;
 
string cast= tos2((byte*)"") ;
 
 if (string_eq( f .typ , tos2((byte*)"void*") ) ) {
 
 cast  =  string_all_after( receiver_type , tos2((byte*)"_") ) ;
 
 cast  =  _STR("*(%.*s*) ", cast.len, cast.str) ;
 
 }
 ;
 
 CGen_set_placeholder( p ->cgen , method_ph , _STR("%.*s %.*s", cast.len, cast.str, method_call.len, method_call.str) ) ;
 
 }
 ;
 
 Parser_fn_call_args( p ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 p ->calling_c  =  0 ;
 
 
 }
 void Parser_fn_args(Parser* p, Fn* f) {
 
 Parser_check( p , main__Token_lpar ) ;
 
 
 if ( f ->is_interface ) {
 
Var int_arg= (Var) { .typ =  f ->receiver_typ , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& f ->args , ( int_arg ), tmp87, Var) ;
 
 }
 ;
 
bool types_only= p ->tok == main__Token_mul  ||  ( Parser_peek( p ) == main__Token_comma  &&  Table_known_type(& /* ? */* p ->table , p ->lit ) )  ||  Parser_peek( p ) == main__Token_rpar ;
 
 if ( types_only ) {
 
 while ( p ->tok != main__Token_rpar ) {
 
 
string typ= Parser_get_type( p ) ;
 
Var v= (Var) { .typ =  typ , .is_arg =  1 , .line_nr =  p ->scanner ->line_nr , .name = tos("", 0) , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& f ->args , ( v ), tmp91, Var) ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 while ( p ->tok != main__Token_rpar ) {
 
 
array_string names=new_array_from_c_array(1, 1, sizeof(string), (string[]) {  Parser_check_name( p )  }) ;
 
 while ( p ->tok == main__Token_comma ) {
 
 
 Parser_check( p , main__Token_comma ) ;
 
 Parser_fspace( p ) ;
 
_PUSH(& names , ( Parser_check_name( p ) ), tmp93, string) ;
 
 }
 ;
 
 Parser_fspace( p ) ;
 
bool is_mut= p ->tok == main__Token_key_mut ;
 
 if ( is_mut ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
string typ= Parser_get_type( p ) ;
 
 if ( is_mut  &&  is_primitive_type ( typ ) ) {
 
 Parser_error( p ,string_add( tos2((byte*)"mutable arguments are only allowed for arrays, maps, and structs.") , tos2((byte*)"\nreturn values instead: `foo(n mut int)` => `foo(n int) int`") ) ) ;
 
 }
 ;
 
 array_string tmp96 =  names;
 ;
for (int tmp97 = 0; tmp97 < tmp96 .len; tmp97 ++) {
 string name = ((string *) tmp96.data)[tmp97];
 
 
 if ( ! Parser_first_pass(& /* ? */* p )  &&  ! Table_known_type(& /* ? */* p ->table , typ ) ) {
 
 Parser_error( p , _STR("fn_args: unknown type %.*s", typ.len, typ.str) ) ;
 
 }
 ;
 
 if ( is_mut ) {
 
 typ = string_add(typ,  tos2((byte*)"*") ) ;
 
 }
 ;
 
Var v= (Var) { .name =  name , .typ =  typ , .is_arg =  1 , .is_mut =  is_mut , .ptr =  is_mut , .line_nr =  p ->scanner ->line_nr , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
 Fn_register_var( f , v ) ;
 
_PUSH(& f ->args , ( v ), tmp99, Var) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_dotdot ) {
 
_PUSH(& f ->args , ( (Var) { .name =  tos2((byte*)"..") , .typ = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ), tmp100, Var) ;
 
 Parser_next( p ) ;
 
 }
 ;
 
 }
 ;
 
  {
 
 Parser_check( p , main__Token_rpar ) ;
 
 }
 }
 Fn* Parser_fn_call_args(Parser* p, Fn* f) {
 
 Parser_check( p , main__Token_lpar ) ;
 
 if ( f ->is_c ) {
 
 while ( p ->tok != main__Token_rpar ) {
 
 
 Parser_bool_expression( p ) ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_gen( p , tos2((byte*)", ") ) ;
 
 Parser_check( p , main__Token_comma ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
return  f ;
 
 }
 ;
 
 if ( p ->v ->pref ->is_debug  && string_eq( f ->name , tos2((byte*)"panic") ) ) {
 
string mod_name= string_replace( p ->mod , tos2((byte*)"_dot_") , tos2((byte*)".") ) ;
 
string fn_name= string_replace( p ->cur_fn ->name , _STR("%.*s__", p ->mod.len, p ->mod.str) , tos2((byte*)"") ) ;
 
string file_path= string_replace( p ->file_path , tos2((byte*)"\\") , tos2((byte*)"\\\\") ) ;
 
 CGen_resetln( p ->cgen , string_replace( p ->cgen ->cur_line , tos2((byte*)"v_panic (") , _STR("_panic_debug (%d, tos2(\"%.*s\"), tos2(\"%.*s\"), tos2(\"%.*s\"), ", p ->scanner ->line_nr, file_path.len, file_path.str, mod_name.len, mod_name.str, fn_name.len, fn_name.str) ) ) ;
 
 }
 ;
 
 array_Var tmp104 =  f ->args ;
 ;
for (int i = 0; i < tmp104 .len; i ++) {
 Var arg = ((Var *) tmp104 . data)[i];
 
 
 if ( i == 0  &&  f ->is_method ) {
 
 if ( f ->args .len > 1 ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 continue
 ;
 
 }
 ;
 
 if ( i == f ->args .len - 1  && string_eq( arg .name , tos2((byte*)"..") ) ) {
 
 break
 ;
 
 }
 ;
 
int ph= CGen_add_placeholder( p ->cgen ) ;
 
 if ( p ->tok == main__Token_rpar ) {
 
string str_args= Fn_str_args(& /* ? */* f , p ->table ) ;
 
 Parser_error( p , _STR("not enough arguments in call to `%.*s (%.*s)`", f ->name.len, f ->name.str, str_args.len, str_args.str) ) ;
 
 }
 ;
 
 if ( arg .is_mut ) {
 
 if ( p ->tok != main__Token_key_mut ) {
 
 Parser_error( p , _STR("`%.*s` is a key_mut argument, you need to provide `mut`: `%.*s(...mut a...)`", arg .name.len, arg .name.str, f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 if ( Parser_peek( p ) != main__Token_name ) {
 
 Parser_error( p , _STR("`%.*s` is a key_mut argument, you need to provide a variable to modify: `%.*s(... mut a...)`", arg .name.len, arg .name.str, f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_key_mut ) ;
 
string var_name= p ->lit ;
 
Var v= Fn_find_var(& /* ? */* p ->cur_fn , var_name ) ;
 
 if (string_eq( v .name , tos2((byte*)"") ) ) {
 
 Parser_error( p , _STR("`%.*s` is a key_mut argument, you need to provide a variable to modify: `%.*s(... mut a...)`", arg .name.len, arg .name.str, f ->name.len, f ->name.str) ) ;
 
 }
 ;
 
 if ( ! v .is_changed ) {
 
 Fn_mark_var_changed(& /* ? */* p ->cur_fn , v ) ;
 
 }
 ;
 
 }
 ;
 
 p ->expected_type  =  arg .typ ;
 
string typ= Parser_bool_expression( p ) ;
 
 if ( i == 0  && string_eq( f ->name , tos2((byte*)"println") )  && string_ne( typ , tos2((byte*)"string") )  && string_ne( typ , tos2((byte*)"void") ) ) {
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 #ifndef _WIN32
 
string fmt= Parser_typ_to_fmt( p , typ , 0 ) ;
 
 if (string_ne( fmt , tos2((byte*)"") ) ) {
 
 CGen_resetln( p ->cgen , string_replace( p ->cgen ->cur_line , tos2((byte*)"println (") ,string_add(string_add( tos2((byte*)"/*opt*/printf (\"") , fmt ) , tos2((byte*)"\\n\", ") ) ) ) ;
 
 continue
 ;
 
 }
 ;
 
 #endif
 ;
 
 if ( string_ends_with( typ , tos2((byte*)"*") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"ptr_str(") ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 continue
 ;
 
 }
 ;
 
 if ( ! Type_has_method(& /* ? */* T , tos2((byte*)"str") ) ) {
 
string error_msg= ( _STR("`%.*s` needs to have method `str() string` to be printable", typ.len, typ.str) ) ;
 
 if ( T ->fields .len > 0 ) {
 
int index= p ->cgen ->cur_line .len - 1 ;
 
 while ( index > 0  &&  string_at( p ->cgen ->cur_line , index) != ' ' ) {
 
 
 index -- ;
 
 }
 ;
 
string name= string_right( p ->cgen ->cur_line , index + 1 ) ;
 
 if (string_eq( name , tos2((byte*)"}") ) ) {
 
 Parser_error( p , error_msg ) ;
 
 }
 ;
 
 CGen_resetln( p ->cgen , string_left( p ->cgen ->cur_line , index ) ) ;
 
 Scanner_create_type_string( p ->scanner ,* T , name ) ;
 
 string_replace( p ->cgen ->cur_line , typ , tos2((byte*)"") ) ;
 
 Parser_next( p ) ;
 
return  Parser_fn_call_args( p , f ) ;
 
 }
 ;
 
 Parser_error( p , error_msg ) ;
 
 }
 ;
 
 CGen_set_placeholder( p ->cgen , ph , _STR("%.*s_str(", typ.len, typ.str) ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 continue
 ;
 
 }
 ;
 
string got= typ ;
 
string expected= arg .typ ;
 
 if ( ! Parser_check_types_no_throw( p , got , expected ) ) {
 
string err= _STR("Fn \"%.*s\" wrong arg #%d. ", f ->name.len, f ->name.str, i + 1) ;
 
 err = string_add(err,  _STR("Expected \"%.*s\" (%.*s)  but got \"%.*s\"", arg .typ.len, arg .typ.str, arg .name.len, arg .name.str, typ.len, typ.str) ) ;
 
 Parser_error( p , err ) ;
 
 }
 ;
 
bool is_interface= Table_is_interface(& /* ? */* p ->table , arg .typ ) ;
 
 if ( ! is_interface ) {
 
 if ( string_contains( got , tos2((byte*)"*") )  &&  ! string_contains( expected , tos2((byte*)"*") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"*") ) ;
 
 }
 ;
 
 if ( ! string_contains( got , tos2((byte*)"*") )  &&  string_contains( expected , tos2((byte*)"*") )  && string_ne( got , tos2((byte*)"voidptr") ) ) {
 
 if ( ! (string_eq( expected , tos2((byte*)"void*") )  && string_eq( got , tos2((byte*)"int") ) )  &&  ! (string_eq( expected , tos2((byte*)"byte*") )  &&  string_contains( got , tos2((byte*)"]byte") ) )  &&  ! (string_eq( expected , tos2((byte*)"byte*") )  && string_eq( got , tos2((byte*)"string") ) ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , _STR("& /*11 EXP:\"%.*s\" GOT:\"%.*s\" */", expected.len, expected.str, got.len, got.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if ( is_interface ) {
 
 if ( ! string_contains( got , tos2((byte*)"*") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"&") ) ;
 
 }
 ;
 
Type* interface_type= Table_find_type(& /* ? */* p ->table , arg .typ ) ;
 
 array_Fn tmp122 =  interface_type ->methods;
 ;
for (int tmp123 = 0; tmp123 < tmp122 .len; tmp123 ++) {
 Fn method = ((Fn *) tmp122.data)[tmp123];
 
 
 Parser_gen( p , _STR(", %.*s_%.*s ", typ.len, typ.str, method .name.len, method .name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( i < f ->args .len - 1 ) {
 
bool is_vararg= i == f ->args .len - 2  && string_eq( ( *(Var*) array__get( f ->args , i + 1) ) .name , tos2((byte*)"..") ) ;
 
 if ( p ->tok != main__Token_comma  &&  ! is_vararg ) {
 
 Parser_error( p , _STR("wrong number of arguments for %d,%.*s fn `%.*s`: expected %d, but got less", i, arg .name.len, arg .name.str, f ->name.len, f ->name.str, f ->args .len) ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_fgen( p , tos2((byte*)", ") ) ;
 
 }
 ;
 
 if ( ! is_vararg ) {
 
 Parser_next( p ) ;
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if ( f ->args .len > 0 ) {
 
Var last_arg=*(Var*)  array_last( f ->args ) ;
 
 if (string_eq( last_arg .name , tos2((byte*)"..") ) ) {
 
 while ( p ->tok != main__Token_rpar ) {
 
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 Parser_check( p , main__Token_comma ) ;
 
 }
 ;
 
 Parser_bool_expression( p ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_error( p , _STR("wrong number of arguments for fn `%.*s`: expected %d, but got more", f ->name.len, f ->name.str, f ->args .len) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 
 }
 string Fn_typ_str(Fn f) {
 
strings__Builder sb= strings__new_builder ( 50 ) ;
 
 strings__Builder_write(& /* ? */ sb , tos2((byte*)"fn (") ) ;
 
 array_Var tmp129 =  f .args ;
 ;
for (int i = 0; i < tmp129 .len; i ++) {
 Var arg = ((Var *) tmp129 . data)[i];
 
 
 strings__Builder_write(& /* ? */ sb , arg .typ ) ;
 
 if ( i < f .args .len - 1 ) {
 
 strings__Builder_write(& /* ? */ sb , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 strings__Builder_write(& /* ? */ sb , tos2((byte*)")") ) ;
 
 if (string_ne( f .typ , tos2((byte*)"void") ) ) {
 
 strings__Builder_write(& /* ? */ sb , _STR(" %.*s", f .typ.len, f .typ.str) ) ;
 
 }
 ;
 
return  strings__Builder_str( sb ) ;
 
 
 }
 string Fn_str_args(Fn* f, Table* table) {
 
string s= tos2((byte*)"") ;
 
 array_Var tmp131 =  f ->args ;
 ;
for (int i = 0; i < tmp131 .len; i ++) {
 Var arg = ((Var *) tmp131 . data)[i];
 
 
 if ( Table_is_interface(& /* ? */* table , arg .typ ) ) {
 
 s = string_add(s,  _STR(" void* %.*s", arg .name.len, arg .name.str) ) ;
 
Type* interface_type= Table_find_type(& /* ? */* table , arg .typ ) ;
 
 array_Fn tmp133 =  interface_type ->methods;
 ;
for (int tmp134 = 0; tmp134 < tmp133 .len; tmp134 ++) {
 Fn method = ((Fn *) tmp133.data)[tmp134];
 
 
 s = string_add(s,  _STR(", %.*s (*%.*s_%.*s)(void*", method .typ.len, method .typ.str, arg .typ.len, arg .typ.str, method .name.len, method .name.str) ) ;
 
 if ( method .args .len > 1 ) {
 
 array_Var tmp135 =  array_right( method .args , 1 );
 ;
for (int tmp136 = 0; tmp136 < tmp135 .len; tmp136 ++) {
 Var a = ((Var *) tmp135.data)[tmp136];
 
 
 s = string_add(s,  _STR(", %.*s", a .typ.len, a .typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 s = string_add(s,  tos2((byte*)")") ) ;
 
 }
 ;
 
 }
  else  if (string_eq( arg .name , tos2((byte*)"..") ) ) {
 
 s = string_add(s,  tos2((byte*)"...") ) ;
 
 }
  else { 
 
 s = string_add(s,  Table_cgen_name_type_pair(& /* ? */* table , arg .name , arg .typ ) ) ;
 
 }
 ;
 
 if ( i < f ->args .len - 1 ) {
 
 s = string_add(s,  tos2((byte*)", ") ) ;
 
 }
 ;
 
 }
 ;
 
return  s ;
 
 
 }
 void Parser_gen_json_for_type(Parser* p, Type typ) {
 
string dec= tos2((byte*)"") ;
 
string enc= tos2((byte*)"") ;
 
string t= typ .name ;
 
 if (string_eq( t , tos2((byte*)"int") )  || string_eq( t , tos2((byte*)"string") )  || string_eq( t , tos2((byte*)"bool") ) ) {
 
 return ;
 
 }
 ;
 
 if ( Parser_first_pass(& /* ? */* p ) ) {
 
 return ;
 
 }
 ;
 
Fn dec_fn= (Fn) { .mod =  p ->mod , .typ =  _STR("Option_%.*s", typ .name.len, typ .name.str) , .name =  js_dec_name ( t ) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
 if ( Table_known_fn(& /* ? */* p ->table , dec_fn .name ) ) {
 
 return ;
 
 }
 ;
 
Var arg= (Var) { .typ =  tos2((byte*)"cJSON*") , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& dec_fn .args , ( arg ), tmp6, Var) ;
 
 Table_register_fn( p ->table , dec_fn ) ;
 
Fn enc_fn= (Fn) { .mod =  p ->mod , .typ =  tos2((byte*)"cJSON*") , .name =  js_enc_name ( t ) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
Var enc_arg= (Var) { .typ =  t , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& enc_fn .args , ( enc_arg ), tmp9, Var) ;
 
 Table_register_fn( p ->table , enc_fn ) ;
 
 dec = string_add(dec,  _STR("\n//%.*s %.*s(cJSON* root) {  \nOption %.*s(cJSON* root, %.*s* res) {  \n//  %.*s res; \n  if (!root) {\n    const char *error_ptr = cJSON_GetErrorPtr();\n    if (error_ptr != NULL)	{\n      fprintf(stderr, \"Error in decode() for %.*s error_ptr=: %%%%s\\n\", error_ptr);\n//      printf(\"\\nbad js=%%%%s\\n\", js.str); \n      return v_error(tos2(error_ptr));\n    }\n  }\n", t.len, t.str, dec_fn .name.len, dec_fn .name.str, dec_fn .name.len, dec_fn .name.str, t.len, t.str, t.len, t.str, t.len, t.str) ) ;
 
 enc = string_add(enc,  _STR("\ncJSON* %.*s(%.*s val) {  \ncJSON *o = cJSON_CreateObject();\nstring res = tos2(\"\"); \n", enc_fn .name.len, enc_fn .name.str, t.len, t.str) ) ;
 
 if ( string_starts_with( t , tos2((byte*)"array_") ) ) {
 
 dec = string_add(dec,  Parser_decode_array( p , t ) ) ;
 
 enc = string_add(enc,  Parser_encode_array(& /* ? */* p , t ) ) ;
 
 }
 ;
 
 array_Var tmp10 =  typ .fields;
 ;
for (int tmp11 = 0; tmp11 < tmp10 .len; tmp11 ++) {
 Var field = ((Var *) tmp10.data)[tmp11];
 
 
 if (string_eq( field .attr , tos2((byte*)"skip") ) ) {
 
 continue
 ;
 
 }
 ;
 
Type* field_type= Table_find_type(& /* ? */* p ->table , field .typ ) ;
 
 Parser_gen_json_for_type( p ,* field_type ) ;
 
string name= field .name ;
 
string _typ= string_replace( field .typ , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
string enc_name= js_enc_name ( _typ ) ;
 
string dec_name= js_dec_name ( _typ ) ;
 
 if ( is_js_prim ( _typ ) ) {
 
 dec = string_add(dec,  _STR(" /*prim*/ res->%.*s = %.*s(js_get(root, \"%.*s\"))", name.len, name.str, dec_name.len, dec_name.str, field .name.len, field .name.str) ) ;
 
 }
  else { 
 
 dec = string_add(dec,  _STR(" /*!!*/ %.*s(js_get(root, \"%.*s\"), & (res->%.*s))", dec_name.len, dec_name.str, field .name.len, field .name.str, name.len, name.str) ) ;
 
 }
 ;
 
 dec = string_add(dec,  tos2((byte*)";\n") ) ;
 
 enc = string_add(enc,  _STR("  cJSON_AddItemToObject(o,  \"%.*s\", %.*s(val.%.*s)); \n", name.len, name.str, enc_name.len, enc_name.str, name.len, name.str) ) ;
 
 }
 ;
 
_PUSH(& p ->cgen ->fns , ( _STR("%.*s return opt_ok(res, sizeof(*res)); \n}", dec.len, dec.str) ), tmp17, string) ;
 
_PUSH(& p ->cgen ->fns , ( _STR("/*enc start*/ %.*s return o;}", enc.len, enc.str) ), tmp18, string) ;
 
 
 }
 bool is_js_prim(string typ) {
 
return string_eq( typ , tos2((byte*)"int") )  || string_eq( typ , tos2((byte*)"string") )  || string_eq( typ , tos2((byte*)"bool") )  || string_eq( typ , tos2((byte*)"f32") )  || string_eq( typ , tos2((byte*)"f64") )  || string_eq( typ , tos2((byte*)"i8") )  || string_eq( typ , tos2((byte*)"i16") )  || string_eq( typ , tos2((byte*)"i32") )  || string_eq( typ , tos2((byte*)"i64") ) ;
 
 
 }
 string Parser_decode_array(Parser* p, string typ) {
 
 typ  =  string_replace( typ , tos2((byte*)"array_") , tos2((byte*)"") ) ;
 
Type* t= Table_find_type(& /* ? */* p ->table , typ ) ;
 
string fn_name= js_dec_name ( typ ) ;
 
 Parser_gen_json_for_type( p ,* t ) ;
 
string s= tos2((byte*)"") ;
 
 if ( is_js_prim ( typ ) ) {
 
 s  =  _STR("%.*s val= %.*s(jsval); ", typ.len, typ.str, fn_name.len, fn_name.str) ;
 
 }
  else { 
 
 s  =  _STR("  %.*s val; %.*s(jsval, &val); ", typ.len, typ.str, fn_name.len, fn_name.str) ;
 
 }
 ;
 
return  _STR("\n*res = new_array(0, 0, sizeof(%.*s));\nconst cJSON *jsval = NULL;\ncJSON_ArrayForEach(jsval, root)\n{\n%.*s \n  array__push(res, &val);\n}\n", typ.len, typ.str, s.len, s.str) ;
 
 
 }
 string js_enc_name(string typ) {
 
string name= _STR("json__jsencode_%.*s", typ.len, typ.str) ;
 
return  name ;
 
 
 }
 string js_dec_name(string typ) {
 
string name= _STR("json__jsdecode_%.*s", typ.len, typ.str) ;
 
return  name ;
 
 
 }
 string Parser_encode_array(Parser* p, string typ) {
 
 typ  =  string_replace( typ , tos2((byte*)"array_") , tos2((byte*)"") ) ;
 
string fn_name= js_enc_name ( typ ) ;
 
return  _STR("\no = cJSON_CreateArray();\nfor (int i = 0; i < val.len; i++){\n  cJSON_AddItemToArray(o, %.*s(  ((%.*s*)val.data)[i]  ));\n} \n", fn_name.len, fn_name.str, typ.len, typ.str) ;
 
 
 }
 string modules_path() {
 
return string_add( os__home_dir ( ) , tos2((byte*)"/.vmodules/") ) ;
 
 
 }
 int main(int argc, char** argv) {
 init_consts();
 os__args = os__init_os_args(argc, argv);
 
array_string args= env_vflags_and_os_args ( ) ;
 
 if (_IN(string,  tos2((byte*)"-v") ,  args )  || _IN(string,  tos2((byte*)"--version") ,  args )  || _IN(string,  tos2((byte*)"version") ,  args ) ) {
 
printf( "V %.*s\n", main__Version.len, main__Version.str ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"-h") ,  args )  || _IN(string,  tos2((byte*)"--help") ,  args )  || _IN(string,  tos2((byte*)"help") ,  args ) ) {
 
 println ( main__HelpText ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"translate") ,  args ) ) {
 
 println ( tos2((byte*)"Translating C to V will be available in V 0.3") ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"up") ,  args ) ) {
 
 update_v ( ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"get") ,  args ) ) {
 
 println ( tos2((byte*)"use `v install` to install modules from vpm.vlang.io") ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"install") ,  args ) ) {
 
string mod=*(string*)  array_last( args ) ;
 
 if ( args .len != 3  ||  mod .len < 2 ) {
 
 println ( tos2((byte*)"usage: v install [module]") ) ;
 
 return 0 ;
 
 }
 ;
 
string vroot= os__dir ( os__executable ( ) ) ;
 
string vget= _STR("%.*s/tools/vget", vroot.len, vroot.str) ;
 
 if ( ! os__file_exists ( vget ) ) {
 
 println ( tos2((byte*)"Building vget...") ) ;
 
 os__chdir (string_add( vroot , tos2((byte*)"/tools") ) ) ;
 
string vexec= ( *(string*) array__get( os__args , 0) ) ;
 
 os__exec ( _STR("%.*s vget.v", vexec.len, vexec.str) ) ;
 
 println ( tos2((byte*)"Done.") ) ;
 
 }
 ;
 
printf( "Installing module %.*s...\n", mod.len, mod.str ) ;
 
 os__exec ( _STR("%.*s %.*s", vget.len, vget.str, mod.len, mod.str) ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"fmt") ,  args ) ) {
 
string file=*(string*)  array_last( args ) ;
 
 if ( ! os__file_exists ( file ) ) {
 
printf( "\"%.*s\" does not exist\n", file.len, file.str ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 if ( ! string_ends_with( file , tos2((byte*)".v") ) ) {
 
 println ( tos2((byte*)"v fmt can only be used on .v files") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 println ( tos2((byte*)"vfmt is temporarily disabled") ) ;
 
 return 0 ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"get") ,  args ) ) {
 
 if ( ! os__file_exists ( main__ModPath ) ) {
 
 os__mkdir ( main__ModPath ) ;
 
 }
 ;
 
 }
 ;
 
 if ( args .len < 2  ||  ( args .len == 2  && string_eq( ( *(string*) array__get( args , 1) ) , tos2((byte*)"-") ) ) ) {
 
 run_repl ( ) ;
 
 return 0 ;
 
 }
 ;
 
V* v= new_v ( args ) ;
 
 if ( v ->pref ->is_verbose ) {
 
 println (array_string_str( args ) ) ;
 
 }
 ;
 
 if (_IN(string,  tos2((byte*)"doc") ,  args ) ) {
 
 v_exit ( 0 ) ;
 
 }
 ;
 
 V_compile( v ) ;
 
 
 }
 void V_compile(V* v) {
 
CGen* cgen= v ->cgen ;
 
 CGen_genln( cgen , tos2((byte*)"// Generated by V") ) ;
 
 V_add_v_files_to_compile( v ) ;
 
 if ( v ->pref ->is_verbose ) {
 
 println ( tos2((byte*)"all .v files:") ) ;
 
 println (array_string_str( v ->files ) ) ;
 
 }
 ;
 
 array_string tmp13 =  v ->files;
 ;
for (int tmp14 = 0; tmp14 < tmp13 .len; tmp14 ++) {
 string file = ((string *) tmp13.data)[tmp14];
 
 
Parser p= V_new_parser( v , file , main__Pass_decl ) ;
 
 Parser_parse(& /* ? */ p ) ;
 
 }
 ;
 
 cgen ->pass  =  main__Pass_main ;
 
 if ( v ->pref ->is_play ) {
 
 CGen_genln( cgen , tos2((byte*)"#define VPLAY (1) ") ) ;
 
 }
 ;
 
 CGen_genln( cgen , tos2((byte*)"   \n#include <stdio.h>  // TODO remove all these includes, define all function signatures and types manually \n#include <stdlib.h>\n#include <signal.h>\n#include <stdarg.h> // for va_list \n#include <inttypes.h>  // int64_t etc \n#include <string.h> // memcpy \n\n#define STRUCT_DEFAULT_VALUE {}\n#define EMPTY_STRUCT_DECLARATION\n#define EMPTY_STRUCT_INIT\n#define OPTION_CAST(x) (x)\n\n#ifdef _WIN32\n#define WIN32_LEAN_AND_MEAN\n#include <windows.h>\n\n// must be included after <windows.h> \n#include <shellapi.h>\n\n#include <io.h> // _waccess\n#include <fcntl.h> // _O_U8TEXT\n#include <direct.h> // _wgetcwd\n//#include <WinSock2.h>\n#ifdef _MSC_VER\n// On MSVC these are the same (as long as /volatile:ms is passed)\n#define _Atomic volatile\n\n// MSVC can\'t parse some things properly\n#undef STRUCT_DEFAULT_VALUE\n#define STRUCT_DEFAULT_VALUE {0}\n#undef EMPTY_STRUCT_DECLARATION\n#define EMPTY_STRUCT_DECLARATION void *____dummy_variable;\n#undef EMPTY_STRUCT_INIT\n#define EMPTY_STRUCT_INIT 0\n#undef OPTION_CAST\n#define OPTION_CAST(x)\n#endif\n\nvoid pthread_mutex_lock(HANDLE *m) {\n	WaitForSingleObject(*m, INFINITE);\n}\n\nvoid pthread_mutex_unlock(HANDLE *m) {\n	ReleaseMutex(*m);\n}\n#else\n#include <pthread.h> \n#endif \n\n//================================== TYPEDEFS ================================*/ \n\ntypedef unsigned char byte;\ntypedef unsigned int uint;\ntypedef int64_t i64;\ntypedef int32_t i32;\ntypedef int16_t i16;\ntypedef int8_t i8;\ntypedef uint64_t u64;\ntypedef uint32_t u32;\ntypedef uint16_t u16;\ntypedef uint8_t u8;\ntypedef uint32_t rune;\ntypedef float f32;\ntypedef double f64; \ntypedef unsigned char* byteptr;\ntypedef int* intptr;\ntypedef void* voidptr;\ntypedef struct array array;\ntypedef struct map map;\ntypedef array array_string; \ntypedef array array_int; \ntypedef array array_byte; \ntypedef array array_uint; \ntypedef array array_float; \ntypedef array array_f32; \ntypedef array array_f64; \ntypedef map map_int; \ntypedef map map_string; \n#ifndef bool\n	typedef int bool;\n	#define true 1\n	#define false 0\n#endif\n\n//============================== HELPER C MACROS =============================*/ \n\n#define _PUSH(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push(arr, &tmp);}\n#define _PUSH_MANY(arr, val, tmp, tmp_typ) {tmp_typ tmp = (val); array__push_many(arr, tmp.data, tmp.len);}\n#define _IN(typ, val, arr) array_##typ##_contains(arr, val) \n#define _IN_MAP(val, m) map__exists(m, val) \n#define ALLOC_INIT(type, ...) (type *)memdup((type[]){ __VA_ARGS__ }, sizeof(type)) \n\n//================================== GLOBALS =================================*/   \n//int V_ZERO = 0; \nbyteptr g_str_buf; \nint load_so(byteptr);\nvoid reload_so();\nvoid init_consts();") ) ;
 
 if ( v ->os != main__OS_windows  &&  v ->os != main__OS_msvc ) {
 
 if ( v ->pref ->is_so ) {
 
 CGen_genln( cgen , tos2((byte*)"pthread_mutex_t live_fn_mutex;") ) ;
 
 }
 ;
 
 if ( v ->pref ->is_live ) {
 
 CGen_genln( cgen , tos2((byte*)"pthread_mutex_t live_fn_mutex = PTHREAD_MUTEX_INITIALIZER;") ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( v ->pref ->is_so ) {
 
 CGen_genln( cgen , tos2((byte*)"HANDLE live_fn_mutex;") ) ;
 
 }
 ;
 
 if ( v ->pref ->is_live ) {
 
 CGen_genln( cgen , tos2((byte*)"HANDLE live_fn_mutex = 0;") ) ;
 
 }
 ;
 
 }
 ;
 
bool imports_json= array_string_contains( v ->table ->imports , tos2((byte*)"json") ) ;
 
 if ( v ->os == main__OS_mac  &&  ( ( v ->pref ->build_mode == main__BuildMode_embed_vlib  &&  array_string_contains( v ->table ->imports , tos2((byte*)"ui") ) )  ||  ( v ->pref ->build_mode == main__BuildMode_build  &&  string_contains( v ->dir , tos2((byte*)"/ui") ) ) ) ) {
 
 CGen_genln( cgen , tos2((byte*)"id defaultFont = 0; // main.v") ) ;
 
 }
 ;
 
 if ( ( imports_json  &&  v ->pref ->build_mode == main__BuildMode_embed_vlib )  ||  ( v ->pref ->build_mode == main__BuildMode_build  &&  string_contains( v ->out_name , tos2((byte*)"json.o") ) ) ) {
 
 }
 ;
 
 if ( v ->pref ->build_mode == main__BuildMode_default_mode ) {
 
 if ( imports_json ) {
 
 CGen_genln( cgen , tos2((byte*)"#include \"cJSON.h\"") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( v ->pref ->build_mode == main__BuildMode_embed_vlib  ||  v ->pref ->build_mode == main__BuildMode_default_mode ) {
 
 CGen_genln( cgen , tos2((byte*)"int g_test_ok = 1; ") ) ;
 
 if ( array_string_contains( v ->table ->imports , tos2((byte*)"json") ) ) {
 
 CGen_genln( cgen , tos2((byte*)" \n#define js_get(object, key) cJSON_GetObjectItemCaseSensitive((object), (key))\n") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( array_string_contains( os__args , tos2((byte*)"-debug_alloc") ) ) {
 
 CGen_genln( cgen , tos2((byte*)"#define DEBUG_ALLOC 1") ) ;
 
 }
 ;
 
 CGen_genln( cgen , tos2((byte*)"/*================================== FNS =================================*/") ) ;
 
 CGen_genln( cgen , tos2((byte*)"this line will be replaced with definitions") ) ;
 
int defs_pos= cgen ->lines .len - 1 ;
 
 array_string tmp18 =  v ->files;
 ;
for (int tmp19 = 0; tmp19 < tmp18 .len; tmp19 ++) {
 string file = ((string *) tmp18.data)[tmp19];
 
 
Parser p= V_new_parser( v , file , main__Pass_main ) ;
 
 Parser_parse(& /* ? */ p ) ;
 
 if ( ! v ->pref ->nofmt  &&  ! string_contains( file , tos2((byte*)"/vlib/") ) ) {
 
 }
 ;
 
 }
 ;
 
 V_log(& /* ? */* v , tos2((byte*)"Done parsing.") ) ;
 
strings__Builder d= strings__new_builder ( 10000 ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->includes ) ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->typedefs ) ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->types ) ) ;
 
 strings__Builder_writeln(& /* ? */ d , tos2((byte*)"\nstring _STR(const char*, ...);\n") ) ;
 
 strings__Builder_writeln(& /* ? */ d , tos2((byte*)"\nstring _STR_TMP(const char*, ...);\n") ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->fns ) ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->consts ) ) ;
 
 strings__Builder_writeln(& /* ? */ d , array_string_join_lines( cgen ->thread_args ) ) ;
 
 if ( v ->pref ->is_prof ) {
 
 strings__Builder_writeln(& /* ? */ d , tos2((byte*)"; // Prof counters:") ) ;
 
 strings__Builder_writeln(& /* ? */ d , V_prof_counters( v ) ) ;
 
 }
 ;
 
string dd= strings__Builder_str( d ) ;
 
 array_set(& /* ? */ cgen ->lines , defs_pos ,& /*11 EXP:"void*" GOT:"string" */ dd ) ;
 
 if ( v ->pref ->build_mode == main__BuildMode_default_mode  ||  v ->pref ->build_mode == main__BuildMode_embed_vlib ) {
 
string consts_init_body= array_string_join_lines( cgen ->consts_init ) ;
 
 array_string tmp24 =  v ->table ->imports;
 ;
for (int tmp25 = 0; tmp25 < tmp24 .len; tmp25 ++) {
 string imp = ((string *) tmp24.data)[tmp25];
 
 
 if (string_eq( imp , tos2((byte*)"http") ) ) {
 
 consts_init_body = string_add(consts_init_body,  tos2((byte*)"\n http__init_module();") ) ;
 
 }
 ;
 
 }
 ;
 
 CGen_genln( cgen , _STR("void init_consts() { \n#ifdef _WIN32\n _setmode(_fileno(stdout), _O_U8TEXT);\nSetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | 0x0004); \n// ENABLE_VIRTUAL_TERMINAL_PROCESSING\n#endif\n g_str_buf=malloc(1000);\n%.*s \n}", consts_init_body.len, consts_init_body.str) ) ;
 
 CGen_genln( cgen , tos2((byte*)"\nstring _STR(const char *fmt, ...) {\n	va_list argptr;\n	va_start(argptr, fmt);\n	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  \n	va_end(argptr);\n	byte* buf = malloc(len);  \n	va_start(argptr, fmt);\n	vsprintf(buf, fmt, argptr);\n	va_end(argptr);\n#ifdef DEBUG_ALLOC \n	puts(\"_STR:\"); \n	puts(buf); \n#endif \n	return tos2(buf);\n}\n\nstring _STR_TMP(const char *fmt, ...) {\n	va_list argptr;\n	va_start(argptr, fmt);\n	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  \n	va_end(argptr);\n	va_start(argptr, fmt);\n	vsprintf(g_str_buf, fmt, argptr);\n	va_end(argptr);\n#ifdef DEBUG_ALLOC \n	//puts(\"_STR_TMP:\"); \n	//puts(g_str_buf); \n#endif \n	return tos2(g_str_buf);\n}\n\n") ) ;
 
 }
 ;
 
 if ( v ->pref ->build_mode != main__BuildMode_build ) {
 
 if ( ! Table_main_exists(& /* ? */* v ->table )  &&  ! v ->pref ->is_test ) {
 
 if ( v ->pref ->is_script ) {
 
 CGen_genln( cgen , _STR("int main() { init_consts(); %.*s; return 0; }", cgen ->fn_main.len, cgen ->fn_main.str) ) ;
 
 }
  else { 
 
 println ( tos2((byte*)"panic: function `main` is undeclared in the main module") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 }
  else  if ( v ->pref ->is_test ) {
 
 CGen_genln( cgen , tos2((byte*)"int main() { init_consts();") ) ;
 
 map_Fn tmp26 =  v ->table ->fns ;
 array_string keys_tmp26 = map_keys(& tmp26 ); 
 for (int l = 0; l < keys_tmp26 .len; l++) {
   string key = ((string*)keys_tmp26 .data)[l];
 Fn f = {0}; map_get(tmp26, key, & f);
 
 
 if ( string_starts_with( f .name , tos2((byte*)"test_") ) ) {
 
 CGen_genln( cgen , _STR("%.*s();", f .name.len, f .name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 CGen_genln( cgen , tos2((byte*)"return g_test_ok == 0; }") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( v ->pref ->is_live ) {
 
string file= v ->dir ;
 
string file_base= string_replace( v ->dir , tos2((byte*)".v") , tos2((byte*)"") ) ;
 
string so_name=string_add( file_base , tos2((byte*)".so") ) ;
 
string vexe= ( *(string*) array__get( os__args , 0) ) ;
 
 if (string_eq( os__user_os ( ) , tos2((byte*)"windows") ) ) {
 
 vexe  =  string_replace( vexe , tos2((byte*)"\\") , tos2((byte*)"\\\\") ) ;
 
 }
 ;
 
string msvc= tos2((byte*)"") ;
 
 if ( v ->os == main__OS_msvc ) {
 
 msvc  =  tos2((byte*)"-os msvc") ;
 
 }
 ;
 
string debug= tos2((byte*)"") ;
 
 if ( v ->pref ->is_debug ) {
 
 debug  =  tos2((byte*)"-debug") ;
 
 }
 ;
 
 os__system ( _STR("%.*s %.*s %.*s -o %.*s -shared %.*s", vexe.len, vexe.str, msvc.len, msvc.str, debug.len, debug.str, file_base.len, file_base.str, file.len, file.str) ) ;
 
 CGen_genln( cgen , tos2((byte*)"\n\nvoid lfnmutex_print(char *s){\n	if(0){\n		fflush(stderr);\n		fprintf(stderr,\">> live_fn_mutex: %p | %s\\n\", &live_fn_mutex, s);\n		fflush(stderr);\n	}\n}\n") ) ;
 
 if ( v ->os != main__OS_windows  &&  v ->os != main__OS_msvc ) {
 
 CGen_genln( cgen , tos2((byte*)"\n#include <dlfcn.h>\nvoid* live_lib=0;\nint load_so(byteptr path) {\n	char cpath[1024];\n	sprintf(cpath,\"./%s\", path);\n	//printf(\"load_so %s\\n\", cpath); \n	if (live_lib) dlclose(live_lib);\n	live_lib = dlopen(cpath, RTLD_LAZY);\n	if (!live_lib) {\n		puts(\"open failed\"); \n		exit(1); \n		return 0;\n	}\n") ) ;
 
 array_string tmp35 =  cgen ->so_fns;
 ;
for (int tmp36 = 0; tmp36 < tmp35 .len; tmp36 ++) {
 string so_fn = ((string *) tmp35.data)[tmp36];
 
 
 CGen_genln( cgen , _STR("%.*s = dlsym(live_lib, \"%.*s\");  ", so_fn.len, so_fn.str, so_fn.len, so_fn.str) ) ;
 
 }
 ;
 
 }
  else { 
 
 CGen_genln( cgen , tos2((byte*)"\nvoid* live_lib=0;\nint load_so(byteptr path) {\n	char cpath[1024];\n	sprintf(cpath, \"./%s\", path);\n	if (live_lib) FreeLibrary(live_lib);\n	live_lib = LoadLibraryA(cpath);\n	if (!live_lib) {\n		puts(\"open failed\");\n		exit(1);\n		return 0;\n	}\n") ) ;
 
 array_string tmp37 =  cgen ->so_fns;
 ;
for (int tmp38 = 0; tmp38 < tmp37 .len; tmp38 ++) {
 string so_fn = ((string *) tmp37.data)[tmp38];
 
 
 CGen_genln( cgen , _STR("%.*s = (void *)GetProcAddress(live_lib, \"%.*s\");  ", so_fn.len, so_fn.str, so_fn.len, so_fn.str) ) ;
 
 }
 ;
 
 }
 ;
 
 CGen_genln( cgen , _STR("return 1; \n}\n\nint _live_reloads = 0;\nvoid reload_so() {\n	char new_so_base[1024];\n	char new_so_name[1024];\n	char compile_cmd[1024];\n	int last = os__file_last_mod_unix(tos2(\"%.*s\"));\n	while (1) {\n		// TODO use inotify\n		int now = os__file_last_mod_unix(tos2(\"%.*s\"));\n		if (now != last) {\n			last = now;\n			_live_reloads++;\n\n			//v -o bounce -shared bounce.v\n			sprintf(new_so_base, \".tmp.%%d.%.*s\", _live_reloads);\n			#ifdef _WIN32\n			// We have to make this directory becuase windows WILL NOT\n			// do it for us\n			os__mkdir(string_all_before_last(tos2(new_so_base), tos2(\"/\")));\n			#endif\n			#ifdef _MSC_VER\n			sprintf(new_so_name, \"%%s.dll\", new_so_base);\n			#else\n			sprintf(new_so_name, \"%%s.so\", new_so_base);\n			#endif\n			sprintf(compile_cmd, \"%.*s %.*s -o %%s -shared %.*s\", new_so_base);\n			os__system(tos2(compile_cmd));\n\n			if( !os__file_exists(tos2(new_so_name)) ) {\n				fprintf(stderr, \"Errors while compiling %.*s\\n\");\n				continue;        \n			}\n      \n			lfnmutex_print(\"reload_so locking...\");\n			pthread_mutex_lock(&live_fn_mutex);\n			lfnmutex_print(\"reload_so locked\");\n        \n			live_lib = 0; // hack: force skipping dlclose/1, the code may be still used...\n			load_so(new_so_name);\n			#ifndef _WIN32\n			unlink(new_so_name); // removing the .so file from the filesystem after dlopen-ing it is safe, since it will still be mapped in memory.\n			#else\n			_unlink(new_so_name);\n			#endif\n			//if(0 == rename(new_so_name, \"%.*s\")){\n			//	load_so(\"%.*s\"); \n			//}\n\n			lfnmutex_print(\"reload_so unlocking...\");  \n			pthread_mutex_unlock(&live_fn_mutex);  \n			lfnmutex_print(\"reload_so unlocked\");\n\n		}\n		time__sleep_ms(100); \n	}\n}\n", file.len, file.str, file.len, file.str, file_base.len, file_base.str, vexe.len, vexe.str, msvc.len, msvc.str, file.len, file.str, file.len, file.str, so_name.len, so_name.str, so_name.len, so_name.str) ) ;
 
 }
 ;
 
 if ( v ->pref ->is_so ) {
 
 CGen_genln( cgen , tos2((byte*)" int load_so(byteptr path) { return 0; }") ) ;
 
 }
 ;
 
 CGen_save( cgen ) ;
 
 if ( v ->pref ->is_verbose ) {
 
 V_log(& /* ? */* v , tos2((byte*)"flags=") ) ;
 
 println (array_string_str( v ->table ->flags ) ) ;
 
 }
 ;
 
 V_cc( v ) ;
 
 if ( v ->pref ->is_test  ||  v ->pref ->is_run ) {
 
 if ( v ->pref ->is_verbose ) {
 
printf( "============ running %.*s ============\n", v ->out_name.len, v ->out_name.str ) ;
 
 }
 ;
 
string cmd= ( string_starts_with( v ->out_name , tos2((byte*)"/") ) ) ? ( v ->out_name ) : (string_add( tos2((byte*)"./") , v ->out_name ) ) ;
 
 #ifdef _WIN32
 
 cmd  =  v ->out_name ;
 
 cmd  =  string_replace( cmd , tos2((byte*)"/") , tos2((byte*)"\\") ) ;
 
 #endif
 ;
 
 if ( os__args .len > 3 ) {
 
 cmd = string_add(cmd, string_add( tos2((byte*)" ") , array_string_join( array_right( os__args , 3 ) , tos2((byte*)" ") ) ) ) ;
 
 }
 ;
 
int ret= os__system ( cmd ) ;
 
 if ( ret != 0 ) {
 
 if ( ! v ->pref ->is_test ) {
 
string s= os__exec ( cmd ) ;
 
 println ( s ) ;
 
 println ( tos2((byte*)"failed to run the compiled program") ) ;
 
 }
 ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void V_cc_windows_cross(V* c) {
 
 if ( ! string_ends_with( c ->out_name , tos2((byte*)".exe") ) ) {
 
 c ->out_name  = string_add( c ->out_name , tos2((byte*)".exe") ) ;
 
 }
 ;
 
string args= _STR("-o %.*s -w -L. ", c ->out_name.len, c ->out_name.str) ;
 
 array_string tmp43 =  c ->table ->flags;
 ;
for (int tmp44 = 0; tmp44 < tmp43 .len; tmp44 ++) {
 string flag = ((string *) tmp43.data)[tmp44];
 
 
 if ( ! string_starts_with( flag , tos2((byte*)"-l") ) ) {
 
 args = string_add(args,  flag ) ;
 
 args = string_add(args,  tos2((byte*)" ") ) ;
 
 }
 ;
 
 }
 ;
 
string libs= tos2((byte*)"") ;
 
 if ( c ->pref ->build_mode == main__BuildMode_default_mode ) {
 
 libs  =  _STR("\"%.*s/vlib/builtin.o\"", main__ModPath.len, main__ModPath.str) ;
 
 if ( ! os__file_exists ( libs ) ) {
 
 println ( tos2((byte*)"`builtin.o` not found") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 array_string tmp46 =  c ->table ->imports;
 ;
for (int tmp47 = 0; tmp47 < tmp46 .len; tmp47 ++) {
 string imp = ((string *) tmp46.data)[tmp47];
 
 
 libs = string_add(libs,  _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len, main__ModPath.str, imp.len, imp.str) ) ;
 
 }
 ;
 
 }
 ;
 
 args = string_add(args,  _STR(" %.*s ", c ->out_name_c.len, c ->out_name_c.str) ) ;
 
 array_string tmp48 =  c ->table ->flags;
 ;
for (int tmp49 = 0; tmp49 < tmp48 .len; tmp49 ++) {
 string flag = ((string *) tmp48.data)[tmp49];
 
 
 if ( string_starts_with( flag , tos2((byte*)"-l") ) ) {
 
 args = string_add(args,  flag ) ;
 
 args = string_add(args,  tos2((byte*)" ") ) ;
 
 }
 ;
 
 }
 ;
 
 println ( tos2((byte*)"Cross compiling for Windows...") ) ;
 
string winroot= _STR("%.*s/winroot", main__ModPath.len, main__ModPath.str) ;
 
 if ( ! os__dir_exists ( winroot ) ) {
 
string winroot_url= tos2((byte*)"https://github.com/vlang/v/releases/download/v0.1.10/winroot.zip") ;
 
printf( "\"%.*s\" not found. Download it from %.*s and save in %.*s\n", winroot.len, winroot.str, winroot_url.len, winroot_url.str, main__ModPath.len, main__ModPath.str ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
string obj_name= c ->out_name ;
 
 obj_name  =  string_replace( obj_name , tos2((byte*)".exe") , tos2((byte*)"") ) ;
 
 obj_name  =  string_replace( obj_name , tos2((byte*)".o.o") , tos2((byte*)".o") ) ;
 
string include= _STR("-I %.*s/include ", winroot.len, winroot.str) ;
 
string cmd= _STR("clang -o %.*s -w %.*s -DUNICODE -D_UNICODE -m32 -c -target x86_64-win32 %.*s/%.*s", obj_name.len, obj_name.str, include.len, include.str, main__ModPath.len, main__ModPath.str, c ->out_name_c.len, c ->out_name_c.str) ;
 
 if ( c ->pref ->show_c_cmd ) {
 
 println ( cmd ) ;
 
 }
 ;
 
 if ( os__system ( cmd ) != 0 ) {
 
 println ( tos2((byte*)"Cross compilation for Windows failed. Make sure you have clang installed.") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 if ( c ->pref ->build_mode != main__BuildMode_build ) {
 
string link_cmd=string_add(string_add( _STR("lld-link %.*s %.*s/lib/libcmt.lib ", obj_name.len, obj_name.str, winroot.len, winroot.str) , _STR("%.*s/lib/libucrt.lib %.*s/lib/kernel32.lib %.*s/lib/libvcruntime.lib ", winroot.len, winroot.str, winroot.len, winroot.str, winroot.len, winroot.str) ) , _STR("%.*s/lib/uuid.lib", winroot.len, winroot.str) ) ;
 
 if ( c ->pref ->show_c_cmd ) {
 
 println ( link_cmd ) ;
 
 }
 ;
 
 if ( os__system ( link_cmd ) != 0 ) {
 
 println ( tos2((byte*)"Cross compilation for Windows failed. Make sure you have lld linker installed.") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 }
 ;
 
 println ( tos2((byte*)"Done!") ) ;
 
 
 }
 void V_cc(V* v) {
 
 if ( v ->os == main__OS_windows ) {
 
 #ifndef _WIN32
 
 V_cc_windows_cross(& /* ? */* v ) ;
 
 return ;
 
 #endif
 ;
 
 }
 ;
 
 #ifdef _WIN32
 
 if ( v ->os == main__OS_msvc ) {
 
 cc_msvc ( v ) ;
 
 return ;
 
 }
 ;
 
 #endif
 ;
 
bool linux_host=string_eq( os__user_os ( ) , tos2((byte*)"linux") ) ;
 
 V_log(& /* ? */* v , _STR("cc() isprod=%d outname=%.*s", v ->pref ->is_prod, v ->out_name.len, v ->out_name.str) ) ;
 
array_string a=new_array_from_c_array(3, 3, sizeof(string), (string[]) {  v ->pref ->cflags ,  tos2((byte*)"-std=gnu11") ,  tos2((byte*)"-w")  }) ;
 
string flags= array_string_join( v ->table ->flags , tos2((byte*)" ") ) ;
 
 if ( v ->pref ->is_so ) {
 
_PUSH(& a , ( tos2((byte*)"-shared -fPIC ") ), tmp59, string) ;
 
 v ->out_name  = string_add( v ->out_name , tos2((byte*)".so") ) ;
 
 }
 ;
 
 if ( v ->pref ->is_prod ) {
 
_PUSH(& a , ( tos2((byte*)"-O2") ), tmp60, string) ;
 
 }
  else { 
 
_PUSH(& a , ( tos2((byte*)"-g") ), tmp61, string) ;
 
 }
 ;
 
 if ( v ->pref ->is_live  ||  v ->pref ->is_so ) {
 
 if ( ( v ->os == main__OS_linux  || string_eq( os__user_os ( ) , tos2((byte*)"linux") ) ) ) {
 
_PUSH(& a , ( tos2((byte*)"-rdynamic") ), tmp62, string) ;
 
 }
 ;
 
 if ( ( v ->os == main__OS_mac  || string_eq( os__user_os ( ) , tos2((byte*)"mac") ) ) ) {
 
_PUSH(& a , ( tos2((byte*)"-flat_namespace") ), tmp63, string) ;
 
 }
 ;
 
 }
 ;
 
string libs= tos2((byte*)"") ;
 
 if ( v ->pref ->build_mode == main__BuildMode_build ) {
 
_PUSH(& a , ( tos2((byte*)"-c") ), tmp65, string) ;
 
 }
  else  if ( v ->pref ->build_mode == main__BuildMode_embed_vlib ) {
 
 }
  else  if ( v ->pref ->build_mode == main__BuildMode_default_mode ) {
 
 libs  =  _STR("\"%.*s/vlib/builtin.o\"", main__ModPath.len, main__ModPath.str) ;
 
 if ( ! os__file_exists ( libs ) ) {
 
 println ( tos2((byte*)"`builtin.o` not found") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 array_string tmp66 =  v ->table ->imports;
 ;
for (int tmp67 = 0; tmp67 < tmp66 .len; tmp67 ++) {
 string imp = ((string *) tmp66.data)[tmp67];
 
 
 if (string_eq( imp , tos2((byte*)"webview") ) ) {
 
 continue
 ;
 
 }
 ;
 
 libs = string_add(libs,  _STR(" \"%.*s/vlib/%.*s.o\"", main__ModPath.len, main__ModPath.str, imp.len, imp.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( v ->pref ->sanitize ) {
 
_PUSH(& a , ( tos2((byte*)"-fsanitize=leak") ), tmp68, string) ;
 
 }
 ;
 
string sysroot= tos2((byte*)"/Users/alex/tmp/lld/linuxroot/") ;
 
 if ( v ->os == main__OS_linux  &&  ! linux_host ) {
 
_PUSH(& a , ( _STR("-c --sysroot=%.*s -target x86_64-linux-gnu", sysroot.len, sysroot.str) ), tmp70, string) ;
 
 if ( ! string_ends_with( v ->out_name , tos2((byte*)".o") ) ) {
 
 v ->out_name  = string_add( v ->out_name , tos2((byte*)".o") ) ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& a , ( _STR("-o %.*s", v ->out_name.len, v ->out_name.str) ), tmp71, string) ;
 
 if ( os__dir_exists ( v ->out_name ) ) {
 
 v_panic ( _STR("\'%.*s\' is a directory", v ->out_name.len, v ->out_name.str) ) ;
 
 }
 ;
 
_PUSH(& a , ( _STR("\".%.*s\"", v ->out_name_c.len, v ->out_name_c.str) ), tmp72, string) ;
 
 if ( v ->os == main__OS_mac ) {
 
_PUSH(& a , ( tos2((byte*)"-mmacosx-version-min=10.7") ), tmp73, string) ;
 
 }
 ;
 
_PUSH(& a , ( flags ), tmp74, string) ;
 
_PUSH(& a , ( libs ), tmp75, string) ;
 
 if ( v ->os == main__OS_mac ) {
 
_PUSH(& a , ( tos2((byte*)"-x objective-c") ), tmp76, string) ;
 
 }
 ;
 
 if ( v ->pref ->build_mode != main__BuildMode_build  &&  ( v ->os == main__OS_linux  ||  v ->os == main__OS_freebsd  ||  v ->os == main__OS_openbsd  ||  v ->os == main__OS_netbsd  ||  v ->os == main__OS_dragonfly ) ) {
 
_PUSH(& a , ( tos2((byte*)"-lm -lpthread ") ), tmp77, string) ;
 
 if ( v ->os == main__OS_linux ) {
 
_PUSH(& a , ( tos2((byte*)" -ldl ") ), tmp78, string) ;
 
 }
 ;
 
 }
 ;
 
 if ( v ->os == main__OS_windows ) {
 
_PUSH(& a , ( tos2((byte*)"-DUNICODE -D_UNICODE") ), tmp79, string) ;
 
 }
 ;
 
string args= array_string_join( a , tos2((byte*)" ") ) ;
 
string cmd= _STR("cc %.*s", args.len, args.str) ;
 
 #ifdef _WIN32
 
 cmd  =  _STR("gcc %.*s", args.len, args.str) ;
 
 #endif
 ;
 
 if ( string_ends_with( v ->out_name , tos2((byte*)".c") ) ) {
 
 os__mv ( _STR(".%.*s", v ->out_name_c.len, v ->out_name_c.str) , v ->out_name ) ;
 
 v_exit ( 0 ) ;
 
 }
 ;
 
i64 ticks= time__ticks ( ) ;
 
string res= os__exec ( cmd ) ;
 
i64 diff= time__ticks ( ) - ticks ;
 
 if ( v ->pref ->show_c_cmd  ||  v ->pref ->is_verbose ) {
 
 println ( tos2((byte*)"\n==========") ) ;
 
 println ( cmd ) ;
 
printf( "cc took %lld ms\n", diff ) ;
 
 println ( tos2((byte*)"=========\n") ) ;
 
 }
 ;
 
 if ( string_contains( res , tos2((byte*)"error: ") ) ) {
 
 if ( v ->pref ->is_debug ) {
 
 println ( res ) ;
 
 }
  else { 
 
 v_print ( string_limit( res , 200 ) ) ;
 
 if ( res .len > 200 ) {
 
 println ( tos2((byte*)"...\n(Use `v -debug` to print the entire error message)\n") ) ;
 
 }
 ;
 
 }
 ;
 
 v_panic (string_add( tos2((byte*)"C error. This should never happen. ") , tos2((byte*)"Please create a GitHub issue: https://github.com/vlang/v/issues/new/choose") ) ) ;
 
 }
 ;
 
 if ( v ->os == main__OS_linux  &&  ! linux_host  &&  v ->pref ->build_mode != main__BuildMode_build ) {
 
 v ->out_name  =  string_replace( v ->out_name , tos2((byte*)".o") , tos2((byte*)"") ) ;
 
string obj_file=string_add( v ->out_name , tos2((byte*)".o") ) ;
 
printf( "linux obj_file=%.*s out_name=%.*s\n", obj_file.len, obj_file.str, v ->out_name.len, v ->out_name.str ) ;
 
string ress= os__exec (string_add(string_add(string_add(string_add(string_add(string_add(string_add(string_add( _STR("/usr/local/Cellar/llvm/8.0.0/bin/ld.lld --sysroot=%.*s ", sysroot.len, sysroot.str) , _STR("-v -o %.*s ", v ->out_name.len, v ->out_name.str) ) , tos2((byte*)"-m elf_x86_64 -dynamic-linker /lib64/ld-linux-x86-64.so.2 ") ) , tos2((byte*)"/usr/lib/x86_64-linux-gnu/crt1.o ") ) , _STR("%.*s/lib/x86_64-linux-gnu/libm-2.28.a ", sysroot.len, sysroot.str) ) , tos2((byte*)"/usr/lib/x86_64-linux-gnu/crti.o ") ) , obj_file ) , tos2((byte*)" /usr/lib/x86_64-linux-gnu/libc.so ") ) , tos2((byte*)"/usr/lib/x86_64-linux-gnu/crtn.o") ) ) ;
 
 println ( ress ) ;
 
 if ( string_contains( ress , tos2((byte*)"error:") ) ) {
 
 v_exit ( 1 ) ;
 
 }
 ;
 
printf( "linux cross compilation done. resulting binary: \"%.*s\"\n", v ->out_name.len, v ->out_name.str ) ;
 
 }
 ;
 
 if ( ! v ->pref ->is_debug  && string_ne( v ->out_name_c , tos2((byte*)"v.c") )  && string_ne( v ->out_name_c , tos2((byte*)"v_macos.c") ) ) {
 
 os__rm ( _STR(".%.*s", v ->out_name_c.len, v ->out_name_c.str) ) ;
 
 }
 ;
 
 
 }
 array_string V_v_files_from_dir(V* v, string dir) {
 
array_string res=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( ! os__file_exists ( dir ) ) {
 
 v_panic ( _STR("%.*s doesn\'t exist", dir.len, dir.str) ) ;
 
 }
  else  if ( ! os__dir_exists ( dir ) ) {
 
 v_panic ( _STR("%.*s isn\'t a directory", dir.len, dir.str) ) ;
 
 }
 ;
 
array_string files= os__ls ( dir ) ;
 
 if ( v ->pref ->is_verbose ) {
 
printf( "v_files_from_dir (\"%.*s\")\n", dir.len, dir.str ) ;
 
 }
 ;
 
 array_string_sort(& /* ? */ files ) ;
 
 array_string tmp89 =  files;
 ;
for (int tmp90 = 0; tmp90 < tmp89 .len; tmp90 ++) {
 string file = ((string *) tmp89.data)[tmp90];
 
 
 if ( ! string_ends_with( file , tos2((byte*)".v") )  &&  ! string_ends_with( file , tos2((byte*)".vh") ) ) {
 
 continue
 ;
 
 }
 ;
 
 if ( string_ends_with( file , tos2((byte*)"_test.v") ) ) {
 
 continue
 ;
 
 }
 ;
 
 if ( string_ends_with( file , tos2((byte*)"_win.v") )  &&  ( v ->os != main__OS_windows  &&  v ->os != main__OS_msvc ) ) {
 
 continue
 ;
 
 }
 ;
 
 if ( string_ends_with( file , tos2((byte*)"_lin.v") )  &&  v ->os != main__OS_linux ) {
 
 continue
 ;
 
 }
 ;
 
 if ( string_ends_with( file , tos2((byte*)"_mac.v") )  &&  v ->os != main__OS_mac ) {
 
 continue
 ;
 
 }
 ;
 
 if ( string_ends_with( file , tos2((byte*)"_nix.v") )  &&  ( v ->os == main__OS_windows  ||  v ->os == main__OS_msvc ) ) {
 
 continue
 ;
 
 }
 ;
 
_PUSH(& res , ( _STR("%.*s/%.*s", dir.len, dir.str, file.len, file.str) ), tmp91, string) ;
 
 }
 ;
 
return  res ;
 
 
 }
 void V_add_v_files_to_compile(V* v) {
 
string dir= v ->dir ;
 
 V_log(& /* ? */* v , _STR("add_v_files(%.*s)", dir.len, dir.str) ) ;
 
array_string user_files=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
bool is_test_with_imports= string_ends_with( dir , tos2((byte*)"_test.v") )  &&  ( string_contains( dir , tos2((byte*)"/volt") )  ||  string_contains( dir , tos2((byte*)"/c2volt") ) ) ;
 
 if ( is_test_with_imports ) {
 
_PUSH(& user_files , ( dir ), tmp95, string) ;
 
int pos= string_last_index( dir , tos2((byte*)"/") ) ;
 
 dir  = string_add( string_left( dir , pos ) , tos2((byte*)"/") ) ;
 
 }
 ;
 
 if ( string_ends_with( dir , tos2((byte*)".v") ) ) {
 
_PUSH(& user_files , ( dir ), tmp97, string) ;
 
 dir  =  string_all_before( dir , tos2((byte*)"/") ) ;
 
 }
  else { 
 
array_string files= V_v_files_from_dir(& /* ? */* v , dir ) ;
 
 array_string tmp99 =  files;
 ;
for (int tmp100 = 0; tmp100 < tmp99 .len; tmp100 ++) {
 string file = ((string *) tmp99.data)[tmp100];
 
 
_PUSH(& user_files , ( file ), tmp101, string) ;
 
 }
 ;
 
 }
 ;
 
 if ( user_files .len == 0 ) {
 
 println ( tos2((byte*)"No input .v files") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 if ( v ->pref ->is_verbose ) {
 
 V_log(& /* ? */* v , tos2((byte*)"user_files:") ) ;
 
 println (array_string_str( user_files ) ) ;
 
 }
 ;
 
 array_string tmp102 =  v ->files;
 ;
for (int tmp103 = 0; tmp103 < tmp102 .len; tmp103 ++) {
 string file = ((string *) tmp102.data)[tmp103];
 
 
Parser p= V_new_parser( v , file , main__Pass_imports ) ;
 
 Parser_parse(& /* ? */ p ) ;
 
 }
 ;
 
 array_string tmp105 =  user_files;
 ;
for (int tmp106 = 0; tmp106 < tmp105 .len; tmp106 ++) {
 string file = ((string *) tmp105.data)[tmp106];
 
 
Parser p= V_new_parser( v , file , main__Pass_imports ) ;
 
 Parser_parse(& /* ? */ p ) ;
 
 }
 ;
 
 for (
int i= 0  ;  i < v ->table ->imports .len  ;  i ++ ) { 
 
 
string mod= ( *(string*) array__get( v ->table ->imports , i) ) ;
 
string import_path= V_find_module_path(& /* ? */* v , mod ) ;
 
array_string vfiles= V_v_files_from_dir(& /* ? */* v , import_path ) ;
 
 if ( vfiles .len == 0 ) {
 
 v_panic ( _STR("cannot import module %.*s (no .v files in \"%.*s\").", mod.len, mod.str, import_path.len, import_path.str) ) ;
 
 }
 ;
 
 array_string tmp114 =  vfiles;
 ;
for (int tmp115 = 0; tmp115 < tmp114 .len; tmp115 ++) {
 string file = ((string *) tmp114.data)[tmp115];
 
 
Parser p= V_new_parser( v , file , main__Pass_imports ) ;
 
 Parser_parse(& /* ? */ p ) ;
 
 }
 ;
 
 }
 ;
 
 if ( v ->pref ->is_verbose ) {
 
 V_log(& /* ? */* v , tos2((byte*)"imports:") ) ;
 
 println (array_string_str( v ->table ->imports ) ) ;
 
 }
 ;
 
ModDepGraph* dep_graph= new_mod_dep_graph ( ) ;
 
 ModDepGraph_from_import_tables( dep_graph , v ->table ->file_imports ) ;
 
ModDepGraph* deps_resolved= ModDepGraph_resolve(& /* ? */* dep_graph ) ;
 
 if ( ! deps_resolved ->acyclic ) {
 
 ModDepGraph_display(& /* ? */* deps_resolved ) ;
 
 v_panic ( tos2((byte*)"Import cycle detected.") ) ;
 
 }
 ;
 
 array_string tmp119 =  ModDepGraph_imports(& /* ? */* deps_resolved );
 ;
for (int tmp120 = 0; tmp120 < tmp119 .len; tmp120 ++) {
 string mod = ((string *) tmp119.data)[tmp120];
 
 
 if (string_eq( mod , v ->mod ) ) {
 
 continue
 ;
 
 }
 ;
 
string mod_path= V_find_module_path(& /* ? */* v , mod ) ;
 
array_string vfiles= V_v_files_from_dir(& /* ? */* v , mod_path ) ;
 
 array_string tmp123 =  vfiles;
 ;
for (int tmp124 = 0; tmp124 < tmp123 .len; tmp124 ++) {
 string file = ((string *) tmp123.data)[tmp124];
 
 
 if ( !_IN(string,  file ,  v ->files ) ) {
 
_PUSH(& v ->files , ( file ), tmp125, string) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 array_FileImportTable tmp126 =  v ->table ->file_imports;
 ;
for (int tmp127 = 0; tmp127 < tmp126 .len; tmp127 ++) {
 FileImportTable fit = ((FileImportTable *) tmp126.data)[tmp127];
 
 
 if ( !_IN(string,  fit .file_path ,  v ->files ) ) {
 
_PUSH(& v ->files , ( fit .file_path ), tmp128, string) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 string get_arg(string joined_args, string arg, string def) {
 
string key= _STR("-%.*s ", arg.len, arg.str) ;
 
int pos= string_index( joined_args , key ) ;
 
 if ( pos == - 1 ) {
 
return  def ;
 
 }
 ;
 
 pos  +=  key .len ;
 
int space= string_index_after( joined_args , tos2((byte*)" ") , pos ) ;
 
 if ( space == - 1 ) {
 
 space  =  joined_args .len ;
 
 }
 ;
 
string res= string_substr( joined_args , pos , space ) ;
 
return  res ;
 
 
 }
 string V_module_path(V* v, string mod) {
 
 if ( string_contains( mod , tos2((byte*)".") ) ) {
 
return  string_replace( mod , tos2((byte*)".") , tos2((byte*)"/") ) ;
 
 }
 ;
 
return  mod ;
 
 
 }
 void V_log(V* v, string s) {
 
 if ( ! v ->pref ->is_verbose ) {
 
 return ;
 
 }
 ;
 
 println ( s ) ;
 
 
 }
 V* new_v(array_string args) {
 
string dir=*(string*)  array_last( args ) ;
 
 if ( array_string_contains( args , tos2((byte*)"run") ) ) {
 
 dir  =  ( *(string*) array__get( args , 2) ) ;
 
 }
 ;
 
 if ( args .len < 2 ) {
 
 dir  =  tos2((byte*)"") ;
 
 }
 ;
 
string joined_args= array_string_join( args , tos2((byte*)" ") ) ;
 
string target_os= get_arg ( joined_args , tos2((byte*)"os") , tos2((byte*)"") ) ;
 
string out_name= get_arg ( joined_args , tos2((byte*)"o") , tos2((byte*)"a.out") ) ;
 
BuildMode build_mode= main__BuildMode_default_mode ;
 
string mod= tos2((byte*)"") ;
 
 if ( string_contains( joined_args , tos2((byte*)"build module ") ) ) {
 
 build_mode  =  main__BuildMode_build ;
 
 mod  =  os__dir ( dir ) ;
 
 mod  =  string_all_after( mod , tos2((byte*)"/") ) ;
 
printf( "Building module  \"%.*s\" dir=\"%.*s\"...\n", mod.len, mod.str, dir.len, dir.str ) ;
 
 out_name  = string_add( mod , tos2((byte*)".o") ) ;
 
 }
  else  if ( ! array_string_contains( args , tos2((byte*)"-embed_vlib") ) ) {
 
 build_mode  =  main__BuildMode_embed_vlib ;
 
 }
 ;
 
bool is_test= string_ends_with( dir , tos2((byte*)"_test.v") ) ;
 
bool is_script= string_ends_with( dir , tos2((byte*)".v") ) ;
 
 if ( is_script  &&  ! os__file_exists ( dir ) ) {
 
printf( "`%.*s` does not exist\n", dir.len, dir.str ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
 if (string_eq( out_name , tos2((byte*)"a.out") )  &&  string_ends_with( dir , tos2((byte*)".v") ) ) {
 
 out_name  =  string_left( dir , dir .len - 2 ) ;
 
 }
 ;
 
 if (string_eq( dir , tos2((byte*)".") )  && string_eq( out_name , tos2((byte*)"a.out") ) ) {
 
string base= string_all_after( os__getwd ( ) , tos2((byte*)"/") ) ;
 
 out_name  =  string_trim_space( base ) ;
 
 }
 ;
 
OS _os= main__OS_mac ;
 
 if (string_eq( target_os , tos2((byte*)"") ) ) {
 
 #ifdef __linux__
 
 _os  =  main__OS_linux ;
 
 #endif
 ;
 
 #ifdef __APPLE__
 
 _os  =  main__OS_mac ;
 
 #endif
 ;
 
 #ifdef _WIN32
 
 _os  =  main__OS_windows ;
 
 #endif
 ;
 
 #ifdef __FreeBSD__
 
 _os  =  main__OS_freebsd ;
 
 #endif
 ;
 
 #ifdef __OpenBSD__
 
 _os  =  main__OS_openbsd ;
 
 #endif
 ;
 
 #ifdef __NetBSD__
 
 _os  =  main__OS_netbsd ;
 
 #endif
 ;
 
 #ifdef __DragonFly__
 
 _os  =  main__OS_dragonfly ;
 
 #endif
 ;
 
 }
  else { 
 
 if ( string_eq( target_os,  tos2((byte*)"linux") )) { /* case */
 
 _os  =  main__OS_linux ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"windows") )) { /* case */
 
 _os  =  main__OS_windows ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"mac") )) { /* case */
 
 _os  =  main__OS_mac ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"freebsd") )) { /* case */
 
 _os  =  main__OS_freebsd ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"openbsd") )) { /* case */
 
 _os  =  main__OS_openbsd ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"netbsd") )) { /* case */
 
 _os  =  main__OS_netbsd ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"dragonfly") )) { /* case */
 
 _os  =  main__OS_dragonfly ;
 
 }
 else  if ( string_eq( target_os,  tos2((byte*)"msvc") )) { /* case */
 
 _os  =  main__OS_msvc ;
 
 }
 ;
 
 }
 ;
 
array_string builtins=new_array_from_c_array(7, 7, sizeof(string), (string[]) {  tos2((byte*)"array.v") ,  tos2((byte*)"string.v") ,  tos2((byte*)"builtin.v") ,  tos2((byte*)"int.v") ,  tos2((byte*)"utf8.v") ,  tos2((byte*)"map.v") ,  tos2((byte*)"option.v") ,   }) ;
 
string vroot= os__dir ( os__executable ( ) ) ;
 
 if ( os__dir_exists ( vroot )  &&  os__dir_exists (string_add( vroot , tos2((byte*)"/vlib/builtin") ) ) ) {
 
 }
  else { 
 
 println ( tos2((byte*)"vlib not found. It should be next to the V executable. ") ) ;
 
 println ( tos2((byte*)"Go to https://vlang.io to install V.") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
string out_name_c=string_add( string_all_after( out_name , tos2((byte*)"/") ) , tos2((byte*)".c") ) ;
 
array_string files=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 if ( ! string_contains( out_name , tos2((byte*)"builtin.o") ) ) {
 
 array_string tmp149 =  builtins;
 ;
for (int tmp150 = 0; tmp150 < tmp149 .len; tmp150 ++) {
 string builtin = ((string *) tmp149.data)[tmp150];
 
 
string f= _STR("%.*s/vlib/builtin/%.*s", vroot.len, vroot.str, builtin.len, builtin.str) ;
 
 if ( build_mode == main__BuildMode_default_mode  ||  build_mode == main__BuildMode_build ) {
 
 }
 ;
 
_PUSH(& files , ( f ), tmp152, string) ;
 
 }
 ;
 
 }
 ;
 
string cflags= tos2((byte*)"") ;
 
 array_string tmp154 =  args ;
 ;
for (int ci = 0; ci < tmp154 .len; ci ++) {
 string cv = ((string *) tmp154 . data)[ci];
 
 
 if (string_eq( cv , tos2((byte*)"-cflags") ) ) {
 
 cflags = string_add(cflags, string_add( ( *(string*) array__get( args , ci + 1) ) , tos2((byte*)" ") ) ) ;
 
 }
 ;
 
 }
 ;
 
bool obfuscate= array_string_contains( args , tos2((byte*)"-obf") ) ;
 
Preferences* pref= ALLOC_INIT(Preferences, { .is_test =  is_test , .is_script =  is_script , .is_so =  array_string_contains( args , tos2((byte*)"-shared") ) , .is_play =  array_string_contains( args , tos2((byte*)"play") ) , .is_prod =  array_string_contains( args , tos2((byte*)"-prod") ) , .is_verbose =  array_string_contains( args , tos2((byte*)"-verbose") ) , .is_debuggable =  array_string_contains( args , tos2((byte*)"-g") ) , .is_debug =  array_string_contains( args , tos2((byte*)"-debug") )  ||  array_string_contains( args , tos2((byte*)"-g") ) , .obfuscate =  obfuscate , .is_prof =  array_string_contains( args , tos2((byte*)"-prof") ) , .is_live =  array_string_contains( args , tos2((byte*)"-live") ) , .sanitize =  array_string_contains( args , tos2((byte*)"-sanitize") ) , .nofmt =  array_string_contains( args , tos2((byte*)"-nofmt") ) , .show_c_cmd =  array_string_contains( args , tos2((byte*)"-show_c_cmd") ) , .translated =  array_string_contains( args , tos2((byte*)"translated") ) , .is_run =  array_string_contains( args , tos2((byte*)"run") ) , .is_repl =  array_string_contains( args , tos2((byte*)"-repl") ) , .build_mode =  build_mode , .cflags =  cflags , .no_auto_free = 0 , } ) ;
 
 if ( pref ->is_so ) {
 
 out_name_c  = string_add( string_all_after( out_name , tos2((byte*)"/") ) , tos2((byte*)"_shared_lib.c") ) ;
 
 }
 ;
 
return  ALLOC_INIT(V, { .os =  _os , .out_name =  out_name , .files =  files , .dir =  dir , .lang_dir =  vroot , .table =  new_table ( obfuscate ) , .out_name =  out_name , .out_name_c =  out_name_c , .cgen =  new_cgen ( out_name_c ) , .vroot =  vroot , .pref =  pref , .mod =  mod , } ) ;
 
 
 }
 array_string run_repl() {
 
 println ( tos2((byte*)"REPL is temporarily disabled, sorry") ) ;
 
 v_exit ( 1 ) ;
 
printf( "V %.*s\n", main__Version.len, main__Version.str ) ;
 
 println ( tos2((byte*)"Use Ctrl-C or `exit` to exit") ) ;
 
string file= tos2((byte*)".vrepl.v") ;
 
string temp_file= tos2((byte*)".vrepl_temp.v") ;
 
 
array_string lines=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
string vexe= ( *(string*) array__get( os__args , 0) ) ;
 
 while (1) { 
 
 v_print ( tos2((byte*)">>> ") ) ;
 
string line= os__get_raw_line ( ) ;
 
 if (string_eq( string_trim_space( line ) , tos2((byte*)"") )  &&  string_ends_with( line , tos2((byte*)"\n") ) ) {
 
 continue
 ;
 
 }
 ;
 
 line  =  string_trim_space( line ) ;
 
 if (string_eq( line , tos2((byte*)"") )  || string_eq( line , tos2((byte*)"exit") ) ) {
 
 break
 ;
 
 }
 ;
 
 if ( string_starts_with( line , tos2((byte*)"print") ) ) {
 
string source_code=string_add(string_add( array_string_join( lines , tos2((byte*)"\n") ) , tos2((byte*)"\n") ) , line ) ;
 
 os__write_file ( file , source_code ) ;
 
string s= os__exec ( _STR("%.*s run %.*s -repl", vexe.len, vexe.str, file.len, file.str) ) ;
 
array_string vals= string_split( s , tos2((byte*)"\n") ) ;
 
 if ( string_contains( s , tos2((byte*)"panic: ") ) ) {
 
 if ( ! string_contains( s , tos2((byte*)"declared and not used") ) ) {
 
 for (
int i= 1  ;  i < vals .len  ;  i ++ ) { 
 
 
 println ( ( *(string*) array__get( vals , i) ) ) ;
 
 }
 ;
 
 }
  else { 
 
 println ( s ) ;
 
 }
 ;
 
 }
  else { 
 
 for (
int i= 0  ;  i < vals .len  ;  i ++ ) { 
 
 
 println ( ( *(string*) array__get( vals , i) ) ) ;
 
 }
 ;
 
 }
 ;
 
 }
  else { 
 
string temp_line= line ;
 
bool temp_flag= 0 ;
 
 if ( ! ( string_contains( line , tos2((byte*)" ") )  ||  string_contains( line , tos2((byte*)":") )  ||  string_contains( line , tos2((byte*)"=") )  ||  string_contains( line , tos2((byte*)",") ) ) ) {
 
 temp_line  =  _STR("println(%.*s)", line.len, line.str) ;
 
 temp_flag  =  1 ;
 
 }
 ;
 
string temp_source_code=string_add(string_add( array_string_join( lines , tos2((byte*)"\n") ) , tos2((byte*)"\n") ) , temp_line ) ;
 
 os__write_file ( temp_file , temp_source_code ) ;
 
string s= os__exec ( _STR("%.*s run %.*s -repl", vexe.len, vexe.str, temp_file.len, temp_file.str) ) ;
 
 if ( string_contains( s , tos2((byte*)"panic: ") ) ) {
 
 if ( ! string_contains( s , tos2((byte*)"declared and not used") ) ) {
 
array_string vals= string_split( s , tos2((byte*)"\n") ) ;
 
 for (
int i= 0  ;  i < vals .len  ;  i ++ ) { 
 
 
 println ( ( *(string*) array__get( vals , i) ) ) ;
 
 }
 ;
 
 }
  else { 
 
_PUSH(& lines , ( line ), tmp183, string) ;
 
 }
 ;
 
 }
  else { 
 
_PUSH(& lines , ( line ), tmp184, string) ;
 
array_string vals= string_split( s , tos2((byte*)"\n") ) ;
 
 for (
int i= 0  ;  i < vals .len - 1  ;  i ++ ) { 
 
 
 println ( ( *(string*) array__get( vals , i) ) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
array_string tmp189 =  lines;
  {
 
 os__rm ( file ) ;
 
 os__rm ( temp_file ) ;
 
 }
 return tmp189;
 ;
 
  {
 
 os__rm ( file ) ;
 
 os__rm ( temp_file ) ;
 
 }
 }
 array_string env_vflags_and_os_args() {
 
array_string args=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
string vflags= os__getenv ( tos2((byte*)"VFLAGS") ) ;
 
 if (string_ne( tos2((byte*)"") , vflags ) ) {
 
_PUSH(& args , ( ( *(string*) array__get( os__args , 0) ) ), tmp192, string) ;
 
_PUSH_MANY(& args , ( string_split( vflags , tos2((byte*)" ") ) ), tmp195, array_string) ;
 
 if ( os__args .len > 1 ) {
 
_PUSH_MANY(& args , ( array_right( os__args , 1 ) ), tmp196, array_string) ;
 
 }
 ;
 
 }
  else { 
 
_PUSH_MANY(& args , ( os__args ), tmp197, array_string) ;
 
 }
 ;
 
return  args ;
 
 
 }
 void update_v() {
 
 println ( tos2((byte*)"Updating V...") ) ;
 
string vroot= os__dir ( os__executable ( ) ) ;
 
string s= os__exec ( _STR("git -C \"%.*s\" pull --rebase origin master", vroot.len, vroot.str) ) ;
 
 println ( s ) ;
 
 #ifdef _WIN32
 
 os__mv ( _STR("%.*s/v.exe", vroot.len, vroot.str) , _STR("%.*s/v_old.exe", vroot.len, vroot.str) ) ;
 
 s  =  os__exec ( _STR("%.*s/make.bat", vroot.len, vroot.str) ) ;
 
 println ( s ) ;
 
 ;
 
 #else
 
 s  =  os__exec ( _STR("make -C \"%.*s\"", vroot.len, vroot.str) ) ;
 
 println ( s ) ;
 
 #endif
 ;
 
 
 }
 void DepSet_add(DepSet* dset, string item) {
 
_PUSH(& dset ->items , ( item ), tmp1, string) ;
 
 
 }
 DepSet DepSet_diff(DepSet* dset, DepSet otherset) {
 
DepSet diff= (DepSet) { .items = new_array(0, 1, sizeof(string)) } ;
 
 array_string tmp3 =  dset ->items;
 ;
for (int tmp4 = 0; tmp4 < tmp3 .len; tmp4 ++) {
 string item = ((string *) tmp3.data)[tmp4];
 
 
 if ( !_IN(string,  item ,  otherset .items ) ) {
 
_PUSH(& diff .items , ( item ), tmp5, string) ;
 
 }
 ;
 
 }
 ;
 
return  diff ;
 
 
 }
 int DepSet_size(DepSet* dset) {
 
return  dset ->items .len ;
 
 
 }
 ModDepGraph* new_mod_dep_graph() {
 
return  ALLOC_INIT(ModDepGraph, { .acyclic =  1 , .nodes = new_array(0, 1, sizeof(ModDepGraphNode)) } ) ;
 
 
 }
 void ModDepGraph_from_import_tables(ModDepGraph* graph, array_FileImportTable import_tables) {
 
 array_FileImportTable tmp6 =  import_tables;
 ;
for (int tmp7 = 0; tmp7 < tmp6 .len; tmp7 ++) {
 FileImportTable fit = ((FileImportTable *) tmp6.data)[tmp7];
 
 
array_string deps=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 map_string tmp9 =  fit .imports ;
 array_string keys_tmp9 = map_keys(& tmp9 ); 
 for (int l = 0; l < keys_tmp9 .len; l++) {
   string _ = ((string*)keys_tmp9 .data)[l];
 string m = {0}; map_get(tmp9, _, & m);
 
 
_PUSH(& deps , ( m ), tmp10, string) ;
 
 }
 ;
 
 ModDepGraph_add( graph , fit .module_name , deps ) ;
 
 }
 ;
 
 
 }
 void ModDepGraph_add(ModDepGraph* graph, string mod, array_string deps) {
 
_PUSH(& graph ->nodes , ( (ModDepGraphNode) { .name =  mod , .deps =  deps , .last_cycle = tos("", 0) } ), tmp11, ModDepGraphNode) ;
 
 
 }
 ModDepGraph* ModDepGraph_resolve(ModDepGraph* graph) {
 
map_ModDepGraphNode node_names= new_map(1, sizeof(ModDepGraphNode)) ;
 
map_DepSet node_deps= new_map(1, sizeof(DepSet)) ;
 
 array_ModDepGraphNode tmp14 =  graph ->nodes ;
 ;
for (int _ = 0; _ < tmp14 .len; _ ++) {
 ModDepGraphNode node = ((ModDepGraphNode *) tmp14 . data)[_];
 
  
 ModDepGraphNode tmp15 =  node; 

map__set(& node_names , node .name , & tmp15) ;
 
DepSet dep_set= (DepSet) { .items = new_array(0, 1, sizeof(string)) } ;
 
 array_string tmp17 =  node .deps ;
 ;
for (int _ = 0; _ < tmp17 .len; _ ++) {
 string dep = ((string *) tmp17 . data)[_];
 
 
 DepSet_add(& /* ? */ dep_set , dep ) ;
 
 }
 ;
  
 DepSet tmp18 =  dep_set; 

map__set(& node_deps , node .name , & tmp18) ;
 
 }
 ;
 
ModDepGraph* resolved= new_mod_dep_graph ( ) ;
 
 while ( node_deps .size != 0 ) {
 
 
DepSet ready_set= (DepSet) { .items = new_array(0, 1, sizeof(string)) } ;
 
 map_DepSet tmp21 =  node_deps ;
 array_string keys_tmp21 = map_keys(& tmp21 ); 
 for (int l = 0; l < keys_tmp21 .len; l++) {
   string name = ((string*)keys_tmp21 .data)[l];
 DepSet deps = {0}; map_get(tmp21, name, & deps);
 
 
 if ( DepSet_size(& /* ? */ deps ) == 0 ) {
 
 DepSet_add(& /* ? */ ready_set , name ) ;
 
 }
 ;
 
 }
 ;
 
 if ( DepSet_size(& /* ? */ ready_set ) == 0 ) {
 
ModDepGraph* g= new_mod_dep_graph ( ) ;
 
 g ->acyclic  =  0 ;
 
array_string ndk= map_keys(& /* ? */ node_deps ) ;
 
 map_DepSet tmp24 =  node_deps ;
 array_string keys_tmp24 = map_keys(& tmp24 ); 
 for (int l = 0; l < keys_tmp24 .len; l++) {
   string name = ((string*)keys_tmp24 .data)[l];
 DepSet _ = {0}; map_get(tmp24, name, & _);
 
  
 ModDepGraphNode tmp25 = {0}; bool tmp26 = map_get( node_names , name, & tmp25); 

ModDepGraphNode node= tmp25 ;
 
 if (string_eq( name , ( *(string*) array__get( ndk , node_deps .size - 1) ) ) ) {
  
 DepSet tmp30 = {0}; bool tmp31 = map_get( node_deps , name, & tmp30); 
 
 DepSet tmp32 = {0}; bool tmp33 = map_get( node_deps , name, & tmp32); 

 node .last_cycle  =  ( *(string*) array__get( tmp30 .items , tmp32 .items .len - 1) ) ;
 
 }
 ;
 
_PUSH(& g ->nodes , ( node ), tmp36, ModDepGraphNode) ;
 
 }
 ;
 
return  g ;
 
 }
 ;
 
 array_string tmp37 =  ready_set .items;
 ;
for (int tmp38 = 0; tmp38 < tmp37 .len; tmp38 ++) {
 string name = ((string *) tmp37.data)[tmp38];
 
 
 map_delete(& /* ? */ node_deps , name ) ;
  
 ModDepGraphNode tmp40 = {0}; bool tmp41 = map_get( node_names , name, & tmp40); 

_PUSH(& resolved ->nodes , ( tmp40 ), tmp39, ModDepGraphNode) ;
 
 }
 ;
 
 map_DepSet tmp42 =  node_deps ;
 array_string keys_tmp42 = map_keys(& tmp42 ); 
 for (int l = 0; l < keys_tmp42 .len; l++) {
   string name = ((string*)keys_tmp42 .data)[l];
 DepSet deps = {0}; map_get(tmp42, name, & deps);
 
  
 DepSet tmp43 =  DepSet_diff(& /* ? */ deps , ready_set ); 

map__set(& node_deps , name , & tmp43) ;
 
 }
 ;
 
 }
 ;
 
return  resolved ;
 
 
 }
 array_string ModDepGraph_imports(ModDepGraph* graph) {
 
array_string mods=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 array_ModDepGraphNode tmp45 =  graph ->nodes;
 ;
for (int tmp46 = 0; tmp46 < tmp45 .len; tmp46 ++) {
 ModDepGraphNode node = ((ModDepGraphNode *) tmp45.data)[tmp46];
 
 
 if (string_eq( node .name , tos2((byte*)"main") ) ) {
 
 continue
 ;
 
 }
 ;
 
_PUSH(& mods , ( node .name ), tmp47, string) ;
 
 }
 ;
 
return  mods ;
 
 
 }
 ModDepGraphNode ModDepGraph_last_node(ModDepGraph* graph) {
 
return  ( *(ModDepGraphNode*) array__get( graph ->nodes , graph ->nodes .len - 1) ) ;
 
 
 }
 string ModDepGraph_last_cycle(ModDepGraph* graph) {
 
return  ModDepGraph_last_node(& /* ? */* graph ) .last_cycle ;
 
 
 }
 void ModDepGraph_display(ModDepGraph* graph) {
 
 for (
int i= 0  ;  i < graph ->nodes .len  ;  i ++ ) { 
 
 
ModDepGraphNode node= ( *(ModDepGraphNode*) array__get( graph ->nodes , i) ) ;
 
 array_string tmp54 =  node .deps;
 ;
for (int tmp55 = 0; tmp55 < tmp54 .len; tmp55 ++) {
 string dep = ((string *) tmp54.data)[tmp55];
 
 
string out= _STR(" * %.*s -> %.*s", node .name.len, node .name.str, dep.len, dep.str) ;
 
 if ( ! graph ->acyclic  &&  i == graph ->nodes .len - 1  && string_eq( dep , node .last_cycle ) ) {
 
 out = string_add(out,  tos2((byte*)" <-- last cycle") ) ;
 
 }
 ;
 
 println ( out ) ;
 
 }
 ;
 
 }
 ;
 
 
 }
 string V_find_module_path(V* v, string mod) {
 
string mod_path= V_module_path(& /* ? */* v , mod ) ;
 
string import_path=string_add( os__getwd ( ) , _STR("/%.*s", mod_path.len, mod_path.str) ) ;
 
 if ( ! os__dir_exists ( import_path ) ) {
 
 import_path  =  _STR("%.*s/vlib/%.*s", v ->lang_dir.len, v ->lang_dir.str, mod_path.len, mod_path.str) ;
 
 }
 ;
 
 if ( ! os__dir_exists ( import_path ) ) {
 
 import_path  =  _STR("%.*s/%.*s", main__ModPath.len, main__ModPath.str, mod_path.len, mod_path.str) ;
 
 if ( ! os__dir_exists ( import_path ) ) {
 
 v_panic ( _STR("module \"%.*s\" not found", mod.len, mod.str) ) ;
 
 }
 ;
 
 }
 ;
 
return  import_path ;
 
 
 }
 void cc_msvc(V* v) {
 
 
 }
 void build_thirdparty_obj_file_with_msvc(string flag) {
 
 
 }
 string platform_postfix_to_ifdefguard(string name) {
 
 if ( string_eq( name,  tos2((byte*)".v") )) { /* case */
 
return  tos2((byte*)"") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"_win.v") )) { /* case */
 
return  tos2((byte*)"#ifdef _WIN32") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"_nix.v") )) { /* case */
 
return  tos2((byte*)"#ifndef _WIN32") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"_lin.v") )) { /* case */
 
return  tos2((byte*)"#ifdef __linux__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"_mac.v") )) { /* case */
 
return  tos2((byte*)"#ifdef __APPLE__") ;
 
 }
 ;
 
 v_panic ( _STR("bad platform_postfix \"%.*s\"", name.len, name.str) ) ;
 
return  tos2((byte*)"") ;
 
 
 }
 Parser V_new_parser(V* v, string path, Pass pass) {
 
 V_log(& /* ? */* v , _STR("new_parser(\"%.*s\")", path.len, path.str) ) ;
 
 v ->cgen ->pass  =  pass ;
 
string path_pcguard= tos2((byte*)"") ;
 
string path_platform= tos2((byte*)".v") ;
 
 array_string tmp3 = new_array_from_c_array(4, 4, sizeof(string), (string[]) {  tos2((byte*)"_lin.v") ,  tos2((byte*)"_mac.v") ,  tos2((byte*)"_win.v") ,  tos2((byte*)"_nix.v")  });
 ;
for (int tmp4 = 0; tmp4 < tmp3 .len; tmp4 ++) {
 string path_ending = ((string *) tmp3.data)[tmp4];
 
 
 if ( string_ends_with( path , path_ending ) ) {
 
 path_platform  =  path_ending ;
 
 path_pcguard  =  platform_postfix_to_ifdefguard ( path_ending ) ;
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
Parser p= (Parser) { .v =  v , .file_path =  path , .file_name =  string_all_after( path , tos2((byte*)"/") ) , .file_platform =  path_platform , .file_pcguard =  path_pcguard , .scanner =  new_scanner ( path ) , .table =  v ->table , .import_table =  new_file_import_table ( path ) , .cur_fn =  main__EmptyFn , .cgen =  v ->cgen , .is_script =  ( v ->pref ->is_script  && string_eq( path , v ->dir ) ) , .pref =  v ->pref , .os =  v ->os , .pass =  pass , .vroot =  v ->vroot , .building_v =  ! v ->pref ->is_repl  &&  ( string_contains( path , tos2((byte*)"compiler/") )  ||  string_contains( path , tos2((byte*)"v/vlib") ) ) , .token_idx = 0 , .lit = tos("", 0) , .mod = tos("", 0) , .inside_const = 0 , .assigned_type = tos("", 0) , .expected_type = tos("", 0) , .tmp_cnt = 0 , .builtin_mod = 0 , .vh_lines = new_array(0, 1, sizeof(string)) , .inside_if_expr = 0 , .is_struct_init = 0 , .if_expr_cnt = 0 , .for_expr_cnt = 0 , .ptr_cast = 0 , .calling_c = 0 , .returns = 0 , .is_c_struct_init = 0 , .can_chash = 0 , .attr = tos("", 0) , .v_script = 0 , .var_decl_name = tos("", 0) , .is_alloc = 0 , .cur_gen_type = tos("", 0) , .is_vweb = 0 } ;
 
 v ->cgen ->line_directives  =  v ->pref ->is_debuggable ;
 
 v ->cgen ->file  =  path ;
 
 Parser_next(& /* ? */ p ) ;
 
return  p ;
 
 
 }
 void Parser_next(Parser* p) {
 
 p ->prev_tok2  =  p ->prev_tok ;
 
 p ->prev_tok  =  p ->tok ;
 
 p ->scanner ->prev_tok  =  p ->tok ;
 
ScanRes res= Scanner_scan( p ->scanner ) ;
 
 p ->tok  =  res .tok ;
 
 p ->lit  =  res .lit ;
 
 
 }
 void Parser_log(Parser* p, string s) {
 
 
 }
 void Parser_parse(Parser* p) {
 
 Parser_log(& /* ? */* p , _STR("\nparse() run=%d file=%.*s tok=%.*s", p ->pass, p ->file_name.len, p ->file_name.str, Parser_strtok(& /* ? */* p ).len, Parser_strtok(& /* ? */* p ).str) ) ;
 
 if ( p ->is_script  ||  p ->pref ->is_test ) {
 
 p ->mod  =  tos2((byte*)"main") ;
 
 if ( p ->tok == main__Token_key_module ) {
 
 Parser_next( p ) ;
 
 Parser_fgen( p , tos2((byte*)"module ") ) ;
 
 p ->mod  =  Parser_check_name( p ) ;
 
 }
 ;
 
 }
  else { 
 
 Parser_check( p , main__Token_key_module ) ;
 
 Parser_fspace( p ) ;
 
 p ->mod  =  Parser_check_name( p ) ;
 
 }
 ;
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 p ->builtin_mod  = string_eq( p ->mod , tos2((byte*)"builtin") ) ;
 
 p ->can_chash  = string_eq( p ->mod , tos2((byte*)"ft") )  || string_eq( p ->mod , tos2((byte*)"glfw") )  || string_eq( p ->mod , tos2((byte*)"glfw2") )  || string_eq( p ->mod , tos2((byte*)"ui") ) ;
 
string fq_mod= Table_qualify_module(& /* ? */* p ->table , p ->mod , p ->file_path ) ;
 
 p ->import_table ->module_name  =  fq_mod ;
 
 Table_register_module( p ->table , fq_mod ) ;
 
 p ->mod  =  string_replace( fq_mod , tos2((byte*)".") , tos2((byte*)"_dot_") ) ;
 
 if ( p ->pass == main__Pass_imports ) {
 
 while ( p ->tok == main__Token_key_import  &&  Parser_peek( p ) != main__Token_key_const ) {
 
 
 Parser_imports( p ) ;
 
 }
 ;
 
 if ( array_string_contains( p ->table ->imports , tos2((byte*)"builtin") ) ) {
 
 Parser_error( p , tos2((byte*)"module `builtin` cannot be imported") ) ;
 
 }
 ;
 
_PUSH(& p ->table ->file_imports , ( * p ->import_table ), tmp8, FileImportTable) ;
 
 return ;
 
 }
 ;
 
 while (1) { 
 
 if ( ( p ->tok ==  main__Token_key_import )) { /* case */
 
 if ( Parser_peek( p ) == main__Token_key_const ) {
 
 Parser_const_decl( p ) ;
 
 }
  else { 
 
 Parser_imports( p ) ;
 
 if ( p ->tok != main__Token_key_import ) {
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_enum )) { /* case */
 
 Parser_next( p ) ;
 
 if ( p ->tok == main__Token_name ) {
 
 Parser_fgen( p , tos2((byte*)"enum ") ) ;
 
string name= Parser_check_name( p ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_enum_decl( p , name ) ;
 
 }
  else  if ( p ->pref ->translated ) {
 
 Parser_enum_decl( p , tos2((byte*)"int") ) ;
 
 }
  else { 
 
 Parser_check( p , main__Token_name ) ;
 
 }
 ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_pub )) { /* case */
 
 if ( Parser_peek( p ) == main__Token_func ) {
 
 Parser_fn_decl( p ) ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_key_struct ) {
 
 Parser_error( p , tos2((byte*)"structs can\'t be declared public *yet*") ) ;
 
 }
  else { 
 
 Parser_error( p , tos2((byte*)"wrong pub keyword usage") ) ;
 
 }
 ;
 
 }
 else  if ( ( p ->tok ==  main__Token_func )) { /* case */
 
 Parser_fn_decl( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_type )) { /* case */
 
 Parser_type_decl( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_lsbr )) { /* case */
 
 Parser_attribute( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_struct ) ||   ( p ->tok ==  main__Token_key_interface ) ||   ( p ->tok ==  main__Token_key_union ) ||   ( p ->tok ==  main__Token_lsbr )) { /* case */
 
 Parser_struct_decl( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_const )) { /* case */
 
 Parser_const_decl( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_hash )) { /* case */
 
 Parser_chash( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_dollar )) { /* case */
 
 Parser_comp_time( p ) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_key_global )) { /* case */
 
 if ( ! p ->pref ->translated  &&  ! p ->pref ->is_live  &&  ! p ->builtin_mod  &&  ! p ->building_v ) {
 
 Parser_error( p , tos2((byte*)"__global is only allowed in translated code") ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
string name= Parser_check_name( p ) ;
 
string typ= Parser_get_type( p ) ;
 
 Parser_register_global( p , name , typ ) ;
 
string g= Table_cgen_name_type_pair(& /* ? */* p ->table , name , typ ) ;
 
 if ( p ->tok == main__Token_assign ) {
 
 Parser_next( p ) ;
 
 g = string_add(g,  tos2((byte*)" = ") ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
 Parser_bool_expression( p ) ;
 
 g = string_add(g,  CGen_end_tmp( p ->cgen ) ) ;
 
 }
 ;
 
 g = string_add(g,  tos2((byte*)"; // global") ) ;
 
_PUSH(& p ->cgen ->consts , ( g ), tmp13, string) ;
 
 }
 else  if ( ( p ->tok ==  main__Token_eof )) { /* case */
 
 Parser_log(& /* ? */* p , tos2((byte*)"end of parse()") ) ;
 
 if ( p ->is_script  &&  ! p ->pref ->is_test ) {
 
 p ->cur_fn  =  main__MainFn ;
 
 Parser_check_unused_variables( p ) ;
 
 }
 ;
 
 if ( 0  &&  ! Parser_first_pass(& /* ? */* p )  &&  Parser_fileis(& /* ? */* p , tos2((byte*)"main.v") ) ) {
 
Option_os__File tmp14 =  os__create ( tos2((byte*)"/var/tmp/fmt.v") ) ;
 if (!tmp14 .ok) {
 string err = tmp14 . error;
 
 v_panic ( tos2((byte*)"failed to create fmt.v") ) ;
 
 return ;
 
 }
 os__File out = *(os__File*) tmp14 . data;
 ;
 
 os__File_writeln( out , strings__Builder_str( p ->scanner ->fmt_out ) ) ;
 
 os__File_close( out ) ;
 
 }
 ;
 
 return ;
 
 }
 else  { // default:
 
 if ( p ->is_script  &&  ! p ->pref ->is_test ) {
 
 if ( Parser_first_pass(& /* ? */* p ) ) {
 
 if (string_eq( p ->cur_fn ->name , tos2((byte*)"") ) ) {
 
 p ->cur_fn  =  main__MainFn ;
 
 }
 ;
 
 return ;
 
 }
 ;
 
 if (string_eq( p ->cur_fn ->name , tos2((byte*)"") ) ) {
 
 p ->cur_fn  =  main__MainFn ;
 
 if ( p ->pref ->is_repl ) {
 
 Fn_clear_vars( p ->cur_fn ) ;
 
 }
 ;
 
 }
 ;
 
int start= p ->cgen ->lines .len ;
 
 Parser_statement( p , 1 ) ;
 
 if (string_ne( ( *(string*) array__get( p ->cgen ->lines , start - 1) ) , tos2((byte*)"") )  && string_ne( p ->cgen ->fn_main , tos2((byte*)"") ) ) {
 
 start -- ;
 
 }
 ;
 
 Parser_genln( p , tos2((byte*)"") ) ;
 
int end= p ->cgen ->lines .len ;
 
array_string lines= array_slice( p ->cgen ->lines , start , end ) ;
 
 p ->cgen ->fn_main  = string_add( p ->cgen ->fn_main , array_string_join( lines , tos2((byte*)"\n") ) ) ;
 
 CGen_resetln( p ->cgen , tos2((byte*)"") ) ;
 
 for (
int i= start  ;  i < end  ;  i ++ ) { 
 
  
 string tmp21 =  tos2((byte*)""); 

array_set(&/*q*/ p ->cgen ->lines , i , & tmp21) ;
 
 }
 ;
 
 }
  else { 
 
 Parser_error( p , _STR("unexpected token `%.*s`", Parser_strtok(& /* ? */* p ).len, Parser_strtok(& /* ? */* p ).str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void Parser_imports(Parser* p) {
 
 Parser_check( p , main__Token_key_import ) ;
 
 if ( p ->tok == main__Token_lpar ) {
 
 Parser_check( p , main__Token_lpar ) ;
 
 while ( p ->tok != main__Token_rpar  &&  p ->tok != main__Token_eof ) {
 
 
 Parser_import_statement( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 return ;
 
 }
 ;
 
 Parser_import_statement( p ) ;
 
 
 }
 void Parser_import_statement(Parser* p) {
 
 if ( p ->tok != main__Token_name ) {
 
 Parser_error( p , tos2((byte*)"bad import format") ) ;
 
 }
 ;
 
 if ( Parser_peek( p ) == main__Token_number  &&  string_at( p ->scanner ->text , p ->scanner ->pos + 1) == '.' ) {
 
 Parser_error( p , tos2((byte*)"bad import format. module/submodule names cannot begin with a number.") ) ;
 
 }
 ;
 
string mod= string_trim_space( Parser_check_name( p ) ) ;
 
string mod_alias= mod ;
 
int depth= 1 ;
 
 while ( p ->tok == main__Token_dot ) {
 
 
 Parser_check( p , main__Token_dot ) ;
 
string submodule= Parser_check_name( p ) ;
 
 mod_alias  =  submodule ;
 
 mod = string_add(mod, string_add( tos2((byte*)".") , submodule ) ) ;
 
 depth ++ ;
 
 if ( depth > main__MaxModuleDepth ) {
 
 Parser_error( p , _STR("module depth of %d exceeded: %.*s", main__MaxModuleDepth, mod.len, mod.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_as  &&  Parser_peek( p ) == main__Token_name ) {
 
 Parser_check( p , main__Token_key_as ) ;
 
 mod_alias  =  Parser_check_name( p ) ;
 
 }
 ;
 
 FileImportTable_register_alias( p ->import_table , mod_alias , mod ) ;
 
 if ( array_string_contains( p ->table ->imports , mod ) ) {
 
 return ;
 
 }
 ;
 
 Parser_log(& /* ? */* p , _STR("adding import %.*s", mod.len, mod.str) ) ;
 
_PUSH(& p ->table ->imports , ( mod ), tmp28, string) ;
 
 Table_register_module( p ->table , mod ) ;
 
 Parser_fgenln( p ,string_add( tos2((byte*)" ") , mod ) ) ;
 
 
 }
 void Parser_const_decl(Parser* p) {
 
bool is_import= p ->tok == main__Token_key_import ;
 
 p ->inside_const  =  1 ;
 
 if ( is_import ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_key_const ) ;
 
 Parser_fspace( p ) ;
 
 Parser_check( p , main__Token_lpar ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 Parser_fmt_inc( p ) ;
 
 while ( p ->tok == main__Token_name ) {
 
 
string name= Parser_check_name( p ) ;
 
 if ( ! is_import ) {
 
 name  =  Parser_prepend_mod(& /* ? */* p , name ) ;
 
 }
 ;
 
string typ= tos2((byte*)"int") ;
 
 if ( ! is_import ) {
 
 Parser_check_space( p , main__Token_assign ) ;
 
 typ  =  Parser_expression( p ) ;
 
 }
 ;
 
 if ( Parser_first_pass(& /* ? */* p )  &&  ! is_import  &&  Table_known_const(& /* ? */* p ->table , name ) ) {
 
 Parser_error( p , _STR("redefinition of `%.*s`", name.len, name.str) ) ;
 
 }
 ;
 
 Table_register_const( p ->table , name , typ , p ->mod , is_import ) ;
 
 if ( p ->pass == main__Pass_main  &&  ! is_import ) {
 
 if ( is_compile_time_const ( p ->cgen ->cur_line ) ) {
 
_PUSH(& p ->cgen ->consts , ( _STR("#define %.*s %.*s", name.len, name.str, p ->cgen ->cur_line.len, p ->cgen ->cur_line.str) ), tmp32, string) ;
 
 CGen_resetln( p ->cgen , tos2((byte*)"") ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 continue
 ;
 
 }
 ;
 
 if ( string_starts_with( typ , tos2((byte*)"[") ) ) {
 
_PUSH(& p ->cgen ->consts , (string_add( Table_cgen_name_type_pair(& /* ? */* p ->table , name , typ ) , _STR(" = %.*s;", p ->cgen ->cur_line.len, p ->cgen ->cur_line.str) ) ), tmp33, string) ;
 
 }
  else { 
 
_PUSH(& p ->cgen ->consts , (string_add( Table_cgen_name_type_pair(& /* ? */* p ->table , name , typ ) , tos2((byte*)";") ) ), tmp34, string) ;
 
_PUSH(& p ->cgen ->consts_init , ( _STR("%.*s = %.*s;", name.len, name.str, p ->cgen ->cur_line.len, p ->cgen ->cur_line.str) ), tmp35, string) ;
 
 }
 ;
 
 CGen_resetln( p ->cgen , tos2((byte*)"") ) ;
 
 }
 ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 Parser_fmt_dec( p ) ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 p ->inside_const  =  0 ;
 
 
 }
 void Parser_type_decl(Parser* p) {
 
 Parser_check( p , main__Token_key_type ) ;
 
string name= Parser_check_name( p ) ;
 
string parent= Parser_get_type( p ) ;
 
string nt_pair= Table_cgen_name_type_pair(& /* ? */* p ->table , name , parent ) ;
 
string _struct= ( ! string_contains( parent , tos2((byte*)"[") )  &&  ! string_starts_with( parent , tos2((byte*)"fn ") )  &&  ! Table_known_type(& /* ? */* p ->table , parent ) ) ? ( tos2((byte*)"struct") ) : ( tos2((byte*)"") ) ;
 
 Parser_gen_typedef( p , _STR("typedef %.*s %.*s; // type alias name=\"%.*s\" parent=\"%.*s\"", _struct.len, _struct.str, nt_pair.len, nt_pair.str, name.len, name.str, parent.len, parent.str) ) ;
 
 Parser_register_type_with_parent( p , name , parent ) ;
 
 
 }
 Fn* Parser_interface_method(Parser* p, string field_name, string receiver) {
 
Fn* method= ALLOC_INIT(Fn, { .name =  field_name , .is_interface =  1 , .is_method =  1 , .receiver_typ =  receiver , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .is_public = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ) ;
 
 Parser_log(& /* ? */* p , _STR("is interface. field=%.*s run=%d", field_name.len, field_name.str, p ->pass) ) ;
 
 Parser_fn_args( p , method ) ;
 
 if ( Scanner_has_gone_over_line_end(* p ->scanner ) ) {
 
 method ->typ  =  tos2((byte*)"void") ;
 
 }
  else { 
 
 method ->typ  =  Parser_get_type( p ) ;
 
 Parser_fspace( p ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
return  method ;
 
 
 }
 void Parser_struct_decl(Parser* p) {
 
string objc_parent= tos2((byte*)"") ;
 
bool is_objc= 0 ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 Parser_check( p , main__Token_lsbr ) ;
 
 is_objc  =  p ->tok == main__Token_key_interface ;
 
 Parser_next( p ) ;
 
 if ( is_objc ) {
 
 Parser_check( p , main__Token_colon ) ;
 
 objc_parent  =  Parser_check_name( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 }
 ;
 
bool is_interface= p ->tok == main__Token_key_interface ;
 
bool is_union= p ->tok == main__Token_key_union ;
 
bool is_struct= p ->tok == main__Token_key_struct ;
 
 Parser_fgen( p ,string_add( Token_str( p ->tok ) , tos2((byte*)" ") ) ) ;
 
 Parser_next( p ) ;
 
string name= Parser_check_name( p ) ;
 
 if ( string_contains( name , tos2((byte*)"_") )  &&  ! p ->pref ->translated ) {
 
 Parser_error( p , tos2((byte*)"type names cannot contain `_`") ) ;
 
 }
 ;
 
 if ( is_interface  &&  ! string_ends_with( name , tos2((byte*)"er") ) ) {
 
 Parser_error( p , tos2((byte*)"interface names temporarily have to end with `er` (e.g. `Speaker`, `Reader`)") ) ;
 
 }
 ;
 
bool is_c=string_eq( name , tos2((byte*)"C") )  &&  p ->tok == main__Token_dot ;
 
 if ( is_c ) {
 
 Parser_check( p , main__Token_dot ) ;
 
 name  =  Parser_check_name( p ) ;
 
 }
 ;
 
 if ( ! is_c  &&  ! good_type_name ( name ) ) {
 
 Parser_error( p , tos2((byte*)"bad struct name, e.g. use `HttpRequest` instead of `HTTPRequest`") ) ;
 
 }
 ;
 
 if ( ! is_c  &&  ! p ->builtin_mod  && string_ne( p ->mod , tos2((byte*)"main") ) ) {
 
 name  =  Parser_prepend_mod(& /* ? */* p , name ) ;
 
 }
 ;
 
 if ( p ->pass == main__Pass_decl  &&  Table_known_type(& /* ? */* p ->table , name ) ) {
 
 Parser_error( p , _STR("`%.*s` redeclared", name.len, name.str) ) ;
 
 }
 ;
 
 if ( is_objc ) {
 
 Parser_gen_type( p , _STR("@interface %.*s : %.*s { @public", name.len, name.str, objc_parent.len, objc_parent.str) ) ;
 
 }
  else { 
 
 if ( ! is_c ) {
 
string kind= ( is_union ) ? ( tos2((byte*)"union") ) : ( tos2((byte*)"struct") ) ;
 
 Parser_gen_typedef( p , _STR("typedef %.*s %.*s %.*s;", kind.len, kind.str, name.len, name.str, name.len, name.str) ) ;
 
 Parser_gen_type( p , _STR("%.*s %.*s {", kind.len, kind.str, name.len, name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( ! is_c  &&  p ->tok == main__Token_key_struct ) {
 
 Parser_error( p , _STR("use `struct %.*s {` instead of `type %.*s struct {`", name.len, name.str, name.len, name.str) ) ;
 
 }
 ;
 
Type* typ= Table_find_type(& /* ? */* p ->table , name ) ;
 
bool is_ph= 0 ;
 
 if ( typ ->is_placeholder ) {
 
 is_ph  =  1 ;
 
 typ ->name  =  name ;
 
 typ ->mod  =  p ->mod ;
 
 typ ->is_c  =  is_c ;
 
 typ ->is_placeholder  =  0 ;
 
 }
  else { 
 
 typ  =  ALLOC_INIT(Type, { .name =  name , .mod =  p ->mod , .is_c =  is_c , .is_interface =  is_interface , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .parent = tos("", 0) , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ) ;
 
 }
 ;
 
 if ( is_c  &&  is_struct  &&  p ->tok != main__Token_lcbr ) {
 
 Table_register_type2( p ->table ,* typ ) ;
 
 return ;
 
 }
 ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
bool is_pub= 0 ;
 
bool is_mut= 0 ;
 
array_string names=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
bool did_gen_something= 0 ;
 
 while ( p ->tok != main__Token_rcbr ) {
 
 
 if ( p ->tok == main__Token_key_pub ) {
 
 if ( is_pub ) {
 
 Parser_error( p , tos2((byte*)"structs can only have one `pub:`, all public fields have to be grouped") ) ;
 
 }
 ;
 
 is_pub  =  1 ;
 
 Parser_fmt_dec( p ) ;
 
 Parser_check( p , main__Token_key_pub ) ;
 
 if ( p ->tok != main__Token_key_mut ) {
 
 Parser_check( p , main__Token_colon ) ;
 
 }
 ;
 
 Parser_fmt_inc( p ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_mut ) {
 
 if ( is_mut ) {
 
 Parser_error( p , tos2((byte*)"structs can only have one `mut:`, all private key_mut fields have to be grouped") ) ;
 
 }
 ;
 
 is_mut  =  1 ;
 
 Parser_fmt_dec( p ) ;
 
 Parser_check( p , main__Token_key_mut ) ;
 
 if ( p ->tok != main__Token_key_mut ) {
 
 Parser_check( p , main__Token_colon ) ;
 
 }
 ;
 
 Parser_fmt_inc( p ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
string field_name= Parser_check_name( p ) ;
 
 if (_IN(string,  field_name ,  names ) ) {
 
 Parser_error( p , _STR("duplicate field `%.*s`", field_name.len, field_name.str) ) ;
 
 }
 ;
 
 if ( ! is_c  && string_ne( p ->mod , tos2((byte*)"os") )  &&  contains_capital ( field_name ) ) {
 
 Parser_error( p , tos2((byte*)"struct fields cannot contain uppercase letters, use snake_case instead") ) ;
 
 }
 ;
 
_PUSH(& names , ( field_name ), tmp56, string) ;
 
 if ( is_interface ) {
 
 Type_add_method( typ ,* Parser_interface_method( p , field_name , name ) ) ;
 
 continue
 ;
 
 }
 ;
 
AccessMod access_mod= ( is_pub ) ? ( main__AccessMod_public ) : ( main__AccessMod_private ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
string field_type= Parser_get_type( p ) ;
 
bool is_atomic= p ->tok == main__Token_key_atomic ;
 
 if ( is_atomic ) {
 
 Parser_next( p ) ;
 
 Parser_gen_type( p , tos2((byte*)"_Atomic ") ) ;
 
 }
 ;
 
 if ( ! is_c ) {
 
 Parser_gen_type( p ,string_add( Table_cgen_name_type_pair(& /* ? */* p ->table , field_name , field_type ) , tos2((byte*)";") ) ) ;
 
 }
 ;
 
string attr= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 Parser_next( p ) ;
 
 attr  =  Parser_check_name( p ) ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 }
 ;
 
 did_gen_something  =  1 ;
 
 Type_add_field( typ , field_name , field_type , is_mut , attr , access_mod ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( ! is_ph  &&  Parser_first_pass(& /* ? */* p ) ) {
 
 Table_register_type2( p ->table ,* typ ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
 if ( ! is_c ) {
 
 if ( ! did_gen_something ) {
 
 Parser_gen_type( p , tos2((byte*)"EMPTY_STRUCT_DECLARATION };") ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
  else { 
 
 Parser_gen_type( p , tos2((byte*)"}; ") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_objc ) {
 
 Parser_gen_type( p , tos2((byte*)"@end") ) ;
 
 }
 ;
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 
 }
 void Parser_enum_decl(Parser* p, string _enum_name) {
 
string enum_name= _enum_name ;
 
 if ( ! p ->builtin_mod  && string_ne( p ->mod , tos2((byte*)"main") ) ) {
 
 enum_name  =  Parser_prepend_mod(& /* ? */* p , enum_name ) ;
 
 }
 ;
 
 if (string_ne( enum_name , tos2((byte*)"int") ) ) {
 
_PUSH(& p ->cgen ->typedefs , ( _STR("typedef int %.*s;", enum_name.len, enum_name.str) ), tmp62, string) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
int val= 0 ;
 
array_string fields=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 while ( p ->tok == main__Token_name ) {
 
 
string field= Parser_check_name( p ) ;
 
_PUSH(& fields , ( field ), tmp66, string) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
string name= _STR("%.*s__%.*s_%.*s", p ->mod.len, p ->mod.str, enum_name.len, enum_name.str, field.len, field.str) ;
 
 if ( p ->pass == main__Pass_main ) {
 
_PUSH(& p ->cgen ->consts , ( _STR("#define %.*s %d", name.len, name.str, val) ), tmp68, string) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 Table_register_const( p ->table , name , enum_name , p ->mod , 0 ) ;
 
 val ++ ;
 
 }
 ;
 
 Table_register_type2( p ->table ,* ALLOC_INIT(Type, { .name =  enum_name , .mod =  p ->mod , .parent =  tos2((byte*)"int") , .is_enum =  1 , .enum_vals =  fields , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .is_c = 0 , .is_interface = 0 , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ) ) ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
 Parser_fgenln( p , tos2((byte*)"\n") ) ;
 
 
 }
 string Parser_check_name(Parser* p) {
 
string name= p ->lit ;
 
 Parser_check( p , main__Token_name ) ;
 
return  name ;
 
 
 }
 string Parser_check_string(Parser* p) {
 
string s= p ->lit ;
 
 Parser_check( p , main__Token_str ) ;
 
return  s ;
 
 
 }
 string Parser_strtok(Parser* p) {
 
 if ( p ->tok == main__Token_name ) {
 
return  p ->lit ;
 
 }
 ;
 
 if ( p ->tok == main__Token_str ) {
 
return  _STR("\"%.*s\"", p ->lit.len, p ->lit.str) ;
 
 }
 ;
 
string res= Token_str( p ->tok ) ;
 
 if (string_eq( res , tos2((byte*)"") ) ) {
 
int n= ((int)( p ->tok ) ) ;
 
return  int_str( n ) ;
 
 }
 ;
 
return  res ;
 
 
 }
 void Parser_check_space(Parser* p, Token expected) {
 
 Parser_fspace( p ) ;
 
 Parser_check( p , expected ) ;
 
 Parser_fspace( p ) ;
 
 
 }
 void Parser_check(Parser* p, Token expected) {
 
 if ( p ->tok != expected ) {
 
 println ( tos2((byte*)"check()") ) ;
 
string s= _STR("expected `%.*s` but got `%.*s`", Token_str( expected ).len, Token_str( expected ).str, Parser_strtok(& /* ? */* p ).len, Parser_strtok(& /* ? */* p ).str) ;
 
 Parser_next( p ) ;
 
printf( "next token = `%.*s`\n", Parser_strtok(& /* ? */* p ).len, Parser_strtok(& /* ? */* p ).str ) ;
 
 print_backtrace ( ) ;
 
 Parser_error( p , s ) ;
 
 }
 ;
 
 if ( expected == main__Token_rcbr ) {
 
 Parser_fmt_dec( p ) ;
 
 }
 ;
 
 Parser_fgen( p , Parser_strtok(& /* ? */* p ) ) ;
 
 if ( expected == main__Token_lcbr  &&  string_at( p ->scanner ->text , p ->scanner ->pos + 1) != '}' ) {
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 Parser_fmt_inc( p ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 if (string_ne( p ->scanner ->line_comment , tos2((byte*)"") ) ) {
 
 }
 ;
 
 
 }
 void Parser_error(Parser* p, string s) {
 
 if ( p ->pref ->is_debug ) {
 
 os__write_file ( tos2((byte*)"fns.txt") , Table_debug_fns(& /* ? */* p ->table ) ) ;
 
 }
 ;
 
printf( "pass=%d fn=`%.*s`\n", p ->pass, p ->cur_fn ->name.len, p ->cur_fn ->name.str ) ;
 
 CGen_save( p ->cgen ) ;
 
string cur_path= os__getwd ( ) ;
 
 if ( ! p ->pref ->is_repl  &&  ( string_contains( p ->file_path , tos2((byte*)"v/compiler") )  ||  string_contains( cur_path , tos2((byte*)"v/compiler") ) ) ) {
 
 println ( tos2((byte*)"\n=========================") ) ;
 
 println ( tos2((byte*)"It looks like you are building V. It is being frequently updated every day.") ) ;
 
 println ( tos2((byte*)"If you didn\'t modify the compiler\'s code, most likely there was a change that ") ) ;
 
 println ( tos2((byte*)"lead to this error.") ) ;
 
 println ( tos2((byte*)"\nRun `git pull && make`, that will most likely fix it.") ) ;
 
 println ( tos2((byte*)"\nIf this doesn\'t help, please create a GitHub issue.") ) ;
 
 println ( tos2((byte*)"=========================\n") ) ;
 
 }
 ;
 
 Scanner_error(& /* ? */* p ->scanner , string_replace( string_replace( string_replace( s , tos2((byte*)"array_") , tos2((byte*)"[]") ) , tos2((byte*)"__") , tos2((byte*)".") ) , tos2((byte*)"Option_") , tos2((byte*)"?") ) ) ;
 
 
 }
 bool Parser_first_pass(Parser* p) {
 
return  p ->pass == main__Pass_decl ;
 
 
 }
 string Parser_get_type(Parser* p) {
 
bool debug= Parser_fileis(& /* ? */* p , tos2((byte*)"fn_test") )  &&  0 ;
 
bool mul= 0 ;
 
int nr_muls= 0 ;
 
string typ= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_func ) {
 
 if ( debug ) {
 
printf( "\nget_type() .key_goT FN TYP line=%d\n", p ->scanner ->line_nr ) ;
 
 }
 ;
 
Fn f= (Fn) { .name =  tos2((byte*)"_") , .mod =  p ->mod , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
 Parser_next( p ) ;
 
int line_nr= p ->scanner ->line_nr ;
 
 Parser_fn_args( p ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ) ;
 
 if ( p ->scanner ->line_nr == line_nr ) {
 
 if ( debug ) {
 
 println ( tos2((byte*)"same line getting type") ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_name ) {
 
 f .typ  =  Parser_get_type( p ) ;
 
 }
  else { 
 
 f .typ  =  tos2((byte*)"void") ;
 
 }
 ;
 
 }
  else { 
 
 f .typ  =  tos2((byte*)"void") ;
 
 }
 ;
 
Type fn_typ= (Type) { .name =  Fn_typ_str( f ) , .mod =  p ->mod , .func =  f , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .parent = tos("", 0) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ;
 
 Table_register_type2( p ->table , fn_typ ) ;
 
return  Fn_typ_str( f ) ;
 
 }
 ;
 
bool is_arr= 0 ;
 
bool is_arr2= 0 ;
 
bool is_question= p ->tok == main__Token_question ;
 
 if ( is_question ) {
 
 Parser_check( p , main__Token_question ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 Parser_check( p , main__Token_lsbr ) ;
 
 if ( p ->tok == main__Token_number ) {
 
 typ  =  _STR("[%.*s]", p ->lit.len, p ->lit.str) ;
 
 Parser_next( p ) ;
 
 }
  else { 
 
 is_arr  =  1 ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 Parser_next( p ) ;
 
 if ( p ->tok == main__Token_number ) {
 
 typ = string_add(typ,  _STR("[%.*s]", p ->lit.len, p ->lit.str) ) ;
 
 Parser_check( p , main__Token_number ) ;
 
 }
  else { 
 
 is_arr2  =  1 ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 }
 ;
 
 }
 ;
 
 if ( ! p ->builtin_mod  &&  p ->tok == main__Token_name  && string_eq( p ->lit , tos2((byte*)"map") ) ) {
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lsbr ) ;
 
string key_type= Parser_check_name( p ) ;
 
 if (string_ne( key_type , tos2((byte*)"string") ) ) {
 
 Parser_error( p , tos2((byte*)"maps only support string keys for now") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
string val_type= Parser_check_name( p ) ;
 
 typ  =  _STR("map_%.*s", val_type.len, val_type.str) ;
 
 Parser_register_map( p , typ ) ;
 
return  typ ;
 
 }
 ;
 
 while ( p ->tok == main__Token_mul ) {
 
 
 mul  =  1 ;
 
 nr_muls ++ ;
 
 Parser_check( p , main__Token_mul ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_amp ) {
 
 mul  =  1 ;
 
 nr_muls ++ ;
 
 Parser_check( p , main__Token_amp ) ;
 
 }
 ;
 
 typ = string_add(typ,  p ->lit ) ;
 
 if ( ! p ->is_struct_init ) {
 
 Parser_fgen( p , p ->lit ) ;
 
 }
 ;
 
 if (string_eq( p ->lit , tos2((byte*)"C") )  &&  Parser_peek( p ) == main__Token_dot ) {
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 typ  =  p ->lit ;
 
 }
  else { 
 
 if ( Parser_peek( p ) == main__Token_dot ) {
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 typ = string_add(typ,  _STR("__%.*s", p ->lit.len, p ->lit.str) ) ;
 
 }
 ;
 
Type* t= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 if (string_eq( t ->name , tos2((byte*)"") )  &&  ! p ->builtin_mod ) {
 
 if ( ! string_contains( typ , tos2((byte*)"array_") )  && string_ne( p ->mod , tos2((byte*)"main") )  &&  ! string_contains( typ , tos2((byte*)"__") )  &&  ! string_starts_with( typ , tos2((byte*)"[") ) ) {
 
 typ  =  Parser_prepend_mod(& /* ? */* p , typ ) ;
 
 }
 ;
 
 t  =  Table_find_type(& /* ? */* p ->table , typ ) ;
 
 if (string_eq( t ->name , tos2((byte*)"") )  &&  ! p ->pref ->translated  &&  ! Parser_first_pass(& /* ? */* p )  &&  ! string_starts_with( typ , tos2((byte*)"[") ) ) {
 
 println ( tos2((byte*)"get_type() bad type") ) ;
 
 Parser_error( p , _STR("unknown type `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"void") ) ) {
 
 Parser_error( p , _STR("unknown type `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 if ( mul ) {
 
 typ = string_add(typ,  strings__repeat ( '*' , nr_muls ) ) ;
 
 }
 ;
 
 if ( is_arr2 ) {
 
 typ  =  _STR("array_array_%.*s", typ.len, typ.str) ;
 
 Parser_register_array( p , typ ) ;
 
 }
  else  if ( is_arr ) {
 
 typ  =  _STR("array_%.*s", typ.len, typ.str) ;
 
 Parser_register_array( p , typ ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 if ( p ->tok == main__Token_question  ||  is_question ) {
 
 typ  =  _STR("Option_%.*s", typ.len, typ.str) ;
 
 Table_register_type_with_parent( p ->table , typ , tos2((byte*)"Option") ) ;
 
 if ( p ->tok == main__Token_question ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"byteptr") ) ) {
 
return  tos2((byte*)"byte*") ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"voidptr") ) ) {
 
return  tos2((byte*)"void*") ;
 
 }
 ;
 
 if ( string_last_index( typ , tos2((byte*)"__") ) > string_index( typ , tos2((byte*)"__") ) ) {
 
 Parser_error( p , _STR("2 __ in gettype(): typ=\"%.*s\"", typ.len, typ.str) ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 void Parser_print_tok(Parser* p) {
 
 if ( p ->tok == main__Token_name ) {
 
 println ( p ->lit ) ;
 
 return ;
 
 }
 ;
 
 if ( p ->tok == main__Token_str ) {
 
printf( "\"%.*s\"\n", p ->lit.len, p ->lit.str ) ;
 
 return ;
 
 }
 ;
 
 println ( Token_str( p ->tok ) ) ;
 
 
 }
 string Parser_statements(Parser* p) {
 
 Parser_log(& /* ? */* p , tos2((byte*)"statements()") ) ;
 
string typ= Parser_statements_no_rcbr( p ) ;
 
 if ( ! p ->inside_if_expr ) {
 
 Parser_genln( p , tos2((byte*)"}") ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_statements_no_rcbr(Parser* p) {
 
 Fn_open_scope( p ->cur_fn ) ;
 
 if ( ! p ->inside_if_expr ) {
 
 Parser_genln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
int i= 0 ;
 
string last_st_typ= tos2((byte*)"") ;
 
 while ( p ->tok != main__Token_rcbr  &&  p ->tok != main__Token_eof  &&  p ->tok != main__Token_key_case  &&  p ->tok != main__Token_key_default  &&  Parser_peek( p ) != main__Token_arrow ) {
 
 
 last_st_typ  =  Parser_statement( p , 1 ) ;
 
 if ( ! p ->inside_if_expr ) {
 
 Parser_genln( p , tos2((byte*)"") ) ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 }
 ;
 
 i ++ ;
 
 if ( i > 50000 ) {
 
 CGen_save( p ->cgen ) ;
 
 Parser_error( p , _STR("more than 50 000 statements in function `%.*s`", p ->cur_fn ->name.len, p ->cur_fn ->name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok != main__Token_key_case  &&  p ->tok != main__Token_key_default  &&  Parser_peek( p ) != main__Token_arrow ) {
 
 Parser_check( p , main__Token_rcbr ) ;
 
 }
  else { 
 
 }
 ;
 
 Parser_close_scope( p ) ;
 
return  last_st_typ ;
 
 
 }
 void Parser_close_scope(Parser* p) {
 
int i= p ->cur_fn ->var_idx - 1 ;
 
 for (
  ;  i >= 0  ;  i -- ) { 
 
 
Var v= ( *(Var*) array__get( p ->cur_fn ->local_vars , i) ) ;
 
 if ( v .scope_level != p ->cur_fn ->scope_level ) {
 
 break
 ;
 
 }
 ;
 
 if ( 0  &&  ! p ->building_v  &&  ! v .is_mut  &&  v .is_alloc ) {
 
 if ( string_starts_with( v .typ , tos2((byte*)"array_") ) ) {
 
 Parser_genln( p , _STR("v_array_free(%.*s); // close_scope free", v .name.len, v .name.str) ) ;
 
 }
  else  if (string_eq( v .typ , tos2((byte*)"string") ) ) {
 
 Parser_genln( p , _STR("v_string_free(%.*s); // close_scope free", v .name.len, v .name.str) ) ;
 
 }
  else  if ( v .ptr ) {
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 p ->cur_fn ->var_idx  =  i + 1 ;
 
 p ->cur_fn ->scope_level -- ;
 
 
 }
 void Parser_genln(Parser* p, string s) {
 
 CGen_genln( p ->cgen , s ) ;
 
 
 }
 void Parser_gen(Parser* p, string s) {
 
 CGen_gen( p ->cgen , s ) ;
 
 
 }
 void Parser_vh_genln(Parser* p, string s) {
 
_PUSH(& p ->vh_lines , ( s ), tmp97, string) ;
 
 
 }
 string Parser_statement(Parser* p, bool add_semi) {
 
 p ->cgen ->is_tmp  =  0 ;
 
Token tok= p ->tok ;
 
string q= tos2((byte*)"") ;
 
 if ( ( tok ==  main__Token_name )) { /* case */
 
Token next= Parser_peek( p ) ;
 
 if ( p ->pref ->is_verbose ) {
 
 println ( Token_str( next ) ) ;
 
 }
 ;
 
 if ( Parser_peek( p ) == main__Token_colon ) {
 
 Parser_fmt_dec( p ) ;
 
string label= Parser_check_name( p ) ;
 
 Parser_fmt_inc( p ) ;
 
 Parser_genln( p ,string_add( label , tos2((byte*)":") ) ) ;
 
 Parser_check( p , main__Token_colon ) ;
 
return  tos2((byte*)"") ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_decl_assign ) {
 
 Parser_log(& /* ? */* p , tos2((byte*)"var decl") ) ;
 
 Parser_var_decl( p ) ;
 
 }
  else  if (string_eq( p ->lit , tos2((byte*)"jsdecode") ) ) {
 
 Parser_js_decode( p ) ;
 
 }
  else { 
 
 q  =  Parser_bool_expression( p ) ;
 
 }
 ;
 
 }
 else  if ( ( tok ==  main__Token_key_goto )) { /* case */
 
 Parser_check( p , main__Token_key_goto ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
string label= Parser_check_name( p ) ;
 
 Parser_genln( p , _STR("goto %.*s;", label.len, label.str) ) ;
 
return  tos2((byte*)"") ;
 
 }
 else  if ( ( tok ==  main__Token_key_defer )) { /* case */
 
 Parser_defer_st( p ) ;
 
return  tos2((byte*)"") ;
 
 }
 else  if ( ( tok ==  main__Token_hash )) { /* case */
 
 Parser_chash( p ) ;
 
return  tos2((byte*)"") ;
 
 }
 else  if ( ( tok ==  main__Token_dollar )) { /* case */
 
 Parser_comp_time( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_if )) { /* case */
 
 Parser_if_st( p , 0 , 0 ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_for )) { /* case */
 
 Parser_for_st( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_switch ) ||   ( tok ==  main__Token_key_match )) { /* case */
 
 Parser_switch_statement( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_mut ) ||   ( tok ==  main__Token_key_static )) { /* case */
 
 Parser_var_decl( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_return )) { /* case */
 
 Parser_return_st( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_lcbr )) { /* case */
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_genln( p , tos2((byte*)"{") ) ;
 
 Parser_statements( p ) ;
 
return  tos2((byte*)"") ;
 
 }
 else  if ( ( tok ==  main__Token_key_continue )) { /* case */
 
 if ( p ->for_expr_cnt == 0 ) {
 
 Parser_error( p , tos2((byte*)"`continue` statement outside `for`") ) ;
 
 }
 ;
 
 Parser_genln( p , tos2((byte*)"continue") ) ;
 
 Parser_check( p , main__Token_key_continue ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_break )) { /* case */
 
 if ( p ->for_expr_cnt == 0 ) {
 
 Parser_error( p , tos2((byte*)"`break` statement outside `for`") ) ;
 
 }
 ;
 
 Parser_genln( p , tos2((byte*)"break") ) ;
 
 Parser_check( p , main__Token_key_break ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_go )) { /* case */
 
 Parser_go_statement( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_assert )) { /* case */
 
 Parser_assert_statement( p ) ;
 
 }
 else  { // default:
 
string typ= Parser_expression( p ) ;
 
 if ( p ->inside_if_expr ) {
 
 }
  else { 
 
 Parser_genln( p , tos2((byte*)"; ") ) ;
 
 }
 ;
 
return  typ ;
 
 }
 ;
 
 if ( p ->inside_if_expr  &&  p ->tok != main__Token_rcbr ) {
 
 Parser_gen( p , tos2((byte*)", ") ) ;
 
 }
 ;
 
 if ( add_semi  &&  ! p ->inside_if_expr ) {
 
 Parser_genln( p , tos2((byte*)";") ) ;
 
 }
 ;
 
return  q ;
 
 
 }
 void Parser_assign_statement(Parser* p, Var v, int ph, bool is_map) {
 
 Parser_log(& /* ? */* p , _STR("assign_statement() name=%.*s tok=", v .name.len, v .name.str) ) ;
 
Token tok= p ->tok ;
 
 if ( ! v .is_mut  &&  ! v .is_arg  &&  ! p ->pref ->translated  &&  ! v .is_global ) {
 
 Parser_error( p , _STR("`%.*s` is immutable", v .name.len, v .name.str) ) ;
 
 }
 ;
 
 if ( ! v .is_changed ) {
 
 Fn_mark_var_changed(& /* ? */* p ->cur_fn , v ) ;
 
 }
 ;
 
bool is_str=string_eq( v .typ , tos2((byte*)"string") ) ;
 
 if ( ( tok ==  main__Token_assign )) { /* case */
 
 if ( ! is_map ) {
 
 Parser_gen( p , tos2((byte*)" = ") ) ;
 
 }
 ;
 
 }
 else  if ( ( tok ==  main__Token_plus_assign )) { /* case */
 
 if ( is_str ) {
 
 Parser_gen( p , _STR("= string_add(%.*s, ", v .name.len, v .name.str) ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)" += ") ) ;
 
 }
 ;
 
 }
 else  { // default:
 
 Parser_gen( p ,string_add(string_add( tos2((byte*)" ") , Token_str( p ->tok ) ) , tos2((byte*)" ") ) ) ;
 
 }
 ;
 
 Parser_fspace( p ) ;
 
 Parser_fgen( p , Token_str( tok ) ) ;
 
 Parser_fspace( p ) ;
 
 Parser_next( p ) ;
 
int pos= p ->cgen ->cur_line .len ;
 
string expr_type= Parser_bool_expression( p ) ;
 
 if ( string_starts_with( p ->assigned_type , tos2((byte*)"Option_") )  && string_eq( expr_type , string_right( p ->assigned_type , tos2((byte*)"Option_") .len ) ) ) {
 
 println ( tos2((byte*)"allowing option asss") ) ;
 
string expr= string_right( p ->cgen ->cur_line , pos ) ;
 
string left= string_left( p ->cgen ->cur_line , pos ) ;
 
 CGen_resetln( p ->cgen ,string_add( left , _STR("opt_ok(%.*s, sizeof(%.*s))", expr.len, expr.str, expr_type.len, expr_type.str) ) ) ;
 
 }
  else  if ( ! p ->builtin_mod  &&  ! Parser_check_types_no_throw( p , expr_type , p ->assigned_type ) ) {
 
 p ->scanner ->line_nr -- ;
 
 Parser_error( p , _STR("cannot use type `%.*s` as type `%.*s` in assignment", expr_type.len, expr_type.str, p ->assigned_type.len, p ->assigned_type.str) ) ;
 
 }
 ;
 
 if ( is_str  &&  tok == main__Token_plus_assign ) {
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 }
 ;
 
 p ->assigned_type  =  tos2((byte*)"") ;
 
 if ( ! v .is_used ) {
 
 Fn_mark_var_used(& /* ? */* p ->cur_fn , v ) ;
 
 }
 ;
 
 
 }
 void Parser_var_decl(Parser* p) {
 
 p ->is_alloc  =  0 ;
 
bool is_mut= p ->tok == main__Token_key_mut  ||  p ->prev_tok == main__Token_key_for ;
 
bool is_static= p ->tok == main__Token_key_static ;
 
 if ( p ->tok == main__Token_key_mut ) {
 
 Parser_check( p , main__Token_key_mut ) ;
 
 Parser_fspace( p ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_static ) {
 
 Parser_check( p , main__Token_key_static ) ;
 
 Parser_fspace( p ) ;
 
 }
 ;
 
string name= Parser_check_name( p ) ;
 
 p ->var_decl_name  =  name ;
 
 if ( ! p ->builtin_mod  &&  Fn_known_var(& /* ? */* p ->cur_fn , name ) ) {
 
Var v= Fn_find_var(& /* ? */* p ->cur_fn , name ) ;
 
 Parser_error( p , _STR("redefinition of `%.*s`", name.len, name.str) ) ;
 
 }
 ;
 
 if ( name .len > 1  &&  contains_capital ( name ) ) {
 
 Parser_error( p , tos2((byte*)"variable names cannot contain uppercase letters, use snake_case instead") ) ;
 
 }
 ;
 
 Parser_check_space( p , main__Token_decl_assign ) ;
 
int pos= CGen_add_placeholder( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
bool or_else= p ->tok == main__Token_key_orelse ;
 
string tmp= Parser_get_tmp( p ) ;
 
 if ( or_else ) {
 
 CGen_set_placeholder( p ->cgen , pos , _STR("%.*s %.*s = ", typ.len, typ.str, tmp.len, tmp.str) ) ;
 
 Parser_genln( p , tos2((byte*)";") ) ;
 
 typ  =  string_replace( typ , tos2((byte*)"Option_") , tos2((byte*)"") ) ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_genln( p , _STR("if (!%.*s .ok) {", tmp.len, tmp.str) ) ;
 
 Parser_register_var( p , (Var) { .name =  tos2((byte*)"err") , .typ =  tos2((byte*)"string") , .is_mut =  0 , .is_used =  1 , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_changed = 0 , .scope_level = 0 } ) ;
 
 Parser_genln( p , _STR("string err = %.*s . error;", tmp.len, tmp.str) ) ;
 
 Parser_statements( p ) ;
 
 Parser_genln( p , _STR("%.*s %.*s = *(%.*s*) %.*s . data;", typ.len, typ.str, name.len, name.str, typ.len, typ.str, tmp.len, tmp.str) ) ;
 
 if ( ! p ->returns  &&  p ->prev_tok2 != main__Token_key_continue  &&  p ->prev_tok2 != main__Token_key_break ) {
 
 Parser_error( p , tos2((byte*)"`or` block must return/continue/break/panic") ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_register_var( p , (Var) { .name =  name , .typ =  typ , .is_mut =  is_mut , .is_alloc =  p ->is_alloc , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ) ;
 
 if ( ! or_else ) {
 
string gen_name= Table_var_cgen_name( p ->table , name ) ;
 
string nt_gen=string_add( Table_cgen_name_type_pair(& /* ? */* p ->table , gen_name , typ ) , tos2((byte*)"=") ) ;
 
 if ( is_static ) {
 
 nt_gen  =  _STR("static %.*s", nt_gen.len, nt_gen.str) ;
 
 }
 ;
 
 CGen_set_placeholder( p ->cgen , pos , nt_gen ) ;
 
 }
 ;
 
 p ->var_decl_name  =  tos2((byte*)"") ;
 
 
 }
 string Parser_bool_expression(Parser* p) {
 
Token tok= p ->tok ;
 
string typ= Parser_bterm( p ) ;
 
bool got_and= 0 ;
 
bool got_or= 0 ;
 
 while ( p ->tok == main__Token_and  ||  p ->tok == main__Token_logical_or ) {
 
 
 if ( p ->tok == main__Token_and ) {
 
 got_and  =  1 ;
 
 if ( got_or ) {
 
 Parser_error( p , main__and_or_error ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_logical_or ) {
 
 got_or  =  1 ;
 
 if ( got_and ) {
 
 Parser_error( p , main__and_or_error ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen( p , _STR(" %.*s ", Token_str( p ->tok ).len, Token_str( p ->tok ).str) ) ;
 
 Parser_check_space( p , p ->tok ) ;
 
 Parser_check_types( p , Parser_bterm( p ) , typ ) ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"") ) ) {
 
 println ( tos2((byte*)"curline:") ) ;
 
 println ( p ->cgen ->cur_line ) ;
 
 println ( Token_str( tok ) ) ;
 
 Parser_error( p , tos2((byte*)"expr() returns empty type") ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_bterm(Parser* p) {
 
int ph= CGen_add_placeholder( p ->cgen ) ;
 
string typ= Parser_expression( p ) ;
 
 p ->expected_type  =  typ ;
 
bool is_str=string_eq( typ , tos2((byte*)"string") ) ;
 
Token tok= p ->tok ;
 
 if ( tok == main__Token_eq  ||  tok == main__Token_gt  ||  tok == main__Token_lt  ||  tok == main__Token_le  ||  tok == main__Token_ge  ||  tok == main__Token_ne ) {
 
 Parser_fgen( p , _STR(" %.*s ", Token_str( p ->tok ).len, Token_str( p ->tok ).str) ) ;
 
 if ( is_str ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
  else { 
 
 Parser_gen( p , Token_str( tok ) ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 Parser_check_types( p , Parser_expression( p ) , typ ) ;
 
 typ  =  tos2((byte*)"bool") ;
 
 if ( is_str ) {
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 if ( ( tok ==  main__Token_eq )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_eq(") ) ;
 
 }
 else  if ( ( tok ==  main__Token_ne )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_ne(") ) ;
 
 }
 else  if ( ( tok ==  main__Token_le )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_le(") ) ;
 
 }
 else  if ( ( tok ==  main__Token_ge )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_ge(") ) ;
 
 }
 else  if ( ( tok ==  main__Token_gt )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_gt(") ) ;
 
 }
 else  if ( ( tok ==  main__Token_lt )) { /* case */
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_lt(") ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_name_expr(Parser* p) {
 
int ph= CGen_add_placeholder( p ->cgen ) ;
 
bool ptr= p ->tok == main__Token_amp ;
 
bool deref= p ->tok == main__Token_mul ;
 
 if ( ptr  ||  deref ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 if ( deref ) {
 
 if ( p ->pref ->is_play  &&  ! p ->builtin_mod ) {
 
 Parser_error( p , tos2((byte*)"dereferencing is temporarily disabled on the playground, will be fixed soon") ) ;
 
 }
 ;
 
 }
 ;
 
string name= p ->lit ;
 
 Parser_fgen( p , name ) ;
 
string orig_name= name ;
 
bool is_c=string_eq( name , tos2((byte*)"C") )  &&  Parser_peek( p ) == main__Token_dot ;
 
bool is_c_struct_init= is_c  &&  ptr ;
 
 if ( is_c ) {
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 name  =  p ->lit ;
 
 Parser_fgen( p , name ) ;
 
 if ( ! is_c_struct_init  &&  Parser_peek( p ) == main__Token_lcbr ) {
 
 is_c_struct_init  =  1 ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_dot ) {
 
Type* T= Parser_find_type(& /* ? */* p , p ->expected_type ) ;
 
 if ( T ->is_enum ) {
 
 Parser_check( p , main__Token_dot ) ;
 
string val= Parser_check_name( p ) ;
 
 if ( ! Type_has_enum_val(& /* ? */* T , val ) ) {
 
 Parser_error( p , _STR("enum `%.*s` does not have value `%.*s`", T ->name.len, T ->name.str, val.len, val.str) ) ;
 
 }
 ;
 
 Parser_gen( p ,string_add(string_add(string_add(string_add( T ->mod , tos2((byte*)"__") ) , p ->expected_type ) , tos2((byte*)"_") ) , val ) ) ;
 
 }
 ;
 
return  p ->expected_type ;
 
 }
 ;
 
 if ( ( (string_eq( name , p ->mod )  &&  Table_known_mod(& /* ? */* p ->table , name ) )  ||  FileImportTable_known_alias(& /* ? */* p ->import_table , name ) )  &&  ! Fn_known_var(& /* ? */* p ->cur_fn , name )  &&  ! is_c ) {
 
string mod= name ;
 
 if (string_ne( name , p ->mod )  &&  FileImportTable_known_alias(& /* ? */* p ->import_table , name ) ) {
 
 mod  =  string_replace( FileImportTable_resolve_alias(& /* ? */* p ->import_table , name ) , tos2((byte*)".") , tos2((byte*)"_dot_") ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
 name  =  p ->lit ;
 
 Parser_fgen( p , name ) ;
 
 name  =  prepend_mod ( mod , name ) ;
 
 }
  else  if ( ! Table_known_type(& /* ? */* p ->table , name )  &&  ! Fn_known_var(& /* ? */* p ->cur_fn , name )  &&  ! Table_known_fn(& /* ? */* p ->table , name )  &&  ! Table_known_const(& /* ? */* p ->table , name )  &&  ! is_c ) {
 
 name  =  Parser_prepend_mod(& /* ? */* p , name ) ;
 
 }
 ;
 
Var v= Fn_find_var(& /* ? */* p ->cur_fn , name ) ;
 
 if (string_eq( name ,string_add( tos2((byte*)"main__") , p ->var_decl_name ) ) ) {
 
 v .name  =  p ->var_decl_name ;
 
 v .typ  =  tos2((byte*)"voidptr") ;
 
 v .is_mut  =  1 ;
 
 }
 ;
 
 if ( v .name .len != 0 ) {
 
 if ( ptr ) {
 
 Parser_gen( p , tos2((byte*)"& /*vvar*/ ") ) ;
 
 }
  else  if ( deref ) {
 
 Parser_gen( p , tos2((byte*)"*") ) ;
 
 }
 ;
 
string typ= Parser_var_expr( p , v ) ;
 
 if ( deref ) {
 
 if ( ! string_contains( typ , tos2((byte*)"*") )  &&  ! string_ends_with( typ , tos2((byte*)"ptr") ) ) {
 
printf( "name=\"%.*s\", t=%.*s\n", name.len, name.str, v .typ.len, v .typ.str ) ;
 
 Parser_error( p , _STR("dereferencing requires a pointer, but got `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 typ  =  string_replace( typ , tos2((byte*)"ptr") , tos2((byte*)"") ) ;
 
 typ  =  string_replace( typ , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 }
  else  if ( ptr ) {
 
 typ = string_add(typ,  tos2((byte*)"*") ) ;
 
 }
 ;
 
return  typ ;
 
 }
 ;
 
 if ( Table_known_type(& /* ? */* p ->table , name ) ) {
 
 if ( ! is_c  &&  ( Parser_peek( p ) == main__Token_lpar  ||  ( deref  &&  Parser_peek( p ) == main__Token_rpar ) ) ) {
 
 if ( deref ) {
 
 name = string_add(name,  tos2((byte*)"*") ) ;
 
 }
  else  if ( ptr ) {
 
 name = string_add(name,  tos2((byte*)"*") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)"(") ) ;
 
string typ= Parser_cast( p , name ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 while ( p ->tok == main__Token_dot ) {
 
 
 typ  =  Parser_dot( p , typ , ph ) ;
 
 }
 ;
 
return  typ ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_dot ) {
 
Type* enum_type= Table_find_type(& /* ? */* p ->table , name ) ;
 
 if ( ! enum_type ->is_enum ) {
 
 Parser_error( p , _STR("`%.*s` is not an enum", name.len, name.str) ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
string val= p ->lit ;
 
 Parser_gen( p ,string_add(string_add(string_add(string_add( enum_type ->mod , tos2((byte*)"__") ) , enum_type ->name ) , tos2((byte*)"_") ) , val ) ) ;
 
 Parser_next( p ) ;
 
return  enum_type ->name ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_lcbr ) {
 
 if ( is_c_struct_init ) {
 
 p ->is_c_struct_init  =  1 ;
 
 CGen_insert_before( p ->cgen , tos2((byte*)"struct /*c struct init*/") ) ;
 
 }
 ;
 
 if ( ptr ) {
 
 name = string_add(name,  tos2((byte*)"*") ) ;
 
 }
 ;
 
 if (string_eq( name , tos2((byte*)"T") ) ) {
 
 name  =  p ->cur_gen_type ;
 
 }
 ;
 
return  Parser_struct_init( p , name , is_c_struct_init ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_c ) {
 
 if ( Parser_peek( p ) != main__Token_lpar ) {
 
 Parser_gen( p , name ) ;
 
 Parser_next( p ) ;
 
return  tos2((byte*)"int") ;
 
 }
 ;
 
Fn f= (Fn) { .name =  name , .is_c =  1 , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
 Parser_fn_call( p , f , 0 , tos2((byte*)"") , tos2((byte*)"") ) ;
 
Fn cfn= Table_find_fn(& /* ? */* p ->table , name ) ;
 
 if (string_eq( cfn .name , tos2((byte*)"") ) ) {
 
return  tos2((byte*)"void*") ;
 
 }
 ;
 
return  cfn .typ ;
 
 }
 ;
 
Var c= Table_find_const(& /* ? */* p ->table , name ) ;
 
 if (string_ne( c .name , tos2((byte*)"") )  &&  ptr  &&  ! c .is_global ) {
 
 Parser_error( p , _STR("cannot take the address of constant `%.*s`", c .name.len, c .name.str) ) ;
 
 }
 ;
 
 if ( c .name .len != 0 ) {
 
 if ( ptr ) {
 
 Parser_gen( p , tos2((byte*)"& /*const*/ ") ) ;
 
 }
 ;
 
 Parser_log(& /* ? */* p , tos2((byte*)"calling var expr") ) ;
 
string typ= Parser_var_expr( p , c ) ;
 
 if ( ptr ) {
 
 typ = string_add(typ,  tos2((byte*)"*") ) ;
 
 }
 ;
 
return  typ ;
 
 }
 ;
 
Fn f= Table_find_fn(& /* ? */* p ->table , name ) ;
 
 if (string_eq( f .name , tos2((byte*)"") ) ) {
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 if ( p ->v_script ) {
 
 name  =  string_replace( name , tos2((byte*)"main__") , tos2((byte*)"os__") ) ;
 
 f  =  Table_find_fn(& /* ? */* p ->table , name ) ;
 
 }
 ;
 
 if (string_eq( f .name , tos2((byte*)"") ) ) {
 
 if ( Table_known_mod(& /* ? */* p ->table , orig_name )  ||  FileImportTable_known_alias(& /* ? */* p ->import_table , orig_name ) ) {
 
 name  =  string_replace( string_replace( name , tos2((byte*)"__") , tos2((byte*)".") ) , tos2((byte*)"_dot_") , tos2((byte*)".") ) ;
 
 Parser_error( p , _STR("undefined: `%.*s`", name.len, name.str) ) ;
 
 }
  else { 
 
 Parser_error( p , _STR("undefined: `%.*s`", orig_name.len, orig_name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
  else { 
 
 Parser_next( p ) ;
 
return  tos2((byte*)"void") ;
 
 }
 ;
 
 }
 ;
 
Token peek= Parser_peek( p ) ;
 
 if ( peek != main__Token_lpar  &&  peek != main__Token_lt ) {
 
 Parser_gen( p , Table_cgen_name( p ->table ,& /*11 EXP:"Fn*" GOT:"Fn" */ f ) ) ;
 
 Parser_next( p ) ;
 
return  tos2((byte*)"void*") ;
 
 }
 ;
 
 if (string_eq( f .typ , tos2((byte*)"void") )  &&  ! p ->inside_if_expr ) {
 
 }
 ;
 
 Parser_log(& /* ? */* p , tos2((byte*)"calling function") ) ;
 
 Parser_fn_call( p , f , 0 , tos2((byte*)"") , tos2((byte*)"") ) ;
 
 if ( p ->tok == main__Token_dot ) {
 
string typ= tos2((byte*)"") ;
 
 while ( p ->tok == main__Token_dot ) {
 
 
 typ  =  Parser_dot( p , f .typ , ph ) ;
 
 }
 ;
 
return  typ ;
 
 }
 ;
 
 Parser_log(& /* ? */* p , tos2((byte*)"end of name_expr") ) ;
 
return  f .typ ;
 
 
 }
 string Parser_var_expr(Parser* p, Var v) {
 
 Parser_log(& /* ? */* p , _STR("\nvar_expr() v.name=\"%.*s\" v.typ=\"%.*s\"", v .name.len, v .name.str, v .typ.len, v .typ.str) ) ;
 
 Fn_mark_var_used(& /* ? */* p ->cur_fn , v ) ;
 
int fn_ph= CGen_add_placeholder( p ->cgen ) ;
 
 p ->expr_var  =  v ;
 
 Parser_gen( p , Table_var_cgen_name( p ->table , v .name ) ) ;
 
 Parser_next( p ) ;
 
string typ= v .typ ;
 
 if ( string_starts_with( typ , tos2((byte*)"fn ") ) ) {
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 Parser_gen( p , tos2((byte*)"(") ) ;
 
 Parser_fn_call_args( p ,& /*11 EXP:"Fn*" GOT:"Fn" */ T ->func ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 typ  =  T ->func .typ ;
 
 }
 ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 typ  =  Parser_index_expr( p , typ , fn_ph ) ;
 
 }
 ;
 
 while ( p ->tok == main__Token_dot ) {
 
 
 typ  =  Parser_dot( p , typ , fn_ph ) ;
 
 Parser_log(& /* ? */* p , _STR("typ after dot=%.*s", typ.len, typ.str) ) ;
 
 if ( p ->tok == main__Token_lsbr ) {
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_inc  ||  p ->tok == main__Token_dec ) {
 
 if ( ! v .is_mut  &&  ! v .is_arg  &&  ! p ->pref ->translated ) {
 
 Parser_error( p , _STR("`%.*s` is immutable", v .name.len, v .name.str) ) ;
 
 }
 ;
 
 if ( ! v .is_changed ) {
 
 Fn_mark_var_changed(& /* ? */* p ->cur_fn , v ) ;
 
 }
 ;
 
 if (string_ne( typ , tos2((byte*)"int") ) ) {
 
 if ( ! p ->pref ->translated  &&  ! is_number_type ( typ ) ) {
 
 Parser_error( p , _STR("cannot ++/-- value of type `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen( p , Token_str( p ->tok ) ) ;
 
 Parser_fgen( p , Token_str( p ->tok ) ) ;
 
 Parser_next( p ) ;
 
 if ( p ->pref ->translated ) {
 
 }
  else { 
 
return  tos2((byte*)"void") ;
 
 }
 ;
 
 }
 ;
 
 typ  =  Parser_index_expr( p , typ , fn_ph ) ;
 
 if ( p ->tok == main__Token_dot ) {
 
 while ( p ->tok == main__Token_dot ) {
 
 
 typ  =  Parser_dot( p , typ , fn_ph ) ;
 
 }
 ;
 
 typ  =  Parser_index_expr( p , typ , fn_ph ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 bool Parser_fileis(Parser* p, string s) {
 
return  string_contains( p ->scanner ->file_path , s ) ;
 
 
 }
 string Parser_dot(Parser* p, string str_typ, int method_ph) {
 
 Parser_check( p , main__Token_dot ) ;
 
Type* typ= Parser_find_type(& /* ? */* p , str_typ ) ;
 
 if ( typ ->name .len == 0 ) {
 
 Parser_error( p , _STR("dot(): cannot find type `%.*s`", str_typ.len, str_typ.str) ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_dollar ) {
 
 Parser_comptime_method_call( p ,* typ ) ;
 
return  tos2((byte*)"void") ;
 
 }
 ;
 
string field_name= p ->lit ;
 
 Parser_fgen( p , field_name ) ;
 
 Parser_log(& /* ? */* p , _STR("dot() field_name=%.*s typ=%.*s", field_name.len, field_name.str, str_typ.len, str_typ.str) ) ;
 
bool has_field= Table_type_has_field(& /* ? */* p ->table , typ , field_name ) ;
 
bool has_method= Table_type_has_method(& /* ? */* p ->table , typ , field_name ) ;
 
 if ( ! typ ->is_c  &&  ! has_field  &&  ! has_method  &&  ! Parser_first_pass(& /* ? */* p ) ) {
 
 if ( string_starts_with( typ ->name , tos2((byte*)"Option_") ) ) {
 
string opt_type= string_right( typ ->name , 7 ) ;
 
 Parser_error( p , _STR("unhandled option type: %.*s?", opt_type.len, opt_type.str) ) ;
 
 }
 ;
 
 Parser_error( p , _STR("type `%.*s` has no field or method `%.*s`", typ ->name.len, typ ->name.str, field_name.len, field_name.str) ) ;
 
 }
 ;
 
string dot= tos2((byte*)".") ;
 
 if ( string_contains( str_typ , tos2((byte*)"*") ) ) {
 
 dot  =  tos2((byte*)"->") ;
 
 }
 ;
 
 if ( has_field ) {
 
Var field= Table_find_field(& /* ? */* p ->table , typ , field_name ) ;
 
Token next= Parser_peek( p ) ;
 
bool modifying= Token_is_assign( next )  ||  next == main__Token_inc  ||  next == main__Token_dec ;
 
bool is_vi= Parser_fileis(& /* ? */* p , tos2((byte*)"vi") ) ;
 
 if ( ! p ->builtin_mod  &&  ! p ->pref ->translated  &&  modifying  &&  ! field .is_mut  &&  ! is_vi ) {
 
 Parser_error( p , _STR("cannot modify immutable field `%.*s` (type `%.*s`)", field_name.len, field_name.str, typ ->name.len, typ ->name.str) ) ;
 
 }
 ;
 
 if ( ! p ->builtin_mod  && string_ne( p ->mod , typ ->mod ) ) {
 
 }
 ;
 
 if ( field .access_mod == main__AccessMod_private  &&  ! p ->builtin_mod  &&  ! p ->pref ->translated  && string_ne( p ->mod , typ ->mod ) ) {
 
 Parser_error( p , _STR("cannot refer to unexported field `%.*s` (type `%.*s`)", field_name.len, field_name.str, typ ->name.len, typ ->name.str) ) ;
 
 }
 ;
 
 if ( field .access_mod == main__AccessMod_public  &&  ! p ->builtin_mod  && string_ne( p ->mod , typ ->mod ) ) {
 
 if ( ! field .is_mut  &&  ! p ->pref ->translated  &&  modifying ) {
 
 Parser_error( p , _STR("cannot modify public immutable field `%.*s` (type `%.*s`)", field_name.len, field_name.str, typ ->name.len, typ ->name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen( p ,string_add( dot , field_name ) ) ;
 
 Parser_next( p ) ;
 
return  field .typ ;
 
 }
 ;
 
Fn method= Table_find_method(& /* ? */* p ->table , typ , field_name ) ;
 
 Parser_fn_call( p , method , method_ph , tos2((byte*)"") , str_typ ) ;
 
 if (string_eq( method .typ , tos2((byte*)"array") )  &&  string_starts_with( typ ->name , tos2((byte*)"array_") ) ) {
 
return  typ ->name ;
 
 }
 ;
 
 if (string_eq( method .typ , tos2((byte*)"void*") )  &&  string_starts_with( typ ->name , tos2((byte*)"array_") ) ) {
 
return  string_right( typ ->name , 6 ) ;
 
 }
 ;
 
return  method .typ ;
 
 
 }
 string Parser_index_expr(Parser* p, string typ, int fn_ph) {
 
Var v= p ->expr_var ;
 
bool is_map= string_starts_with( typ , tos2((byte*)"map_") ) ;
 
bool is_str=string_eq( typ , tos2((byte*)"string") ) ;
 
bool is_arr0= string_starts_with( typ , tos2((byte*)"array_") ) ;
 
bool is_arr= is_arr0  || string_eq( typ , tos2((byte*)"array") ) ;
 
bool is_ptr=string_eq( typ , tos2((byte*)"byte*") )  || string_eq( typ , tos2((byte*)"byteptr") )  ||  string_contains( typ , tos2((byte*)"*") ) ;
 
bool is_indexer= p ->tok == main__Token_lsbr ;
 
bool close_bracket= 0 ;
 
 if ( is_indexer ) {
 
bool is_fixed_arr= string_at( typ , 0) == '[' ;
 
 if ( ! is_str  &&  ! is_arr  &&  ! is_map  &&  ! is_ptr  &&  ! is_fixed_arr ) {
 
 Parser_error( p , _STR("Cant [] non-array/string/map. Got type \"%.*s\"", typ.len, typ.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lsbr ) ;
 
 if ( is_str ) {
 
 typ  =  tos2((byte*)"byte") ;
 
 Parser_fgen( p , tos2((byte*)"[") ) ;
 
 if ( p ->builtin_mod ) {
 
 Parser_gen( p , tos2((byte*)".str[") ) ;
 
 close_bracket  =  1 ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_fixed_arr ) {
 
 if ( string_contains( typ , tos2((byte*)"][") ) ) {
 
int pos= string_index_after( typ , tos2((byte*)"[") , 1 ) ;
 
 typ  =  string_right( typ , pos ) ;
 
 }
  else { 
 
 typ  =  string_all_after( typ , tos2((byte*)"]") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)"[") ) ;
 
 close_bracket  =  1 ;
 
 }
  else  if ( is_ptr ) {
 
 typ  =  string_replace( typ , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 if ( ! is_arr ) {
 
 Parser_gen( p , tos2((byte*)"[/*ptr*/") ) ;
 
 close_bracket  =  1 ;
 
 }
 ;
 
 }
 ;
 
 if ( is_arr ) {
 
 if ( is_arr0 ) {
 
 if ( Parser_fileis(& /* ? */* p , tos2((byte*)"int_test") ) ) {
 
printf( "\nRRRR0 %.*s\n", typ.len, typ.str ) ;
 
 }
 ;
 
 typ  =  string_right( typ , 6 ) ;
 
 if ( Parser_fileis(& /* ? */* p , tos2((byte*)"int_test") ) ) {
 
printf( "RRRR %.*s\n", typ.len, typ.str ) ;
 
 }
 ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"array") ) ) {
 
 typ  =  tos2((byte*)"void*") ;
 
 }
 ;
 
 if ( p ->pref ->translated  &&  ! p ->builtin_mod ) {
 
 CGen_set_placeholder( p ->cgen , fn_ph , _STR("((%.*s*)(", typ.len, typ.str) ) ;
 
 Parser_gen( p , tos2((byte*)".data))[") ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_map ) {
 
 typ  =  string_replace( typ , tos2((byte*)"map_") , tos2((byte*)"") ) ;
 
 if (string_eq( typ , tos2((byte*)"map") ) ) {
 
 typ  =  tos2((byte*)"void*") ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 if ( is_arr ) {
 
Type* T= Table_find_type(& /* ? */* p ->table , Parser_expression( p ) ) ;
 
 if (string_ne( T ->parent , tos2((byte*)"int") ) ) {
 
 Parser_check_types( p , T ->name , tos2((byte*)"int") ) ;
 
 }
 ;
 
 }
  else { 
 
 Parser_expression( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 if ( close_bracket ) {
 
 Parser_gen( p , _STR("]/*r%.*s %d*/", typ.len, typ.str, v .is_mut) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_assign  ||  p ->tok == main__Token_plus_assign  ||  p ->tok == main__Token_minus_assign  ||  p ->tok == main__Token_mult_assign  ||  p ->tok == main__Token_div_assign  ||  p ->tok == main__Token_xor_assign  ||  p ->tok == main__Token_mod_assign  ||  p ->tok == main__Token_or_assign  ||  p ->tok == main__Token_and_assign  ||  p ->tok == main__Token_righ_shift_assign  ||  p ->tok == main__Token_left_shift_assign ) {
 
 if ( is_indexer  &&  is_str  &&  ! p ->builtin_mod ) {
 
 Parser_error( p , tos2((byte*)"strings are immutable") ) ;
 
 }
 ;
 
int assign_pos= p ->cgen ->cur_line .len ;
 
 p ->assigned_type  =  typ ;
 
 p ->expected_type  =  typ ;
 
 Parser_assign_statement( p , v , fn_ph , is_indexer  &&  ( is_map  ||  is_arr ) ) ;
 
 if ( is_indexer  &&  ( is_map  ||  is_arr ) ) {
 
string tmp= Parser_get_tmp( p ) ;
 
string tmp_val= string_right( p ->cgen ->cur_line , assign_pos ) ;
 
 CGen_resetln( p ->cgen , string_left( p ->cgen ->cur_line , assign_pos ) ) ;
 
 if ( is_map ) {
 
 CGen_set_placeholder( p ->cgen , fn_ph , tos2((byte*)"map__set(&") ) ;
 
 }
  else { 
 
 if ( is_ptr ) {
 
 CGen_set_placeholder( p ->cgen , fn_ph , tos2((byte*)"array_set(") ) ;
 
 }
  else { 
 
 CGen_set_placeholder( p ->cgen , fn_ph , tos2((byte*)"array_set(&/*q*/") ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen( p , _STR(", & %.*s)", tmp.len, tmp.str) ) ;
 
 CGen_insert_before( p ->cgen , _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len, tmp.str, tmp_val.len, tmp_val.str) ) ;
 
 }
 ;
 
return  typ ;
 
return  tos2((byte*)"void") ;
 
 }
  else  if ( ( is_map  ||  is_arr  ||  ( is_str  &&  ! p ->builtin_mod ) )  &&  is_indexer ) {
 
string index_expr= string_right( p ->cgen ->cur_line , fn_ph ) ;
 
 CGen_resetln( p ->cgen , string_left( p ->cgen ->cur_line , fn_ph ) ) ;
 
string tmp= Parser_get_tmp( p ) ;
 
string tmp_ok= Parser_get_tmp( p ) ;
 
 if ( is_map ) {
 
 Parser_gen( p , _STR("%.*s", tmp.len, tmp.str) ) ;
 
string def= type_default ( typ ) ;
 
 if (string_eq( def , tos2((byte*)"STRUCT_DEFAULT_VALUE") ) ) {
 
 def  =  tos2((byte*)"{0}") ;
 
 }
 ;
 
 CGen_insert_before( p ->cgen , _STR("%.*s %.*s = %.*s; bool %.*s = map_get(%.*s, & %.*s);", typ.len, typ.str, tmp.len, tmp.str, def.len, def.str, tmp_ok.len, tmp_ok.str, index_expr.len, index_expr.str, tmp.len, tmp.str) ) ;
 
 }
  else  if ( is_arr ) {
 
 if ( p ->pref ->translated  &&  ! p ->builtin_mod ) {
 
 Parser_gen( p , _STR("%.*s ]", index_expr.len, index_expr.str) ) ;
 
 }
  else { 
 
 if ( is_ptr ) {
 
 Parser_gen( p , _STR("( *(%.*s*) array__get(* %.*s) )", typ.len, typ.str, index_expr.len, index_expr.str) ) ;
 
 }
  else { 
 
 Parser_gen( p , _STR("( *(%.*s*) array__get(%.*s) )", typ.len, typ.str, index_expr.len, index_expr.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
  else  if ( is_str  &&  ! p ->builtin_mod ) {
 
 Parser_gen( p , _STR("string_at(%.*s)", index_expr.len, index_expr.str) ) ;
 
 }
 ;
 
 if ( is_map  && string_eq( typ , tos2((byte*)"string") ) ) {
 
 CGen_insert_before( p ->cgen , _STR("if (!%.*s) %.*s = tos(\"\", 0);", tmp_ok.len, tmp_ok.str, tmp.len, tmp.str) ) ;
 
 }
 ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_expression(Parser* p) {
 
 if ( string_contains( p ->scanner ->file_path , tos2((byte*)"test_test") ) ) {
 
printf( "expression() pass=%d tok=\n", p ->pass ) ;
 
 Parser_print_tok(& /* ? */* p ) ;
 
 }
 ;
 
 p ->cgen ;
 
 ( tos2((byte*)"/* expr start*/") ) ; 
 
int ph= CGen_add_placeholder( p ->cgen ) ;
 
string typ= Parser_term( p ) ;
 
bool is_str=string_eq( typ , tos2((byte*)"string") ) ;
 
 if ( p ->tok == main__Token_left_shift ) {
 
 if ( string_contains( typ , tos2((byte*)"array_") ) ) {
 
string tmp= Parser_get_tmp( p ) ;
 
string tmp_typ= string_right( typ , 6 ) ;
 
 Parser_check_space( p , main__Token_left_shift ) ;
 
 Parser_gen( p , tos2((byte*)", (") ) ;
 
 if ( ! p ->expr_var .is_mut  &&  ! p ->pref ->translated ) {
 
 Parser_error( p , _STR("`%.*s` is immutable (can\'t <<)", p ->expr_var .name.len, p ->expr_var .name.str) ) ;
 
 }
 ;
 
 if ( ! p ->expr_var .is_changed ) {
 
 Fn_mark_var_changed(& /* ? */* p ->cur_fn , p ->expr_var ) ;
 
 }
 ;
 
string expr_type= Parser_expression( p ) ;
 
bool push_array=string_eq( typ , expr_type ) ;
 
 if ( push_array ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"_PUSH_MANY(&") ) ;
 
 Parser_gen( p , _STR("), %.*s, %.*s)", tmp.len, tmp.str, typ.len, typ.str) ) ;
 
 }
  else { 
 
 Parser_check_types( p , expr_type , tmp_typ ) ;
 
string push_call= ( string_contains( typ , tos2((byte*)"*") ) ) ? ( tos2((byte*)"_PUSH(") ) : ( tos2((byte*)"_PUSH(&") ) ;
 
 CGen_set_placeholder( p ->cgen , ph , push_call ) ;
 
 Parser_gen( p , _STR("), %.*s, %.*s)", tmp.len, tmp.str, tmp_typ.len, tmp_typ.str) ) ;
 
 }
 ;
 
return  tos2((byte*)"void") ;
 
 }
  else { 
 
 Parser_next( p ) ;
 
 Parser_gen( p , tos2((byte*)" << ") ) ;
 
 Parser_check_types( p , Parser_expression( p ) , typ ) ;
 
return  tos2((byte*)"int") ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_in ) {
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_key_in ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_gen( p , tos2((byte*)", ") ) ;
 
string arr_typ= Parser_expression( p ) ;
 
bool is_map= string_starts_with( arr_typ , tos2((byte*)"map_") ) ;
 
 if ( ! string_starts_with( arr_typ , tos2((byte*)"array_") )  &&  ! is_map ) {
 
 Parser_error( p , tos2((byte*)"`in` requires an array/map") ) ;
 
 }
 ;
 
Type* T= Table_find_type(& /* ? */* p ->table , arr_typ ) ;
 
 if ( ! is_map  &&  ! Type_has_method(& /* ? */* T , tos2((byte*)"contains") ) ) {
 
 Parser_error( p , _STR("%.*s has no method `contains`", arr_typ.len, arr_typ.str) ) ;
 
 }
 ;
 
 if ( is_map ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"_IN_MAP( ") ) ;
 
 }
  else { 
 
 CGen_set_placeholder( p ->cgen , ph , _STR("_IN(%.*s, ", typ.len, typ.str) ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
return  tos2((byte*)"bool") ;
 
 }
 ;
 
 if ( p ->tok == main__Token_righ_shift ) {
 
 Parser_next( p ) ;
 
 Parser_gen( p , tos2((byte*)" >> ") ) ;
 
 Parser_check_types( p , Parser_expression( p ) , typ ) ;
 
return  tos2((byte*)"int") ;
 
 }
 ;
 
 if ( p ->tok == main__Token_dot ) {
 
 while ( p ->tok == main__Token_dot ) {
 
 
 typ  =  Parser_dot( p , typ , ph ) ;
 
 }
 ;
 
 }
 ;
 
 while ( p ->tok == main__Token_plus  ||  p ->tok == main__Token_minus  ||  p ->tok == main__Token_pipe  ||  p ->tok == main__Token_amp  ||  p ->tok == main__Token_xor ) {
 
 
Token tok_op= p ->tok ;
 
bool is_num=string_eq( typ , tos2((byte*)"void*") )  || string_eq( typ , tos2((byte*)"byte*") )  ||  is_number_type ( typ ) ;
 
 Parser_check_space( p , p ->tok ) ;
 
 if ( is_str  &&  tok_op == main__Token_plus ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"string_add(") ) ;
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
  else  if ( is_num ) {
 
 if (string_eq( typ , tos2((byte*)"void*") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , tos2((byte*)"(byte*)") ) ;
 
 }
 ;
 
 Parser_gen( p , Token_str( tok_op ) ) ;
 
 }
  else { 
 
 if ( p ->pref ->translated ) {
 
 Parser_gen( p ,string_add( Token_str( tok_op ) , tos2((byte*)" /*doom hack*/") ) ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_check_types( p , Parser_term( p ) , typ ) ;
 
 if ( is_str  &&  tok_op == main__Token_plus ) {
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 }
 ;
 
 if ( ! p ->pref ->translated  &&  ! is_str  &&  ! is_num ) {
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 if ( tok_op == main__Token_plus ) {
 
 if ( Type_has_method(& /* ? */* T , tos2((byte*)"+") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph ,string_add( typ , tos2((byte*)"_plus(") ) ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 }
  else { 
 
 Parser_error( p , _STR("operator + not defined on `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
  else  if ( tok_op == main__Token_minus ) {
 
 if ( Type_has_method(& /* ? */* T , tos2((byte*)"-") ) ) {
 
 CGen_set_placeholder( p ->cgen , ph , _STR("%.*s_minus(", typ.len, typ.str) ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 }
  else { 
 
 Parser_error( p , _STR("operator - not defined on `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_term(Parser* p) {
 
int line_nr= p ->scanner ->line_nr ;
 
string typ= Parser_unary( p ) ;
 
 if ( p ->tok == main__Token_mul  &&  line_nr != p ->scanner ->line_nr ) {
 
return  typ ;
 
 }
 ;
 
 while ( p ->tok == main__Token_mul  ||  p ->tok == main__Token_div  ||  p ->tok == main__Token_mod ) {
 
 
Token tok= p ->tok ;
 
bool is_div= tok == main__Token_div ;
 
bool is_mod= tok == main__Token_mod ;
 
 Parser_next( p ) ;
 
 Parser_gen( p , Token_str( tok ) ) ;
 
 Parser_fgen( p ,string_add(string_add( tos2((byte*)" ") , Token_str( tok ) ) , tos2((byte*)" ") ) ) ;
 
 if ( is_div  &&  p ->tok == main__Token_number  && string_eq( p ->lit , tos2((byte*)"0") ) ) {
 
 Parser_error( p , tos2((byte*)"division by zero") ) ;
 
 }
 ;
 
 if ( is_mod  &&  ( is_float_type ( typ )  ||  ! is_number_type ( typ ) ) ) {
 
 Parser_error( p , tos2((byte*)"operator .mod requires integer types") ) ;
 
 }
 ;
 
 Parser_check_types( p , Parser_unary( p ) , typ ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_unary(Parser* p) {
 
string typ= tos2((byte*)"") ;
 
Token tok= p ->tok ;
 
 if ( ( tok ==  main__Token_not )) { /* case */
 
 Parser_gen( p , tos2((byte*)"!") ) ;
 
 Parser_check( p , main__Token_not ) ;
 
 typ  =  tos2((byte*)"bool") ;
 
 Parser_bool_expression( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_bit_not )) { /* case */
 
 Parser_gen( p , tos2((byte*)"~") ) ;
 
 Parser_check( p , main__Token_bit_not ) ;
 
 typ  =  Parser_bool_expression( p ) ;
 
 }
 else  { // default:
 
 typ  =  Parser_factor( p ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 string Parser_factor(Parser* p) {
 
string typ= tos2((byte*)"") ;
 
Token tok= p ->tok ;
 
 if ( ( tok ==  main__Token_number )) { /* case */
 
 typ  =  tos2((byte*)"int") ;
 
 if ( ( string_contains( p ->lit , tos2((byte*)".") )  ||  ( string_contains( p ->lit , tos2((byte*)"e") )  ||  string_contains( p ->lit , tos2((byte*)"E") ) ) )  &&  ! ( string_at( p ->lit , 0) == '0'  &&  ( string_at( p ->lit , 1) == 'x'  ||  string_at( p ->lit , 1) == 'X' ) ) ) {
 
 typ  =  tos2((byte*)"f32") ;
 
 }
  else { 
 
u64 v_u64= string_u64( p ->lit ) ;
 
 if ( ((u64)( ((u32)( v_u64 ) ) ) ) < v_u64 ) {
 
 typ  =  tos2((byte*)"u64") ;
 
 }
 ;
 
 }
 ;
 
 if (string_ne( p ->expected_type , tos2((byte*)"") )  &&  ! is_valid_int_const ( p ->lit , p ->expected_type ) ) {
 
 Parser_error( p , _STR("constant `%.*s` overflows `%.*s`", p ->lit.len, p ->lit.str, p ->expected_type.len, p ->expected_type.str) ) ;
 
 }
 ;
 
 Parser_gen( p , p ->lit ) ;
 
 Parser_fgen( p , p ->lit ) ;
 
 }
 else  if ( ( tok ==  main__Token_minus )) { /* case */
 
 Parser_gen( p , tos2((byte*)"-") ) ;
 
 Parser_fgen( p , tos2((byte*)"-") ) ;
 
 Parser_next( p ) ;
 
return  Parser_factor( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_sizeof )) { /* case */
 
 Parser_gen( p , tos2((byte*)"sizeof(") ) ;
 
 Parser_fgen( p , tos2((byte*)"sizeof(") ) ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lpar ) ;
 
string sizeof_typ= Parser_get_type( p ) ;
 
 if ( string_ends_with( sizeof_typ , tos2((byte*)"*") ) ) {
 
 sizeof_typ  = string_add( tos2((byte*)"*") , string_left( sizeof_typ , sizeof_typ .len - 1 ) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 Parser_gen( p , _STR("%.*s)", sizeof_typ.len, sizeof_typ.str) ) ;
 
 Parser_fgen( p , _STR("%.*s)", sizeof_typ.len, sizeof_typ.str) ) ;
 
return  tos2((byte*)"int") ;
 
 }
 else  if ( ( tok ==  main__Token_amp ) ||   ( tok ==  main__Token_dot ) ||   ( tok ==  main__Token_mul )) { /* case */
 
return  Parser_name_expr( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_name )) { /* case */
 
 if (string_eq( p ->lit , tos2((byte*)"map") )  &&  Parser_peek( p ) == main__Token_lsbr ) {
 
return  Parser_map_init( p ) ;
 
 }
 ;
 
 if (string_eq( p ->lit , tos2((byte*)"json") )  &&  Parser_peek( p ) == main__Token_dot ) {
 
return  Parser_js_decode( p ) ;
 
 }
 ;
 
 typ  =  Parser_name_expr( p ) ;
 
return  typ ;
 
 }
 else  if ( ( tok ==  main__Token_key_default )) { /* case */
 
 Parser_next( p ) ;
 
 Parser_next( p ) ;
 
string name= Parser_check_name( p ) ;
 
 if (string_ne( name , tos2((byte*)"T") ) ) {
 
 Parser_error( p , tos2((byte*)"default needs T") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)"default(T)") ) ;
 
 Parser_next( p ) ;
 
return  tos2((byte*)"T") ;
 
 }
 else  if ( ( tok ==  main__Token_lpar )) { /* case */
 
 Parser_gen( p , tos2((byte*)"(") ) ;
 
 Parser_check( p , main__Token_lpar ) ;
 
 typ  =  Parser_bool_expression( p ) ;
 
 if ( ! p ->ptr_cast ) {
 
 Parser_check( p , main__Token_rpar ) ;
 
 }
 ;
 
 p ->ptr_cast  =  0 ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
return  typ ;
 
 }
 else  if ( ( tok ==  main__Token_chartoken )) { /* case */
 
 Parser_char_expr( p ) ;
 
 typ  =  tos2((byte*)"byte") ;
 
return  typ ;
 
 }
 else  if ( ( tok ==  main__Token_str )) { /* case */
 
 Parser_string_expr( p ) ;
 
 typ  =  tos2((byte*)"string") ;
 
return  typ ;
 
 }
 else  if ( ( tok ==  main__Token_key_false )) { /* case */
 
 typ  =  tos2((byte*)"bool") ;
 
 Parser_gen( p , tos2((byte*)"0") ) ;
 
 Parser_fgen( p , tos2((byte*)"false") ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_true )) { /* case */
 
 typ  =  tos2((byte*)"bool") ;
 
 Parser_gen( p , tos2((byte*)"1") ) ;
 
 Parser_fgen( p , tos2((byte*)"true") ) ;
 
 }
 else  if ( ( tok ==  main__Token_lsbr )) { /* case */
 
return  Parser_array_init( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_lcbr )) { /* case */
 
 if ( Parser_peek( p ) == main__Token_str ) {
 
return  Parser_map_init( p ) ;
 
 }
 ;
 
return  Parser_assoc( p ) ;
 
 }
 else  if ( ( tok ==  main__Token_key_if )) { /* case */
 
 typ  =  Parser_if_st( p , 1 , 0 ) ;
 
return  typ ;
 
 }
 else  { // default:
 
Token next= Parser_peek( p ) ;
 
printf( "PREV=%.*s\n", Token_str( p ->prev_tok ).len, Token_str( p ->prev_tok ).str ) ;
 
printf( ".neXT=%.*s\n", Token_str( next ).len, Token_str( next ).str ) ;
 
 Parser_error( p , _STR("unexpected token: `%.*s`", Token_str( p ->tok ).len, Token_str( p ->tok ).str) ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
return  typ ;
 
 
 }
 string Parser_assoc(Parser* p) {
 
 Parser_next( p ) ;
 
string name= Parser_check_name( p ) ;
 
 if ( ! Fn_known_var(& /* ? */* p ->cur_fn , name ) ) {
 
 Parser_error( p , _STR("unknown variable `%.*s`", name.len, name.str) ) ;
 
 }
 ;
 
Var var= Fn_find_var(& /* ? */* p ->cur_fn , name ) ;
 
 Parser_check( p , main__Token_pipe ) ;
 
 Parser_gen( p , _STR("(%.*s){", var .typ.len, var .typ.str) ) ;
 
array_string fields=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 while ( p ->tok != main__Token_rcbr ) {
 
 
string field= Parser_check_name( p ) ;
 
_PUSH(& fields , ( field ), tmp221, string) ;
 
 Parser_gen( p , _STR(".%.*s = ", field.len, field.str) ) ;
 
 Parser_check( p , main__Token_colon ) ;
 
 Parser_bool_expression( p ) ;
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 if ( p ->tok != main__Token_rcbr ) {
 
 Parser_check( p , main__Token_comma ) ;
 
 }
 ;
 
 }
 ;
 
Type* T= Table_find_type(& /* ? */* p ->table , var .typ ) ;
 
 array_Var tmp223 =  T ->fields;
 ;
for (int tmp224 = 0; tmp224 < tmp223 .len; tmp224 ++) {
 Var ffield = ((Var *) tmp223.data)[tmp224];
 
 
string f= ffield .name ;
 
 if (_IN(string,  f ,  fields ) ) {
 
 continue
 ;
 
 }
 ;
 
 Parser_gen( p , _STR(".%.*s = %.*s . %.*s,", f.len, f.str, name.len, name.str, f.len, f.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
 Parser_gen( p , tos2((byte*)"}") ) ;
 
return  var .typ ;
 
 
 }
 void Parser_char_expr(Parser* p) {
 
 Parser_gen( p , _STR("\'%.*s\'", p ->lit.len, p ->lit.str) ) ;
 
 Parser_next( p ) ;
 
 
 }
 string format_str(string str) {
 
 str  =  string_replace( str , tos2((byte*)"\"") , tos2((byte*)"\\\"") ) ;
 
 #ifdef _WIN32
 
 str  =  string_replace( str , tos2((byte*)"\r\n") , tos2((byte*)"\\n") ) ;
 
 #endif
 ;
 
 str  =  string_replace( str , tos2((byte*)"\n") , tos2((byte*)"\\n") ) ;
 
return  str ;
 
 
 }
 void Parser_string_expr(Parser* p) {
 
string str= p ->lit ;
 
 if ( Parser_peek( p ) != main__Token_dollar ) {
 
 Parser_fgen( p , _STR("\'%.*s\'", str.len, str.str) ) ;
 
string f= format_str ( str ) ;
 
 if ( p ->calling_c  ||  ( p ->pref ->translated  && string_eq( p ->mod , tos2((byte*)"main") ) ) ) {
 
 Parser_gen( p , _STR("\"%.*s\"", f.len, f.str) ) ;
 
 }
  else { 
 
 Parser_gen( p , _STR("tos2((byte*)\"%.*s\")", f.len, f.str) ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 return ;
 
 }
 ;
 
 p ->is_alloc  =  1 ;
 
string args= tos2((byte*)"\"") ;
 
string format= tos2((byte*)"\"") ;
 
 Parser_fgen( p , tos2((byte*)"\'") ) ;
 
bool complex_inter= 0 ;
 
 while ( p ->tok == main__Token_str ) {
 
 
 Parser_fgen( p , p ->lit ) ;
 
 p ->lit  =  string_replace( p ->lit , tos2((byte*)"%") , tos2((byte*)"%%") ) ;
 
 format = string_add(format,  format_str ( p ->lit ) ) ;
 
 Parser_next( p ) ;
 
 if ( p ->tok != main__Token_dollar ) {
 
 continue
 ;
 
 }
 ;
 
 Parser_check( p , main__Token_dollar ) ;
 
 if ( Parser_peek( p ) != main__Token_str ) {
 
 Parser_fgen( p , tos2((byte*)"{") ) ;
 
 complex_inter  =  1 ;
 
 }
 ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
string val= CGen_end_tmp( p ->cgen ) ;
 
 val  =  string_trim_space( val ) ;
 
 args = string_add(args,  _STR(", %.*s", val.len, val.str) ) ;
 
 if (string_eq( typ , tos2((byte*)"string") ) ) {
 
 args = string_add(args,  _STR(".len, %.*s.str", val.len, val.str) ) ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"ustring") ) ) {
 
 args = string_add(args,  _STR(".len, %.*s.s.str", val.len, val.str) ) ;
 
 }
 ;
 
bool custom= p ->tok == main__Token_colon ;
 
 if ( custom ) {
 
 format = string_add(format,  tos2((byte*)"%") ) ;
 
 Parser_next( p ) ;
 
 if ( p ->tok == main__Token_dot ) {
 
 format = string_add(format,  tos2((byte*)".") ) ;
 
 Parser_next( p ) ;
 
 }
 ;
 
 format = string_add(format,  p ->lit ) ;
 
 Parser_next( p ) ;
 
 format = string_add(format,  p ->lit ) ;
 
 Parser_next( p ) ;
 
 }
  else { 
 
string f= Parser_typ_to_fmt( p , typ , 0 ) ;
 
 if (string_eq( f , tos2((byte*)"") ) ) {
 
 Parser_error( p , _STR("unhandled sprintf format \"%.*s\" ", typ.len, typ.str) ) ;
 
 }
 ;
 
 format = string_add(format,  f ) ;
 
 }
 ;
 
 }
 ;
 
 if ( complex_inter ) {
 
 Parser_fgen( p , tos2((byte*)"}") ) ;
 
 }
 ;
 
 Parser_fgen( p , tos2((byte*)"\'") ) ;
 
 if ( p ->cgen ->nogen ) {
 
 return ;
 
 }
 ;
 
 #ifndef _WIN32
 
string cur_line= string_trim_space( p ->cgen ->cur_line ) ;
 
 if ( string_contains( cur_line , tos2((byte*)"println (") )  &&  p ->tok != main__Token_plus  &&  ! string_contains( cur_line , tos2((byte*)"string_add") )  &&  ! string_contains( cur_line , tos2((byte*)"eprintln") ) ) {
 
 CGen_resetln( p ->cgen , string_replace( cur_line , tos2((byte*)"println (") , tos2((byte*)"printf(") ) ) ;
 
 Parser_gen( p , _STR("%.*s\\n%.*s", format.len, format.str, args.len, args.str) ) ;
 
 return ;
 
 }
 ;
 
 #endif
 ;
 
 if ( p ->tok == main__Token_not ) {
 
 Parser_check( p , main__Token_not ) ;
 
 Parser_gen( p , _STR("_STR_TMP(%.*s%.*s)", format.len, format.str, args.len, args.str) ) ;
 
 }
  else { 
 
 Parser_gen( p , _STR("_STR(%.*s%.*s)", format.len, format.str, args.len, args.str) ) ;
 
 }
 ;
 
 
 }
 string Parser_map_init(Parser* p) {
 
string keys_gen= tos2((byte*)"") ;
 
string vals_gen= tos2((byte*)"") ;
 
string val_type= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_lcbr ) {
 
 Parser_check( p , main__Token_lcbr ) ;
 
int i= 0 ;
 
 while (1) { 
 
string key= p ->lit ;
 
 keys_gen = string_add(keys_gen,  _STR("tos2(\"%.*s\"), ", key.len, key.str) ) ;
 
 Parser_check( p , main__Token_str ) ;
 
 Parser_check( p , main__Token_colon ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string t= Parser_bool_expression( p ) ;
 
 if ( i == 0 ) {
 
 val_type  =  t ;
 
 }
 ;
 
 i ++ ;
 
 if (string_ne( val_type , t ) ) {
 
 if ( ! Parser_check_types_no_throw( p , val_type , t ) ) {
 
 Parser_error( p , _STR("bad map element type `%.*s` instead of `%.*s`", val_type.len, val_type.str, t.len, t.str) ) ;
 
 }
 ;
 
 }
 ;
 
string val_expr= CGen_end_tmp( p ->cgen ) ;
 
 vals_gen = string_add(vals_gen,  _STR("%.*s, ", val_expr.len, val_expr.str) ) ;
 
 if ( p ->tok == main__Token_rcbr ) {
 
 Parser_check( p , main__Token_rcbr ) ;
 
 break
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_check( p , main__Token_comma ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen( p ,string_add( _STR("new_map_init(%d, sizeof(%.*s), ", i, val_type.len, val_type.str) , _STR("(string[]){ %.*s }, (%.*s []){ %.*s } )", keys_gen.len, keys_gen.str, val_type.len, val_type.str, vals_gen.len, vals_gen.str) ) ) ;
 
string typ= _STR("map_%.*s", val_type.len, val_type.str) ;
 
return  typ ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_lsbr ) ;
 
string key_type= Parser_check_name( p ) ;
 
 if (string_ne( key_type , tos2((byte*)"string") ) ) {
 
 Parser_error( p , tos2((byte*)"only string key maps allowed for now") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 val_type  =  Parser_check_name( p ) ;
 
 if ( ! Table_known_type(& /* ? */* p ->table , val_type ) ) {
 
 Parser_error( p , _STR("map init unknown type \"%.*s\"", val_type.len, val_type.str) ) ;
 
 }
 ;
 
string typ= _STR("map_%.*s", val_type.len, val_type.str) ;
 
 Parser_register_map( p , typ ) ;
 
 Parser_gen( p , _STR("new_map(1, sizeof(%.*s))", val_type.len, val_type.str) ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
return  typ ;
 
 
 }
 string Parser_array_init(Parser* p) {
 
 p ->is_alloc  =  1 ;
 
 Parser_check( p , main__Token_lsbr ) ;
 
bool is_integer= p ->tok == main__Token_number ;
 
bool is_const_len= 0 ;
 
 if ( p ->tok == main__Token_name ) {
 
Var c= Table_find_const(& /* ? */* p ->table , Parser_prepend_mod(& /* ? */* p , p ->lit ) ) ;
 
 if (string_ne( c .name , tos2((byte*)"") )  && string_eq( c .typ , tos2((byte*)"int") )  &&  Parser_peek( p ) == main__Token_rsbr  &&  ! p ->inside_const ) {
 
 is_integer  =  1 ;
 
 is_const_len  =  1 ;
 
 }
 ;
 
 }
 ;
 
string lit= p ->lit ;
 
string typ= tos2((byte*)"") ;
 
int new_arr_ph= CGen_add_placeholder( p ->cgen ) ;
 
int i= 0 ;
 
int pos= p ->cgen ->cur_line .len ;
 
 while ( p ->tok != main__Token_rsbr ) {
 
 
string val_typ= Parser_bool_expression( p ) ;
 
 if ( i == 0 ) {
 
 typ  =  val_typ ;
 
 if ( is_integer  &&  p ->tok == main__Token_rsbr  &&  Parser_peek( p ) == main__Token_name ) {
 
byte nextc= string_at( p ->scanner ->text , p ->scanner ->pos + 1) ;
 
 if ( ! byte_is_space( nextc ) ) {
 
 Parser_check( p , main__Token_rsbr ) ;
 
string name= Parser_check_name( p ) ;
 
 if ( Table_known_type(& /* ? */* p ->table , name ) ) {
 
 CGen_resetln( p ->cgen , tos2((byte*)"") ) ;
 
 Parser_gen( p , tos2((byte*)"STRUCT_DEFAULT_VALUE") ) ;
 
 if ( is_const_len ) {
 
return  _STR("[%.*s__%.*s]%.*s", p ->mod.len, p ->mod.str, lit.len, lit.str, name.len, name.str) ;
 
 }
 ;
 
return  _STR("[%.*s]%.*s", lit.len, lit.str, name.len, name.str) ;
 
 }
  else { 
 
 Parser_error( p , _STR("bad type `%.*s`", name.len, name.str) ) ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
 if (string_ne( val_typ , typ ) ) {
 
 if ( ! Parser_check_types_no_throw( p , val_typ , typ ) ) {
 
 Parser_error( p , _STR("bad array element type `%.*s` instead of `%.*s`", val_typ.len, val_typ.str, typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok != main__Token_rsbr  &&  p ->tok != main__Token_semicolon ) {
 
 Parser_gen( p , tos2((byte*)", ") ) ;
 
 Parser_check( p , main__Token_comma ) ;
 
 Parser_fspace( p ) ;
 
 }
 ;
 
 i ++ ;
 
 if ( i == 1  &&  p ->tok == main__Token_semicolon ) {
 
 Parser_check_space( p , main__Token_semicolon ) ;
 
string val= string_right( p ->cgen ->cur_line , pos ) ;
 
 CGen_resetln( p ->cgen , string_left( p ->cgen ->cur_line , pos ) ) ;
 
 if ( 0  && string_eq( string_trim_space( val ) , tos2((byte*)"0") ) ) {
 
 Parser_gen( p , tos2((byte*)"array_repeat( & V_ZERO, ") ) ;
 
 }
  else { 
 
string tmp= Parser_get_tmp( p ) ;
 
 CGen_insert_before( p ->cgen , _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len, tmp.str, val.len, val.str) ) ;
 
 Parser_gen( p , _STR("array_repeat(&%.*s, ", tmp.len, tmp.str) ) ;
 
 }
 ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"int") ) ;
 
 Parser_gen( p , _STR(", sizeof(%.*s) )", typ.len, typ.str) ) ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
return  _STR("array_%.*s", typ.len, typ.str) ;
 
 }
 ;
 
 }
 ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 if ( p ->tok != main__Token_name  &&  i == 0 ) {
 
 Parser_error( p , tos2((byte*)"specify array type: `[]typ` instead of `[]`") ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_name  &&  i == 0 ) {
 
 typ  =  Parser_get_type( p ) ;
 
 }
 ;
 
bool no_alloc= p ->tok == main__Token_not ;
 
 if ( no_alloc ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
bool is_fixed_size= p ->tok == main__Token_not ;
 
 if ( is_fixed_size ) {
 
 Parser_next( p ) ;
 
 Parser_gen( p , tos2((byte*)" }") ) ;
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 if ( p ->inside_const ) {
 
 CGen_set_placeholder( p ->cgen , new_arr_ph , tos2((byte*)"{ ") ) ;
 
 }
  else { 
 
 CGen_set_placeholder( p ->cgen , new_arr_ph , _STR("(%.*s[]) { ", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
return  _STR("[%d]%.*s", i, typ.len, typ.str) ;
 
 }
 ;
 
string new_arr= tos2((byte*)"new_array_from_c_array") ;
 
 if ( no_alloc ) {
 
 new_arr = string_add(new_arr,  tos2((byte*)"_no_alloc") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)" })") ) ;
 
 if ( ! Parser_first_pass(& /* ? */* p ) ) {
 
 if ( i == 0 ) {
 
 CGen_set_placeholder( p ->cgen , new_arr_ph , _STR("%.*s(%d, %d, sizeof(%.*s), (%.*s[]) {EMPTY_STRUCT_INIT ", new_arr.len, new_arr.str, i, i, typ.len, typ.str, typ.len, typ.str) ) ;
 
 }
  else { 
 
 CGen_set_placeholder( p ->cgen , new_arr_ph , _STR("%.*s(%d, %d, sizeof(%.*s), (%.*s[]) { ", new_arr.len, new_arr.str, i, i, typ.len, typ.str, typ.len, typ.str) ) ;
 
 }
 ;
 
 }
 ;
 
 typ  =  _STR("array_%.*s", typ.len, typ.str) ;
 
 Parser_register_array( p , typ ) ;
 
return  typ ;
 
 
 }
 string Parser_struct_init(Parser* p, string typ, bool is_c_struct_init) {
 
 p ->is_struct_init  =  1 ;
 
 Parser_next( p ) ;
 
 strings__Builder_cut(& /* ? */ p ->scanner ->fmt_out , typ .len ) ;
 
bool ptr= string_contains( typ , tos2((byte*)"*") ) ;
 
 if (string_eq( typ , tos2((byte*)"tm") ) ) {
  
 string tmp265 =  tos2((byte*)""); 

array_set(&/*q*/ p ->cgen ->lines , p ->cgen ->lines .len - 1 , & tmp265) ;
  
 string tmp266 =  tos2((byte*)""); 

array_set(&/*q*/ p ->cgen ->lines , p ->cgen ->lines .len - 2 , & tmp266) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 if ( ! ptr ) {
 
 if ( p ->is_c_struct_init ) {
 
 Parser_gen( p , _STR("(struct %.*s) {", typ.len, typ.str) ) ;
 
 p ->is_c_struct_init  =  0 ;
 
 }
  else { 
 
 Parser_gen( p , _STR("(%.*s) {", typ.len, typ.str) ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( p ->tok == main__Token_not ) {
 
 Parser_next( p ) ;
 
 Parser_gen( p , tos2((byte*)"0") ) ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
return  typ ;
 
 }
 ;
 
string no_star= string_replace( typ , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 Parser_gen( p , _STR("ALLOC_INIT(%.*s, {", no_star.len, no_star.str) ) ;
 
 }
 ;
 
bool did_gen_something= 0 ;
 
array_string inited_fields=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
Token peek= Parser_peek( p ) ;
 
 if ( peek == main__Token_colon  ||  p ->tok == main__Token_rcbr ) {
 
Type* t= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 while ( p ->tok != main__Token_rcbr ) {
 
 
string field= Parser_check_name( p ) ;
 
 if ( ! Type_has_field(& /* ? */* t , field ) ) {
 
 Parser_error( p , _STR("`%.*s` has no field `%.*s`", t ->name.len, t ->name.str, field.len, field.str) ) ;
 
 }
 ;
 
Var f= Type_find_field(& /* ? */* t , field ) ;
 
_PUSH(& inited_fields , ( field ), tmp274, string) ;
 
 Parser_gen( p , _STR(".%.*s = ", field.len, field.str) ) ;
 
 Parser_check( p , main__Token_colon ) ;
 
 Parser_fspace( p ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , f .typ ) ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 if ( p ->tok != main__Token_rcbr ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 did_gen_something  =  1 ;
 
 }
 ;
 
 if ( t ->fields .len != inited_fields .len  &&  inited_fields .len > 0 ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 array_Var tmp275 =  t ->fields ;
 ;
for (int i = 0; i < tmp275 .len; i ++) {
 Var field = ((Var *) tmp275 . data)[i];
 
 
 if ( array_string_contains( inited_fields , field .name ) ) {
 
 continue
 ;
 
 }
 ;
 
string field_typ= field .typ ;
 
 if ( ! p ->builtin_mod  &&  string_ends_with( field_typ , tos2((byte*)"*") )  &&  string_contains( field_typ , tos2((byte*)"Cfg") ) ) {
 
 Parser_error( p , _STR("pointer field `%.*s.%.*s` must be initialized", typ.len, typ.str, field .name.len, field .name.str) ) ;
 
 }
 ;
 
string def_val= type_default ( field_typ ) ;
 
 if (string_ne( def_val , tos2((byte*)"") )  && string_ne( def_val , tos2((byte*)"STRUCT_DEFAULT_VALUE") ) ) {
 
 Parser_gen( p , _STR(".%.*s = %.*s", field .name.len, field .name.str, def_val.len, def_val.str) ) ;
 
 if ( i != t ->fields .len - 1 ) {
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 }
 ;
 
 }
 ;
 
 did_gen_something  =  1 ;
 
 }
 ;
 
 }
  else { 
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 if ( T ->fields .len == 0  && string_ne( T ->parent , tos2((byte*)"") ) ) {
 
 T  =  Table_find_type(& /* ? */* p ->table , T ->parent ) ;
 
 }
 ;
 
 array_Var tmp279 =  T ->fields ;
 ;
for (int i = 0; i < tmp279 .len; i ++) {
 Var ffield = ((Var *) tmp279 . data)[i];
 
 
string expr_typ= Parser_bool_expression( p ) ;
 
 if ( ! Parser_check_types_no_throw( p , expr_typ , ffield .typ ) ) {
 
 Parser_error( p , _STR("field value #%d `%.*s` has type `%.*s`, got `%.*s` ", i + 1, ffield .name.len, ffield .name.str, ffield .typ.len, ffield .typ.str, expr_typ.len, expr_typ.str) ) ;
 
 }
 ;
 
 if ( i < T ->fields .len - 1 ) {
 
 if ( p ->tok != main__Token_comma ) {
 
 Parser_error( p , _STR("too few values in `%.*s` literal (%d instead of %d)", typ.len, typ.str, i + 1, T ->fields .len) ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)",") ) ;
 
 Parser_next( p ) ;
 
 }
 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_next( p ) ;
 
 }
 ;
 
 if ( p ->tok != main__Token_rcbr ) {
 
 Parser_error( p , _STR("too many fields initialized: `%.*s` has %d field(s)", typ.len, typ.str, T ->fields .len) ) ;
 
 }
 ;
 
 did_gen_something  =  1 ;
 
 }
 ;
 
 if ( ! did_gen_something ) {
 
 Parser_gen( p , tos2((byte*)"EMPTY_STRUCT_INIT") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)"}") ) ;
 
 if ( ptr ) {
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rcbr ) ;
 
 p ->is_struct_init  =  0 ;
 
return  typ ;
 
 
 }
 string Parser_cast(Parser* p, string typ) {
 
 Parser_next( p ) ;
 
int pos= CGen_add_placeholder( p ->cgen ) ;
 
 if ( p ->tok == main__Token_rpar ) {
 
 p ->ptr_cast  =  1 ;
 
 Parser_next( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lpar ) ;
 
 p ->expected_type  =  typ ;
 
string expr_typ= Parser_bool_expression( p ) ;
 
 p ->expected_type  =  tos2((byte*)"") ;
 
bool is_byteptr=string_eq( expr_typ , tos2((byte*)"byte*") )  || string_eq( expr_typ , tos2((byte*)"byteptr") ) ;
 
bool is_bytearr=string_eq( expr_typ , tos2((byte*)"array_byte") ) ;
 
 if (string_eq( typ , tos2((byte*)"string") ) ) {
 
 if ( is_byteptr  ||  is_bytearr ) {
 
 if ( p ->tok == main__Token_comma ) {
 
 Parser_check( p , main__Token_comma ) ;
 
 CGen_set_placeholder( p ->cgen , pos , tos2((byte*)"tos(") ) ;
 
 if ( is_bytearr ) {
 
 Parser_gen( p , tos2((byte*)".data") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)", ") ) ;
 
 Parser_check_types( p , Parser_expression( p ) , tos2((byte*)"int") ) ;
 
 }
  else { 
 
 if ( is_bytearr ) {
 
 Parser_gen( p , tos2((byte*)".data") ) ;
 
 }
 ;
 
 CGen_set_placeholder( p ->cgen , pos , tos2((byte*)"tos2(") ) ;
 
 }
 ;
 
 }
  else  if (string_eq( expr_typ , tos2((byte*)"int") ) ) {
 
 Parser_error( p , _STR("cannot cast `%.*s` to `%.*s`, use `str()` method instead", expr_typ.len, expr_typ.str, typ.len, typ.str) ) ;
 
 }
  else { 
 
 Parser_error( p , _STR("cannot cast `%.*s` to `%.*s`", expr_typ.len, expr_typ.str, typ.len, typ.str) ) ;
 
 }
 ;
 
 }
  else { 
 
 CGen_set_placeholder( p ->cgen , pos , _STR("(%.*s)(", typ.len, typ.str) ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 Parser_gen( p , tos2((byte*)")") ) ;
 
return  typ ;
 
 
 }
 string Parser_get_tmp(Parser* p) {
 
 p ->tmp_cnt ++ ;
 
return  _STR("tmp%d", p ->tmp_cnt) ;
 
 
 }
 int Parser_get_tmp_counter(Parser* p) {
 
 p ->tmp_cnt ++ ;
 
return  p ->tmp_cnt ;
 
 
 }
 string os_name_to_ifdef(string name) {
 
 if ( string_eq( name,  tos2((byte*)"windows") )) { /* case */
 
return  tos2((byte*)"_WIN32") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"mac") )) { /* case */
 
return  tos2((byte*)"__APPLE__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"linux") )) { /* case */
 
return  tos2((byte*)"__linux__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"freebsd") )) { /* case */
 
return  tos2((byte*)"__FreeBSD__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"openbsd") )) { /* case */
 
return  tos2((byte*)"__OpenBSD__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"netbsd") )) { /* case */
 
return  tos2((byte*)"__NetBSD__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"dragonfly") )) { /* case */
 
return  tos2((byte*)"__DragonFly__") ;
 
 }
 else  if ( string_eq( name,  tos2((byte*)"msvc") )) { /* case */
 
return  tos2((byte*)"_MSC_VER") ;
 
 }
 ;
 
 v_panic ( _STR("bad os ifdef name \"%.*s\"", name.len, name.str) ) ;
 
return  tos2((byte*)"") ;
 
 
 }
 string Parser_if_st(Parser* p, bool is_expr, int elif_depth) {
 
 if ( is_expr ) {
 
 if ( Parser_fileis(& /* ? */* p , tos2((byte*)"if_expr") ) ) {
 
 println ( tos2((byte*)"IF EXPR") ) ;
 
 }
 ;
 
 p ->inside_if_expr  =  1 ;
 
 Parser_gen( p , tos2((byte*)"(") ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)"if (") ) ;
 
 Parser_fgen( p , tos2((byte*)"if ") ) ;
 
 }
 ;
 
 Parser_next( p ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"bool") ) ;
 
 if ( is_expr ) {
 
 Parser_gen( p , tos2((byte*)") ? (") ) ;
 
 }
  else { 
 
 Parser_genln( p , tos2((byte*)") {") ) ;
 
 }
 ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
string typ= tos2((byte*)"") ;
 
 if ( p ->tok == main__Token_key_if  &&  p ->inside_if_expr ) {
 
 typ  =  Parser_factor( p ) ;
 
 Parser_next( p ) ;
 
 }
  else { 
 
 typ  =  Parser_statements( p ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_else ) {
 
 Parser_fgenln( p , tos2((byte*)"") ) ;
 
 Parser_check( p , main__Token_key_else ) ;
 
 Parser_fspace( p ) ;
 
 if ( p ->tok == main__Token_key_if ) {
 
 if ( is_expr ) {
 
 Parser_gen( p , tos2((byte*)") : (") ) ;
 
return  Parser_if_st( p , is_expr , elif_depth + 1 ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)" else ") ) ;
 
return  Parser_if_st( p , is_expr , 0 ) ;
 
 }
 ;
 
 }
 ;
 
 if ( is_expr ) {
 
 Parser_gen( p , tos2((byte*)") : (") ) ;
 
 }
  else { 
 
 Parser_genln( p , tos2((byte*)" else { ") ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 typ  =  Parser_statements( p ) ;
 
 p ->inside_if_expr  =  0 ;
 
 if ( is_expr ) {
 
 Parser_gen( p , strings__repeat ( ')' , elif_depth + 1 ) ) ;
 
 }
 ;
 
return  typ ;
 
 }
 ;
 
 p ->inside_if_expr  =  0 ;
 
 if ( Parser_fileis(& /* ? */* p , tos2((byte*)"test_test") ) ) {
 
printf( "if ret typ=\"%.*s\" line=%d\n", typ.len, typ.str, p ->scanner ->line_nr ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 void Parser_for_st(Parser* p) {
 
 Parser_check( p , main__Token_key_for ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 p ->for_expr_cnt ++ ;
 
Token next_tok= Parser_peek( p ) ;
 
 Fn_open_scope( p ->cur_fn ) ;
 
 if ( p ->tok == main__Token_lcbr ) {
 
 Parser_gen( p , tos2((byte*)"while (1) {") ) ;
 
 }
  else  if ( p ->tok == main__Token_key_mut ) {
 
 Parser_error( p , tos2((byte*)"`mut` is not required in for loops") ) ;
 
 }
  else  if ( next_tok == main__Token_decl_assign  ||  next_tok == main__Token_assign  ||  p ->tok == main__Token_semicolon ) {
 
 Parser_genln( p , tos2((byte*)"for (") ) ;
 
 if ( next_tok == main__Token_decl_assign ) {
 
 Parser_var_decl( p ) ;
 
 }
  else  if ( p ->tok != main__Token_semicolon ) {
 
 Parser_statement( p , 0 ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_semicolon ) ;
 
 Parser_gen( p , tos2((byte*)" ; ") ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 if ( p ->tok != main__Token_semicolon ) {
 
 Parser_bool_expression( p ) ;
 
 }
 ;
 
 Parser_check( p , main__Token_semicolon ) ;
 
 Parser_gen( p , tos2((byte*)" ; ") ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 if ( p ->tok != main__Token_lcbr ) {
 
 Parser_statement( p , 0 ) ;
 
 }
 ;
 
 Parser_genln( p , tos2((byte*)") { ") ) ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_comma ) {
 
string i= Parser_check_name( p ) ;
 
 Parser_check( p , main__Token_comma ) ;
 
string val= Parser_check_name( p ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_key_in ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
string tmp= Parser_get_tmp( p ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
bool is_arr= string_starts_with( typ , tos2((byte*)"array_") ) ;
 
bool is_map= string_starts_with( typ , tos2((byte*)"map_") ) ;
 
bool is_str=string_eq( typ , tos2((byte*)"string") ) ;
 
 if ( ! is_arr  &&  ! is_str  &&  ! is_map ) {
 
 Parser_error( p , _STR("cannot range over type `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
string expr= CGen_end_tmp( p ->cgen ) ;
 
 Parser_genln( p , _STR("%.*s %.*s = %.*s ;", typ.len, typ.str, tmp.len, tmp.str, expr.len, expr.str) ) ;
 
int pad= ( is_arr ) ? ( 6 ) : ( 4 ) ;
 
string var_typ= string_right( typ , pad ) ;
 
Var val_var= (Var) { .name =  val , .typ =  var_typ , .ptr =  string_contains( typ , tos2((byte*)"*") ) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
 Parser_register_var( p , val_var ) ;
 
 if ( is_arr  ||  is_str ) {
 
Var i_var= (Var) { .name =  i , .typ =  tos2((byte*)"int") , .is_mut =  1 , .is_changed =  1 , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .scope_level = 0 } ;
 
 Parser_register_var( p , i_var ) ;
 
 Parser_genln( p , _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {", i.len, i.str, i.len, i.str, tmp.len, tmp.str, i.len, i.str) ) ;
 
 Parser_genln( p , _STR("%.*s %.*s = ((%.*s *) %.*s . data)[%.*s];", var_typ.len, var_typ.str, val.len, val.str, var_typ.len, var_typ.str, tmp.len, tmp.str, i.len, i.str) ) ;
 
 }
  else  if ( is_map ) {
 
Var i_var= (Var) { .name =  i , .typ =  tos2((byte*)"string") , .is_mut =  1 , .is_changed =  1 , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .scope_level = 0 } ;
 
 Parser_register_var( p , i_var ) ;
 
 Parser_genln( p , _STR("array_string keys_%.*s = map_keys(& %.*s ); ", tmp.len, tmp.str, tmp.len, tmp.str) ) ;
 
 Parser_genln( p , _STR("for (int l = 0; l < keys_%.*s .len; l++) {", tmp.len, tmp.str) ) ;
 
 Parser_genln( p , _STR("  string %.*s = ((string*)keys_%.*s .data)[l];", i.len, i.str, tmp.len, tmp.str) ) ;
 
string def= type_default ( typ ) ;
 
 if (string_eq( def , tos2((byte*)"STRUCT_DEFAULT_VALUE") ) ) {
 
 def  =  tos2((byte*)"{0}") ;
 
 }
 ;
 
 Parser_genln( p , _STR("%.*s %.*s = %.*s; map_get(%.*s, %.*s, & %.*s);", var_typ.len, var_typ.str, val.len, val.str, def.len, def.str, tmp.len, tmp.str, i.len, i.str, val.len, val.str) ) ;
 
 }
 ;
 
 }
  else  if ( Parser_peek( p ) == main__Token_key_in ) {
 
string val= Parser_check_name( p ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 Parser_check( p , main__Token_key_in ) ;
 
 Parser_fspace( p ) ;
 
string tmp= Parser_get_tmp( p ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
string expr= CGen_end_tmp( p ->cgen ) ;
 
bool is_range= p ->tok == main__Token_dotdot ;
 
string range_end= tos2((byte*)"") ;
 
 if ( is_range ) {
 
 Parser_check_types( p , typ , tos2((byte*)"int") ) ;
 
 Parser_check_space( p , main__Token_dotdot ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"int") ) ;
 
 range_end  =  CGen_end_tmp( p ->cgen ) ;
 
 }
 ;
 
bool is_arr= string_contains( typ , tos2((byte*)"array") ) ;
 
bool is_str=string_eq( typ , tos2((byte*)"string") ) ;
 
 if ( ! is_arr  &&  ! is_str  &&  ! is_range ) {
 
 Parser_error( p , _STR("cannot range over type `%.*s`", typ.len, typ.str) ) ;
 
 }
 ;
 
 Parser_genln( p , _STR("%.*s %.*s = %.*s;", typ.len, typ.str, tmp.len, tmp.str, expr.len, expr.str) ) ;
 
string var_type= tos2((byte*)"") ;
 
 if ( is_arr ) {
 
 var_type  =  string_right( typ , 6 ) ;
 
 }
  else  if ( is_str ) {
 
 var_type  =  tos2((byte*)"byte") ;
 
 }
  else  if ( is_range ) {
 
 var_type  =  tos2((byte*)"int") ;
 
 }
 ;
 
Var val_var= (Var) { .name =  val , .typ =  var_type , .ptr =  string_contains( typ , tos2((byte*)"*") ) , .is_changed =  1 , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .scope_level = 0 } ;
 
 Parser_register_var( p , val_var ) ;
 
string i= Parser_get_tmp( p ) ;
 
 if ( is_range ) {
 
 Parser_genln( p , _STR(";\nfor (int %.*s = %.*s; %.*s < %.*s; %.*s++) {", i.len, i.str, tmp.len, tmp.str, i.len, i.str, range_end.len, range_end.str, i.len, i.str) ) ;
 
 }
  else { 
 
 Parser_genln( p , _STR(";\nfor (int %.*s = 0; %.*s < %.*s .len; %.*s ++) {", i.len, i.str, i.len, i.str, tmp.len, tmp.str, i.len, i.str) ) ;
 
 }
 ;
 
 if ( is_arr ) {
 
 Parser_genln( p , _STR("%.*s %.*s = ((%.*s *) %.*s.data)[%.*s];", var_type.len, var_type.str, val.len, val.str, var_type.len, var_type.str, tmp.len, tmp.str, i.len, i.str) ) ;
 
 }
  else  if ( is_str ) {
 
 Parser_genln( p , _STR("%.*s %.*s = ((%.*s *) %.*s.str)[%.*s];", var_type.len, var_type.str, val.len, val.str, var_type.len, var_type.str, tmp.len, tmp.str, i.len, i.str) ) ;
 
 }
  else  if ( is_range ) {
 
 Parser_genln( p , _STR("%.*s %.*s = %.*s;", var_type.len, var_type.str, val.len, val.str, i.len, i.str) ) ;
 
 }
 ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)"while (") ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"bool") ) ;
 
 Parser_genln( p , tos2((byte*)") {") ) ;
 
 }
 ;
 
 Parser_fspace( p ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
 Parser_genln( p , tos2((byte*)"") ) ;
 
 Parser_statements( p ) ;
 
 Parser_close_scope( p ) ;
 
 p ->for_expr_cnt -- ;
 
 
 }
 void Parser_switch_statement(Parser* p) {
 
 if ( p ->tok == main__Token_key_switch ) {
 
 Parser_check( p , main__Token_key_switch ) ;
 
 }
  else { 
 
 Parser_check( p , main__Token_key_match ) ;
 
 }
 ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
string expr= CGen_end_tmp( p ->cgen ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
int i= 0 ;
 
 while ( p ->tok == main__Token_key_case  ||  p ->tok == main__Token_key_default  ||  Parser_peek( p ) == main__Token_arrow  ||  p ->tok == main__Token_key_else ) {
 
 
 if ( p ->tok == main__Token_key_default  ||  p ->tok == main__Token_key_else ) {
 
 Parser_genln( p , tos2((byte*)"else  { // default:") ) ;
 
 if ( p ->tok == main__Token_key_default ) {
 
 Parser_check( p , main__Token_key_default ) ;
 
 Parser_check( p , main__Token_colon ) ;
 
 }
  else { 
 
 Parser_check( p , main__Token_key_else ) ;
 
 Parser_check( p , main__Token_arrow ) ;
 
 }
 ;
 
 Parser_statements( p ) ;
 
 break
 ;
 
 }
 ;
 
 if ( i > 0 ) {
 
 Parser_gen( p , tos2((byte*)"else ") ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)"if (") ) ;
 
bool got_comma= 0 ;
 
 while (1) { 
 
 if ( got_comma ) {
 
 Parser_gen( p , tos2((byte*)") ||  ") ) ;
 
 }
 ;
 
 if (string_eq( typ , tos2((byte*)"string") ) ) {
 
 Parser_gen( p , _STR("string_eq(%.*s, ", expr.len, expr.str) ) ;
 
 }
  else { 
 
 Parser_gen( p , _STR("(%.*s == ", expr.len, expr.str) ) ;
 
 }
 ;
 
 if ( p ->tok == main__Token_key_case  ||  p ->tok == main__Token_key_default ) {
 
 Parser_check( p , p ->tok ) ;
 
 }
 ;
 
 Parser_bool_expression( p ) ;
 
 if ( p ->tok != main__Token_comma ) {
 
 break
 ;
 
 }
 ;
 
 Parser_check( p , main__Token_comma ) ;
 
 got_comma  =  1 ;
 
 }
 ;
 
 if ( p ->tok == main__Token_colon ) {
 
 Parser_check( p , main__Token_colon ) ;
 
 }
  else { 
 
 Parser_check( p , main__Token_arrow ) ;
 
 }
 ;
 
 Parser_gen( p , tos2((byte*)")) {") ) ;
 
 Parser_genln( p , tos2((byte*)"/* case */") ) ;
 
 Parser_statements( p ) ;
 
 i ++ ;
 
 }
 ;
 
 
 }
 void Parser_assert_statement(Parser* p) {
 
 if ( Parser_first_pass(& /* ? */* p ) ) {
 
 return ;
 
 }
 ;
 
 Parser_check( p , main__Token_key_assert ) ;
 
 Parser_fspace( p ) ;
 
string tmp= Parser_get_tmp( p ) ;
 
 Parser_gen( p , _STR("bool %.*s = ", tmp.len, tmp.str) ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"bool") ) ;
 
string filename= string_replace( p ->file_path , tos2((byte*)"\\") , tos2((byte*)"\\\\") ) ;
 
 Parser_genln( p , _STR(";\n \nif (!%.*s) {\n  println(tos2(\"\\x1B[31mFAILED: %.*s() in %.*s:%d\\x1B[0m\"));\ng_test_ok = 0 ; \n	// TODO\n	// Maybe print all vars in a test function if it fails? \n} \nelse { \n  //puts(\"\\x1B[32mPASSED: %.*s()\\x1B[0m\");\n}", tmp.len, tmp.str, p ->cur_fn ->name.len, p ->cur_fn ->name.str, filename.len, filename.str, p ->scanner ->line_nr, p ->cur_fn ->name.len, p ->cur_fn ->name.str) ) ;
 
 
 }
 void Parser_return_st(Parser* p) {
 
 Parser_check( p , main__Token_key_return ) ;
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
bool fn_returns=string_ne( p ->cur_fn ->typ , tos2((byte*)"void") ) ;
 
 if ( fn_returns ) {
 
 if ( p ->tok == main__Token_rcbr ) {
 
 Parser_error( p , _STR("`%.*s` needs to return `%.*s`", p ->cur_fn ->name.len, p ->cur_fn ->name.str, p ->cur_fn ->typ.len, p ->cur_fn ->typ.str) ) ;
 
 }
  else { 
 
int ph= CGen_add_placeholder( p ->cgen ) ;
 
string expr_type= Parser_bool_expression( p ) ;
 
 if ( string_ends_with( p ->cur_fn ->typ , expr_type )  &&  string_starts_with( p ->cur_fn ->typ , tos2((byte*)"Option_") ) ) {
 
string tmp= Parser_get_tmp( p ) ;
 
string ret= string_right( p ->cgen ->cur_line , ph ) ;
 
 p ->cgen ->cur_line  =  _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len, expr_type.str, tmp.len, tmp.str, expr_type.len, expr_type.str, ret.len, ret.str) ;
 
 CGen_resetln( p ->cgen , _STR("%.*s %.*s = OPTION_CAST(%.*s)(%.*s);", expr_type.len, expr_type.str, tmp.len, tmp.str, expr_type.len, expr_type.str, ret.len, ret.str) ) ;
 
 Parser_gen( p , _STR("return opt_ok(&%.*s, sizeof(%.*s))", tmp.len, tmp.str, expr_type.len, expr_type.str) ) ;
 
 }
  else { 
 
string ret= string_right( p ->cgen ->cur_line , ph ) ;
 
 p ->cgen ;
 
 ( p ->cur_fn ->defer_text ) ; 
 
 if (string_eq( p ->cur_fn ->defer_text , tos2((byte*)"") )  || string_eq( expr_type , tos2((byte*)"void*") ) ) {
 
 CGen_resetln( p ->cgen , _STR("return %.*s", ret.len, ret.str) ) ;
 
 }
  else { 
 
string tmp= Parser_get_tmp( p ) ;
 
 CGen_resetln( p ->cgen , _STR("%.*s %.*s = %.*s;\n", expr_type.len, expr_type.str, tmp.len, tmp.str, ret.len, ret.str) ) ;
 
 Parser_genln( p , p ->cur_fn ->defer_text ) ;
 
 Parser_genln( p , _STR("return %.*s;", tmp.len, tmp.str) ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_check_types( p , expr_type , p ->cur_fn ->typ ) ;
 
 }
 ;
 
 }
  else { 
 
 if ( ! p ->is_vweb  &&  ( p ->tok == main__Token_name  ||  p ->tok == main__Token_number  ||  p ->tok == main__Token_str ) ) {
 
 Parser_error( p , _STR("function `%.*s` should not return a value", p ->cur_fn ->name.len, p ->cur_fn ->name.str) ) ;
 
 }
 ;
 
 if (string_eq( p ->cur_fn ->name , tos2((byte*)"main") ) ) {
 
 Parser_gen( p , tos2((byte*)"return 0") ) ;
 
 }
  else { 
 
 Parser_gen( p , tos2((byte*)"return") ) ;
 
 }
 ;
 
 }
 ;
 
 p ->returns  =  1 ;
 
 
 }
 string prepend_mod(string mod, string name) {
 
return  _STR("%.*s__%.*s", mod.len, mod.str, name.len, name.str) ;
 
 
 }
 string Parser_prepend_mod(Parser* p, string name) {
 
return  prepend_mod ( p ->mod , name ) ;
 
 
 }
 void Parser_go_statement(Parser* p) {
 
 Parser_check( p , main__Token_key_go ) ;
 
 if ( Parser_peek( p ) == main__Token_dot ) {
 
string var_name= p ->lit ;
 
Var v= Fn_find_var(& /* ? */* p ->cur_fn , var_name ) ;
 
 Fn_mark_var_used(& /* ? */* p ->cur_fn , v ) ;
 
 Parser_next( p ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
Type* typ= Table_find_type(& /* ? */* p ->table , v .typ ) ;
 
Fn method= Table_find_method(& /* ? */* p ->table , typ , p ->lit ) ;
 
 Parser_async_fn_call( p , method , 0 , var_name , v .typ ) ;
 
 }
  else { 
 
Fn f= Table_find_fn(& /* ? */* p ->table , p ->lit ) ;
 
 if (string_eq( f .name , tos2((byte*)"println") ) ) {
 
 Parser_error( p , tos2((byte*)"`go` cannot be used with `println`") ) ;
 
 }
 ;
 
 Parser_async_fn_call( p , f , 0 , tos2((byte*)"") , tos2((byte*)"") ) ;
 
 }
 ;
 
 
 }
 void Parser_register_var(Parser* p, Var v) {
 
 if ( v .line_nr == 0 ) {
 
 v .line_nr  =  p ->scanner ->line_nr ;
 
 }
 ;
 
 Fn_register_var( p ->cur_fn , v ) ;
 
 
 }
 string Parser_js_decode(Parser* p) {
 
 Parser_check( p , main__Token_name ) ;
 
 Parser_check( p , main__Token_dot ) ;
 
string op= Parser_check_name( p ) ;
 
 if (string_eq( op , tos2((byte*)"decode") ) ) {
 
 Parser_check( p , main__Token_lpar ) ;
 
string typ= Parser_get_type( p ) ;
 
 Parser_check( p , main__Token_comma ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
 Parser_check_types( p , Parser_bool_expression( p ) , tos2((byte*)"string") ) ;
 
string expr= CGen_end_tmp( p ->cgen ) ;
 
 Parser_check( p , main__Token_rpar ) ;
 
string tmp= Parser_get_tmp( p ) ;
 
string cjson_tmp= Parser_get_tmp( p ) ;
 
string decl= _STR("%.*s %.*s; ", typ.len, typ.str, tmp.len, tmp.str) ;
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 array_Var tmp337 =  T ->fields;
 ;
for (int tmp338 = 0; tmp338 < tmp337 .len; tmp338 ++) {
 Var field = ((Var *) tmp337.data)[tmp338];
 
 
string def_val= type_default ( field .typ ) ;
 
 if (string_ne( def_val , tos2((byte*)"") ) ) {
 
 decl = string_add(decl,  _STR("%.*s . %.*s = OPTION_CAST(%.*s) %.*s;\n", tmp.len, tmp.str, field .name.len, field .name.str, field .typ.len, field .typ.str, def_val.len, def_val.str) ) ;
 
 }
 ;
 
 }
 ;
 
 Parser_gen_json_for_type( p ,* T ) ;
 
 decl = string_add(decl,  _STR("cJSON* %.*s = json__json_parse(%.*s);", cjson_tmp.len, cjson_tmp.str, expr.len, expr.str) ) ;
 
 CGen_insert_before( p ->cgen , decl ) ;
 
 Parser_gen( p , _STR("json__jsdecode_%.*s(%.*s, &%.*s); cJSON_Delete(%.*s);", typ.len, typ.str, cjson_tmp.len, cjson_tmp.str, tmp.len, tmp.str, cjson_tmp.len, cjson_tmp.str) ) ;
 
string opt_type= _STR("Option_%.*s", typ.len, typ.str) ;
 
_PUSH(& p ->cgen ->typedefs , ( _STR("typedef Option %.*s;", opt_type.len, opt_type.str) ), tmp341, string) ;
 
 Table_register_type( p ->table , opt_type ) ;
 
return  opt_type ;
 
 }
  else  if (string_eq( op , tos2((byte*)"encode") ) ) {
 
 Parser_check( p , main__Token_lpar ) ;
 
 CGen_start_tmp( p ->cgen ) ;
 
string typ= Parser_bool_expression( p ) ;
 
Type* T= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 Parser_gen_json_for_type( p ,* T ) ;
 
string expr= CGen_end_tmp( p ->cgen ) ;
 
 Parser_check( p , main__Token_rpar ) ;
 
 Parser_gen( p , _STR("json__json_print(json__jsencode_%.*s(%.*s))", typ.len, typ.str, expr.len, expr.str) ) ;
 
return  tos2((byte*)"string") ;
 
 }
  else { 
 
 Parser_error( p , _STR("bad json op \"%.*s\"", op.len, op.str) ) ;
 
 }
 ;
 
return  tos2((byte*)"") ;
 
 
 }
 void Parser_attribute(Parser* p) {
 
 Parser_check( p , main__Token_lsbr ) ;
 
 p ->attr  =  Parser_check_name( p ) ;
 
 Parser_check( p , main__Token_rsbr ) ;
 
 if ( p ->tok == main__Token_func ) {
 
 Parser_fn_decl( p ) ;
 
 p ->attr  =  tos2((byte*)"") ;
 
 return ;
 
 }
  else  if ( p ->tok == main__Token_key_struct ) {
 
 Parser_struct_decl( p ) ;
 
 p ->attr  =  tos2((byte*)"") ;
 
 return ;
 
 }
 ;
 
 Parser_error( p , tos2((byte*)"bad attribute usage") ) ;
 
 
 }
 void Parser_defer_st(Parser* p) {
 
 Parser_check( p , main__Token_key_defer ) ;
 
 Parser_check( p , main__Token_lcbr ) ;
 
int pos= p ->cgen ->lines .len ;
 
 Parser_genln( p , tos2((byte*)"{") ) ;
 
 Parser_statements( p ) ;
 
 p ->cur_fn ->defer_text  = string_add( array_string_join( array_right( p ->cgen ->lines , pos ) , tos2((byte*)"\n") ) , p ->cur_fn ->defer_text ) ;
 
 p ->cgen ->lines  =  array_left( p ->cgen ->lines , pos ) ;
 
 CGen_resetln( p ->cgen , tos2((byte*)"") ) ;
 
 
 }
 Scanner* new_scanner(string file_path) {
 
 if ( ! os__file_exists ( file_path ) ) {
 
 v_panic ( _STR("\"%.*s\" doesn\'t exist", file_path.len, file_path.str) ) ;
 
 }
 ;
 
Option_string tmp1 =  os__read_file ( file_path ) ;
 if (!tmp1 .ok) {
 string err = tmp1 . error;
 
 v_panic ( _STR("scanner: failed to open \"%.*s\"", file_path.len, file_path.str) ) ;
 
return  ALLOC_INIT(Scanner, { .file_path = tos("", 0) , .text = tos("", 0) , .pos = 0 , .line_nr = 0 , .inside_string = 0 , .dollar_start = 0 , .dollar_end = 0 , .debug = 0 , .line_comment = tos("", 0) , .started = 0 , .fmt_indent = 0 , .fmt_line_empty = 0 , } ) ;
 
 }
 string raw_text = *(string*) tmp1 . data;
 ;
 
 if ( raw_text .len >= 3 ) {
 
byte* c_text= raw_text .str ;
 
 if ( c_text [/*ptr*/ 0 ]/*rbyte 0*/ == 0xEF  &&  c_text [/*ptr*/ 1 ]/*rbyte 0*/ == 0xBB  &&  c_text [/*ptr*/ 2 ]/*rbyte 0*/ == 0xBF ) {
 
int offset_from_begin= 3 ;
 
 raw_text  =  tos (& /*11 EXP:"byte*" GOT:"byte" */ c_text [/*ptr*/ offset_from_begin ]/*rbyte 0*/ , strlen ( c_text ) - offset_from_begin ) ;
 
 }
 ;
 
 }
 ;
 
string text= raw_text ;
 
Scanner* scanner= ALLOC_INIT(Scanner, { .file_path =  file_path , .text =  text , .fmt_out =  strings__new_builder ( 1000 ) , .pos = 0 , .line_nr = 0 , .inside_string = 0 , .dollar_start = 0 , .dollar_end = 0 , .debug = 0 , .line_comment = tos("", 0) , .started = 0 , .fmt_indent = 0 , .fmt_line_empty = 0 , } ) ;
 
return  scanner ;
 
 
 }
 ScanRes scan_res(Token tok, string lit) {
 
return  (ScanRes) { tok , lit } ;
 
 
 }
 string Scanner_ident_name(Scanner* s) {
 
int start= s ->pos ;
 
 while (1) { 
 
 s ->pos ++ ;
 
 if ( s ->pos >= s ->text .len ) {
 
 break
 ;
 
 }
 ;
 
byte c= string_at( s ->text , s ->pos) ;
 
 if ( ! is_name_char ( c )  &&  ! byte_is_digit( c ) ) {
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
string name= string_substr( s ->text , start , s ->pos ) ;
 
 s ->pos -- ;
 
return  name ;
 
 
 }
 string Scanner_ident_hex_number(Scanner* s) {
 
int start_pos= s ->pos ;
 
 s ->pos  +=  2 ;
 
 while (1) { 
 
 if ( s ->pos >= s ->text .len ) {
 
 break
 ;
 
 }
 ;
 
byte c= string_at( s ->text , s ->pos) ;
 
 if ( ! byte_is_hex_digit( c ) ) {
 
 break
 ;
 
 }
 ;
 
 s ->pos ++ ;
 
 }
 ;
 
string number= string_substr( s ->text , start_pos , s ->pos ) ;
 
 s ->pos -- ;
 
return  number ;
 
 
 }
 string Scanner_ident_oct_number(Scanner* s) {
 
int start_pos= s ->pos ;
 
 while (1) { 
 
 if ( s ->pos >= s ->text .len ) {
 
 break
 ;
 
 }
 ;
 
byte c= string_at( s ->text , s ->pos) ;
 
 if ( byte_is_digit( c ) ) {
 
 if ( ! byte_is_oct_digit( c ) ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"malformed octal constant") ) ;
 
 }
 ;
 
 }
  else { 
 
 break
 ;
 
 }
 ;
 
 s ->pos ++ ;
 
 }
 ;
 
string number= string_substr( s ->text , start_pos , s ->pos ) ;
 
 s ->pos -- ;
 
return  number ;
 
 
 }
 string Scanner_ident_dec_number(Scanner* s) {
 
int start_pos= s ->pos ;
 
 while ( s ->pos < s ->text .len  &&  byte_is_digit( string_at( s ->text , s ->pos) ) ) {
 
 
 s ->pos ++ ;
 
 }
 ;
 
 if ( Scanner_expect( s , tos2((byte*)"..") , s ->pos ) ) {
 
string number= string_substr( s ->text , start_pos , s ->pos ) ;
 
 s ->pos -- ;
 
return  number ;
 
 }
 ;
 
 if ( s ->pos < s ->text .len  &&  string_at( s ->text , s ->pos) == '.' ) {
 
 s ->pos ++ ;
 
 while ( s ->pos < s ->text .len  &&  byte_is_digit( string_at( s ->text , s ->pos) ) ) {
 
 
 s ->pos ++ ;
 
 }
 ;
 
 }
 ;
 
bool has_exponential_part= 0 ;
 
 if ( Scanner_expect( s , tos2((byte*)"e+") , s ->pos )  ||  Scanner_expect( s , tos2((byte*)"e-") , s ->pos ) ) {
 
int exp_start_pos= s ->pos  +=  2 ;
 
 while ( s ->pos < s ->text .len  &&  byte_is_digit( string_at( s ->text , s ->pos) ) ) {
 
 
 s ->pos ++ ;
 
 }
 ;
 
 if ( exp_start_pos == s ->pos ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"exponent has no digits") ) ;
 
 }
 ;
 
 has_exponential_part  =  1 ;
 
 }
 ;
 
 if ( s ->pos < s ->text .len  &&  string_at( s ->text , s ->pos) == '.' ) {
 
 if ( has_exponential_part ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"exponential part should be integer") ) ;
 
 }
  else { 
 
 Scanner_error(& /* ? */* s , tos2((byte*)"too many decimal points in number") ) ;
 
 }
 ;
 
 }
 ;
 
string number= string_substr( s ->text , start_pos , s ->pos ) ;
 
 s ->pos -- ;
 
return  number ;
 
 
 }
 string Scanner_ident_number(Scanner* s) {
 
 if ( Scanner_expect( s , tos2((byte*)"0x") , s ->pos ) ) {
 
return  Scanner_ident_hex_number( s ) ;
 
 }
 ;
 
 if ( Scanner_expect( s , tos2((byte*)"0.") , s ->pos )  ||  Scanner_expect( s , tos2((byte*)"0e") , s ->pos ) ) {
 
return  Scanner_ident_dec_number( s ) ;
 
 }
 ;
 
 if ( string_at( s ->text , s ->pos) == '0' ) {
 
return  Scanner_ident_oct_number( s ) ;
 
 }
 ;
 
return  Scanner_ident_dec_number( s ) ;
 
 
 }
 bool Scanner_has_gone_over_line_end(Scanner s) {
 
int i= s .pos - 1 ;
 
 while ( i >= 0  &&  ! byte_is_white( string_at( s .text , i) ) ) {
 
 
 i -- ;
 
 }
 ;
 
 while ( i >= 0  &&  byte_is_white( string_at( s .text , i) ) ) {
 
 
 if ( is_nl ( string_at( s .text , i) ) ) {
 
return  1 ;
 
 }
 ;
 
 i -- ;
 
 }
 ;
 
return  0 ;
 
 
 }
 void Scanner_skip_whitespace(Scanner* s) {
 
 while ( s ->pos < s ->text .len  &&  byte_is_white( string_at( s ->text , s ->pos) ) ) {
 
 
 if ( is_nl ( string_at( s ->text , s ->pos) )  &&  ! Scanner_expect( s , tos2((byte*)"\r\n") , s ->pos - 1 ) ) {
 
 s ->line_nr ++ ;
 
 }
 ;
 
 s ->pos ++ ;
 
 }
 ;
 
 
 }
 ScanRes Scanner_scan(Scanner* s) {
 
 if (string_ne( s ->line_comment , tos2((byte*)"") ) ) {
 
 }
 ;
 
 if ( s ->started ) {
 
 s ->pos ++ ;
 
 }
 ;
 
 s ->started  =  1 ;
 
 if ( s ->pos >= s ->text .len ) {
 
return  scan_res ( main__Token_eof , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( ! s ->inside_string ) {
 
 Scanner_skip_whitespace( s ) ;
 
 }
 ;
 
 if ( s ->dollar_end ) {
 
 if ( string_at( s ->text , s ->pos) == '\'' ) {
 
 s ->dollar_end  =  0 ;
 
return  scan_res ( main__Token_str , tos2((byte*)"") ) ;
 
 }
 ;
 
 s ->dollar_end  =  0 ;
 
return  scan_res ( main__Token_str , Scanner_ident_string( s ) ) ;
 
 }
 ;
 
 Scanner_skip_whitespace( s ) ;
 
 if ( s ->pos >= s ->text .len ) {
 
return  scan_res ( main__Token_eof , tos2((byte*)"") ) ;
 
 }
 ;
 
byte c= string_at( s ->text , s ->pos) ;
 
byte nextc= '\0' ;
 
 if ( s ->pos + 1 < s ->text .len ) {
 
 nextc  =  string_at( s ->text , s ->pos + 1) ;
 
 }
 ;
 
 if ( is_name_char ( c ) ) {
 
string name= Scanner_ident_name( s ) ;
 
byte next_char= ( s ->pos + 1 < s ->text .len ) ? ( string_at( s ->text , s ->pos + 1) ) : ( '\0' ) ;
 
 if ( is_key ( name ) ) {
 
return  scan_res ( key_to_token ( name ) , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( s ->inside_string ) {
 
 if ( next_char == '\'' ) {
 
 s ->pos ++ ;
 
 s ->dollar_start  =  0 ;
 
 s ->inside_string  =  0 ;
 
 }
 ;
 
 }
 ;
 
 if ( s ->dollar_start  &&  next_char != '.' ) {
 
 s ->dollar_end  =  1 ;
 
 s ->dollar_start  =  0 ;
 
 }
 ;
 
 if ( s ->pos == 0  &&  next_char == ' ' ) {
 
 s ->pos ++ ;
 
 }
 ;
 
return  scan_res ( main__Token_name , name ) ;
 
 }
  else  if ( byte_is_digit( c )  ||  ( c == '.'  &&  byte_is_digit( nextc ) ) ) {
 
string num= Scanner_ident_number( s ) ;
 
return  scan_res ( main__Token_number , num ) ;
 
 }
 ;
 
 if ( ( c ==  '+' )) { /* case */
 
 if ( nextc == '+' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_inc , tos2((byte*)"") ) ;
 
 }
  else  if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_plus_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_plus , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '-' )) { /* case */
 
 if ( nextc == '-' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_dec , tos2((byte*)"") ) ;
 
 }
  else  if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_minus_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_minus , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '*' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_mult_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_mul , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '^' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_xor_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_xor , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '%' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_mod_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_mod , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '?' )) { /* case */
 
return  scan_res ( main__Token_question , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '\'' )) { /* case */
 
return  scan_res ( main__Token_str , Scanner_ident_string( s ) ) ;
 
 }
 else  if ( ( c ==  '\`' )) { /* case */
 
return  scan_res ( main__Token_chartoken , Scanner_ident_char( s ) ) ;
 
 }
 else  if ( ( c ==  '(' )) { /* case */
 
return  scan_res ( main__Token_lpar , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  ')' )) { /* case */
 
return  scan_res ( main__Token_rpar , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '[' )) { /* case */
 
return  scan_res ( main__Token_lsbr , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  ']' )) { /* case */
 
return  scan_res ( main__Token_rsbr , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '{' )) { /* case */
 
 if ( s ->inside_string ) {
 
return  Scanner_scan( s ) ;
 
 }
 ;
 
return  scan_res ( main__Token_lcbr , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '$' )) { /* case */
 
return  scan_res ( main__Token_dollar , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '}' )) { /* case */
 
 if ( s ->inside_string ) {
 
 s ->pos ++ ;
 
 if ( string_at( s ->text , s ->pos) == '\'' ) {
 
 s ->inside_string  =  0 ;
 
return  scan_res ( main__Token_str , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_str , Scanner_ident_string( s ) ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_rcbr , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  '&' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_and_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( nextc == '&' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_and , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_amp , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '|' )) { /* case */
 
 if ( nextc == '|' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_logical_or , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_or_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_pipe , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  ',' )) { /* case */
 
return  scan_res ( main__Token_comma , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '@' )) { /* case */
 
 s ->pos ++ ;
 
string name= Scanner_ident_name( s ) ;
 
 if ( ! is_key ( name ) ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"@ must be used before keywords (e.g. `@type string`)") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_name , name ) ;
 
 }
 else  if ( ( c ==  '\r' )) { /* case */
 
 if ( nextc == '\n' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_nl , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  '\n' )) { /* case */
 
return  scan_res ( main__Token_nl , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '.' )) { /* case */
 
 if ( nextc == '.' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_dotdot , tos2((byte*)"") ) ;
 
 }
 ;
 
return  scan_res ( main__Token_dot , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '#' )) { /* case */
 
int start= s ->pos + 1 ;
 
 while ( s ->pos < s ->text .len  &&  string_at( s ->text , s ->pos) != '\n' ) {
 
 
 s ->pos ++ ;
 
 }
 ;
 
 s ->line_nr ++ ;
 
 if ( nextc == '!' ) {
 
 s ->line_comment  =  string_trim_space( string_substr( s ->text , start + 1 , s ->pos ) ) ;
 
 Scanner_fgenln( s , _STR("// shebang line \"%.*s\"", s ->line_comment.len, s ->line_comment.str) ) ;
 
return  Scanner_scan( s ) ;
 
 }
 ;
 
string hash= string_substr( s ->text , start , s ->pos ) ;
 
return  scan_res ( main__Token_hash , string_trim_space( hash ) ) ;
 
 }
 else  if ( ( c ==  '>' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_ge , tos2((byte*)"") ) ;
 
 }
  else  if ( nextc == '>' ) {
 
 if ( s ->pos + 2 < s ->text .len  &&  string_at( s ->text , s ->pos + 2) == '=' ) {
 
 s ->pos  +=  2 ;
 
return  scan_res ( main__Token_righ_shift_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_righ_shift , tos2((byte*)"") ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_gt , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  '<' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_le , tos2((byte*)"") ) ;
 
 }
  else  if ( nextc == '<' ) {
 
 if ( s ->pos + 2 < s ->text .len  &&  string_at( s ->text , s ->pos + 2) == '=' ) {
 
 s ->pos  +=  2 ;
 
return  scan_res ( main__Token_left_shift_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_left_shift , tos2((byte*)"") ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_lt , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  '=' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_eq , tos2((byte*)"") ) ;
 
 }
  else  if ( nextc == '>' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_arrow , tos2((byte*)"") ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  ':' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_decl_assign , tos2((byte*)"") ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_colon , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  ';' )) { /* case */
 
return  scan_res ( main__Token_semicolon , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '!' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_ne , tos2((byte*)"") ) ;
 
 }
  else { 
 
return  scan_res ( main__Token_not , tos2((byte*)"") ) ;
 
 }
 ;
 
 }
 else  if ( ( c ==  '~' )) { /* case */
 
return  scan_res ( main__Token_bit_not , tos2((byte*)"") ) ;
 
 }
 else  if ( ( c ==  '/' )) { /* case */
 
 if ( nextc == '=' ) {
 
 s ->pos ++ ;
 
return  scan_res ( main__Token_div_assign , tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( nextc == '/' ) {
 
int start= s ->pos + 1 ;
 
 while ( s ->pos < s ->text .len  &&  string_at( s ->text , s ->pos) != '\n' ) {
 
 
 s ->pos ++ ;
 
 }
 ;
 
 s ->line_nr ++ ;
 
 s ->line_comment  =  string_substr( s ->text , start + 1 , s ->pos ) ;
 
 s ->line_comment  =  string_trim_space( s ->line_comment ) ;
 
 Scanner_fgenln( s , _STR("// %.*s \"%.*s\"", Token_str( s ->prev_tok ).len, Token_str( s ->prev_tok ).str, s ->line_comment.len, s ->line_comment.str) ) ;
 
return  Scanner_scan( s ) ;
 
 }
 ;
 
 if ( nextc == '*' ) {
 
int start= s ->pos ;
 
int nest_count= 1 ;
 
 while ( nest_count > 0 ) {
 
 
 s ->pos ++ ;
 
 if ( s ->pos >= s ->text .len ) {
 
 s ->line_nr -- ;
 
 Scanner_error(& /* ? */* s , tos2((byte*)"comment not terminated") ) ;
 
 }
 ;
 
 if ( string_at( s ->text , s ->pos) == '\n' ) {
 
 s ->line_nr ++ ;
 
 continue
 ;
 
 }
 ;
 
 if ( Scanner_expect( s , tos2((byte*)"/*") , s ->pos ) ) {
 
 nest_count ++ ;
 
 continue
 ;
 
 }
 ;
 
 if ( Scanner_expect( s , tos2((byte*)"*/") , s ->pos ) ) {
 
 nest_count -- ;
 
 }
 ;
 
 }
 ;
 
 s ->pos ++ ;
 
int end= s ->pos + 1 ;
 
string comm= string_substr( s ->text , start , end ) ;
 
 Scanner_fgenln( s , comm ) ;
 
return  Scanner_scan( s ) ;
 
 }
 ;
 
return  scan_res ( main__Token_div , tos2((byte*)"") ) ;
 
 }
 ;
 
 #ifdef _WIN32
 
 if ( c == '\0' ) {
 
return  scan_res ( main__Token_eof , tos2((byte*)"") ) ;
 
 }
 ;
 
 #endif
 ;
 
string msg= _STR("invalid character `%.*s`", byte_str( c ).len, byte_str( c ).str) ;
 
 if ( c == '"' ) {
 
 msg = string_add(msg,  tos2((byte*)", use \' to denote strings") ) ;
 
 }
 ;
 
 Scanner_error(& /* ? */* s , msg ) ;
 
return  scan_res ( main__Token_eof , tos2((byte*)"") ) ;
 
 
 }
 void Scanner_error(Scanner* s, string msg) {
 
string file= string_all_after( s ->file_path , tos2((byte*)"/") ) ;
 
printf( "%.*s:%d panic: %.*s\n", file.len, file.str, s ->line_nr + 1, msg.len, msg.str ) ;
 
 v_exit ( 1 ) ;
 
 
 }
 string Scanner_ident_string(Scanner* s) {
 
int start= s ->pos ;
 
 s ->inside_string  =  0 ;
 
byte slash= '\\' ;
 
 while (1) { 
 
 s ->pos ++ ;
 
 if ( s ->pos >= s ->text .len ) {
 
 break
 ;
 
 }
 ;
 
byte c= string_at( s ->text , s ->pos) ;
 
byte prevc= string_at( s ->text , s ->pos - 1) ;
 
 if ( c == '\''  &&  ( prevc != slash  ||  ( prevc == slash  &&  string_at( s ->text , s ->pos - 2) == slash ) ) ) {
 
 break
 ;
 
 }
 ;
 
 if ( c == '\n' ) {
 
 s ->line_nr ++ ;
 
 }
 ;
 
 if ( c == '0'  &&  s ->pos > 2  &&  string_at( s ->text , s ->pos - 1) == '\\' ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"0 character in a string literal") ) ;
 
 }
 ;
 
 if ( c == '0'  &&  s ->pos > 5  &&  Scanner_expect( s , tos2((byte*)"\\x0") , s ->pos - 3 ) ) {
 
 Scanner_error(& /* ? */* s , tos2((byte*)"0 character in a string literal") ) ;
 
 }
 ;
 
 if ( c == '{'  &&  prevc == '$' ) {
 
 s ->inside_string  =  1 ;
 
 s ->pos  -=  2 ;
 
 break
 ;
 
 }
 ;
 
 if ( ( byte_is_letter( c )  ||  c == '_' )  &&  prevc == '$' ) {
 
 s ->inside_string  =  1 ;
 
 s ->dollar_start  =  1 ;
 
 s ->pos  -=  2 ;
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
string lit= tos2((byte*)"") ;
 
 if ( string_at( s ->text , start) == '\'' ) {
 
 start ++ ;
 
 }
 ;
 
int end= s ->pos ;
 
 if ( s ->inside_string ) {
 
 end ++ ;
 
 }
 ;
 
 if ( start > s ->pos ) {
 
 }
  else { 
 
 lit  =  string_substr( s ->text , start , end ) ;
 
 }
 ;
 
return  lit ;
 
 
 }
 string Scanner_ident_char(Scanner* s) {
 
int start= s ->pos ;
 
byte slash= '\\' ;
 
int len= 0 ;
 
 while (1) { 
 
 s ->pos ++ ;
 
 if ( s ->pos >= s ->text .len ) {
 
 break
 ;
 
 }
 ;
 
 if ( string_at( s ->text , s ->pos) != slash ) {
 
 len ++ ;
 
 }
 ;
 
bool double_slash= Scanner_expect( s , tos2((byte*)"\\\\") , s ->pos - 2 ) ;
 
 if ( string_at( s ->text , s ->pos) == '\`'  &&  ( string_at( s ->text , s ->pos - 1) != slash  ||  double_slash ) ) {
 
 if ( double_slash ) {
 
 len ++ ;
 
 }
 ;
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
 len -- ;
 
string c= string_substr( s ->text , start + 1 , s ->pos ) ;
 
 if ( len != 1 ) {
 
ustring u= string_ustring( c ) ;
 
 if ( u .len != 1 ) {
 
 Scanner_error(& /* ? */* s , _STR("invalid character literal (more than one character: %d)", len) ) ;
 
 }
 ;
 
 }
 ;
 
return  c ;
 
 
 }
 Token Scanner_peek(Scanner* s) {
 
int pos= s ->pos ;
 
int line= s ->line_nr ;
 
bool inside_string= s ->inside_string ;
 
bool dollar_start= s ->dollar_start ;
 
bool dollar_end= s ->dollar_end ;
 
ScanRes res= Scanner_scan( s ) ;
 
Token tok= res .tok ;
 
 s ->pos  =  pos ;
 
 s ->line_nr  =  line ;
 
 s ->inside_string  =  inside_string ;
 
 s ->dollar_start  =  dollar_start ;
 
 s ->dollar_end  =  dollar_end ;
 
return  tok ;
 
 
 }
 bool Scanner_expect(Scanner* s, string want, int start_pos) {
 
int end_pos= start_pos + want .len ;
 
 if ( start_pos < 0  ||  start_pos >= s ->text .len ) {
 
return  0 ;
 
 }
 ;
 
 if ( end_pos < 0  ||  end_pos > s ->text .len ) {
 
return  0 ;
 
 }
 ;
 
 int tmp120 =  start_pos;
 ;
for (int tmp121 = tmp120; tmp121 <  end_pos; tmp121++) {
 int pos = tmp121;
 
 
 if ( string_at( s ->text , pos) != string_at( want , pos - start_pos) ) {
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 void Scanner_debug_tokens(Scanner* s) {
 
 s ->pos  =  0 ;
 
 s ->debug  =  1 ;
 
string fname= string_all_after( s ->file_path , tos2((byte*)"/") ) ;
 
printf( "\n===DEBUG TOKENS %.*s===\n", fname.len, fname.str ) ;
 
 while (1) { 
 
ScanRes res= Scanner_scan( s ) ;
 
Token tok= res .tok ;
 
string lit= res .lit ;
 
 v_print ( Token_str( tok ) ) ;
 
 if (string_ne( lit , tos2((byte*)"") ) ) {
 
printf( " `%.*s`\n", lit.len, lit.str ) ;
 
 }
  else { 
 
 println ( tos2((byte*)"") ) ;
 
 }
 ;
 
 if ( tok == main__Token_eof ) {
 
 println ( tos2((byte*)"============ END OF DEBUG TOKENS ==================") ) ;
 
 break
 ;
 
 }
 ;
 
 }
 ;
 
 
 }
 bool is_name_char(byte c) {
 
return  byte_is_letter( c )  ||  c == '_' ;
 
 
 }
 bool is_nl(byte c) {
 
return  c == '\r'  ||  c == '\n' ;
 
 
 }
 int Scanner_get_opening_bracket(Scanner* s) {
 
int pos= s ->pos ;
 
int parentheses= 0 ;
 
bool inside_string= 0 ;
 
 while ( pos > 0  &&  string_at( s ->text , pos) != '\n' ) {
 
 
 if ( string_at( s ->text , pos) == ')'  &&  ! inside_string ) {
 
 parentheses ++ ;
 
 }
 ;
 
 if ( string_at( s ->text , pos) == '('  &&  ! inside_string ) {
 
 parentheses -- ;
 
 }
 ;
 
 if ( string_at( s ->text , pos) == '\''  &&  string_at( s ->text , pos - 1) != '\\'  &&  string_at( s ->text , pos - 1) != '\`' ) {
 
 inside_string  =  ! inside_string ;
 
 }
 ;
 
 if ( parentheses == 0 ) {
 
 break
 ;
 
 }
 ;
 
 pos -- ;
 
 }
 ;
 
return  pos ;
 
 
 }
 void Scanner_create_type_string(Scanner* s, Type T, string name) {
 
int line= s ->line_nr ;
 
bool inside_string= s ->inside_string ;
 
string newtext= tos2((byte*)"\'{ ") ;
 
int start= Scanner_get_opening_bracket( s ) + 1 ;
 
int end= s ->pos ;
 
 array_Var tmp150 =  T .fields ;
 ;
for (int i = 0; i < tmp150 .len; i ++) {
 Var field = ((Var *) tmp150 . data)[i];
 
 
 if ( i != 0 ) {
 
 newtext = string_add(newtext,  tos2((byte*)", ") ) ;
 
 }
 ;
 
 newtext = string_add(newtext, string_add( _STR("%.*s: ", field .name.len, field .name.str) , _STR("$%.*s.%.*s", name.len, name.str, field .name.len, field .name.str) ) ) ;
 
 }
 ;
 
 newtext = string_add(newtext,  tos2((byte*)" }\'") ) ;
 
 s ->text  = string_add(string_add( string_substr( s ->text , 0 , start ) , newtext ) , string_substr( s ->text , end , s ->text .len ) ) ;
 
 s ->pos  =  start - 2 ;
 
 s ->line_nr  =  line ;
 
 s ->inside_string  =  inside_string ;
 
 
 }
 bool contains_capital(string s) {
 
 for (
int i= 0  ;  i < s .len  ;  i ++ ) { 
 
 
byte c= string_at( s , i) ;
 
 if ( c >= 'A'  &&  c <= 'Z' ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool good_type_name(string s) {
 
 if ( s .len < 4 ) {
 
return  1 ;
 
 }
 ;
 
 int tmp155 =  2;
 ;
for (int tmp156 = tmp155; tmp156 <  s .len; tmp156++) {
 int i = tmp156;
 
 
 if ( byte_is_capital( string_at( s , i) )  &&  byte_is_capital( string_at( s , i - 1) )  &&  byte_is_capital( string_at( s , i - 2) ) ) {
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 string Type_str(Type t) {
 
string s= _STR("type \"%.*s\" {", t .name.len, t .name.str) ;
 
 if ( t .fields .len > 0 ) {
 
 array_Var tmp2 =  t .fields;
 ;
for (int tmp3 = 0; tmp3 < tmp2 .len; tmp3 ++) {
 Var field = ((Var *) tmp2.data)[tmp3];
 
 
 s = string_add(s,  _STR("\n    %.*s %.*s", field .name.len, field .name.str, field .typ.len, field .typ.str) ) ;
 
 }
 ;
 
 s = string_add(s,  tos2((byte*)"\n") ) ;
 
 }
 ;
 
 if ( t .methods .len > 0 ) {
 
 array_Fn tmp4 =  t .methods;
 ;
for (int tmp5 = 0; tmp5 < tmp4 .len; tmp5 ++) {
 Fn method = ((Fn *) tmp4.data)[tmp5];
 
 
 s = string_add(s,  _STR("\n    %.*s", Fn_str( method ).len, Fn_str( method ).str) ) ;
 
 }
 ;
 
 s = string_add(s,  tos2((byte*)"\n") ) ;
 
 }
 ;
 
 s = string_add(s,  tos2((byte*)"}\n") ) ;
 
return  s ;
 
 
 }
 string Fn_str(Fn f) {
 
Table t= (Table) { .types = new_array(0, 1, sizeof(Type)) , .consts = new_array(0, 1, sizeof(Var)) , .generic_fns = new_array(0, 1, sizeof(GenTable)) , .modules = new_array(0, 1, sizeof(string)) , .imports = new_array(0, 1, sizeof(string)) , .file_imports = new_array(0, 1, sizeof(FileImportTable)) , .flags = new_array(0, 1, sizeof(string)) , .fn_cnt = 0 , .obfuscate = 0 } ;
 
string str_args= Fn_str_args(& /* ? */ f ,& /*11 EXP:"Table*" GOT:"Table" */ t ) ;
 
return  _STR("%.*s(%.*s) %.*s", f .name.len, f .name.str, str_args.len, str_args.str, f .typ.len, f .typ.str) ;
 
 
 }
 string Table_debug_fns(Table* t) {
 
strings__Builder s= strings__new_builder ( 1000 ) ;
 
 map_Fn tmp9 =  t ->fns ;
 array_string keys_tmp9 = map_keys(& tmp9 ); 
 for (int l = 0; l < keys_tmp9 .len; l++) {
   string _ = ((string*)keys_tmp9 .data)[l];
 Fn f = {0}; map_get(tmp9, _, & f);
 
 
 strings__Builder_writeln(& /* ? */ s , f .name ) ;
 
 }
 ;
 
return  strings__Builder_str( s ) ;
 
 
 }
 bool is_number_type(string typ) {
 
return _IN(string,  typ ,  main__number_types ) ;
 
 
 }
 bool is_float_type(string typ) {
 
return _IN(string,  typ ,  main__float_types ) ;
 
 
 }
 bool is_primitive_type(string typ) {
 
return  is_number_type ( typ )  || string_eq( typ , tos2((byte*)"string") ) ;
 
 
 }
 Table* new_table(bool obfuscate) {
 
Table* t= ALLOC_INIT(Table, { .obf_ids =  new_map(1, sizeof(int)) , .fns =  new_map(1, sizeof(Fn)) , .generic_fns = new_array_from_c_array(0, 0, sizeof(GenTable), (GenTable[]) {EMPTY_STRUCT_INIT   }) , .obfuscate =  obfuscate , .file_imports = new_array_from_c_array(0, 0, sizeof(FileImportTable), (FileImportTable[]) {EMPTY_STRUCT_INIT   }) , .types = new_array(0, 1, sizeof(Type)) , .consts = new_array(0, 1, sizeof(Var)) , .modules = new_array(0, 1, sizeof(string)) , .imports = new_array(0, 1, sizeof(string)) , .flags = new_array(0, 1, sizeof(string)) , .fn_cnt = 0 , } ) ;
 
 Table_register_type( t , tos2((byte*)"int") ) ;
 
 Table_register_type( t , tos2((byte*)"size_t") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"i8") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"u8") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"i16") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"u16") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"i32") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"u32") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"byte") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"i64") , tos2((byte*)"int") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"u64") , tos2((byte*)"int") ) ;
 
 Table_register_type( t , tos2((byte*)"byteptr") ) ;
 
 Table_register_type( t , tos2((byte*)"intptr") ) ;
 
 Table_register_type( t , tos2((byte*)"f32") ) ;
 
 Table_register_type( t , tos2((byte*)"f64") ) ;
 
 Table_register_type( t , tos2((byte*)"rune") ) ;
 
 Table_register_type( t , tos2((byte*)"bool") ) ;
 
 Table_register_type( t , tos2((byte*)"void") ) ;
 
 Table_register_type( t , tos2((byte*)"voidptr") ) ;
 
 Table_register_type( t , tos2((byte*)"T") ) ;
 
 Table_register_type( t , tos2((byte*)"va_list") ) ;
 
 Table_register_const( t , tos2((byte*)"stdin") , tos2((byte*)"int") , tos2((byte*)"main") , 0 ) ;
 
 Table_register_const( t , tos2((byte*)"stdout") , tos2((byte*)"int") , tos2((byte*)"main") , 0 ) ;
 
 Table_register_const( t , tos2((byte*)"stderr") , tos2((byte*)"int") , tos2((byte*)"main") , 0 ) ;
 
 Table_register_const( t , tos2((byte*)"errno") , tos2((byte*)"int") , tos2((byte*)"main") , 0 ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"map_string") , tos2((byte*)"map") ) ;
 
 Table_register_type_with_parent( t , tos2((byte*)"map_int") , tos2((byte*)"map") ) ;
 
return  t ;
 
 
 }
 string Table_var_cgen_name(Table* t, string name) {
 
 if ( array_string_contains( main__CReserved , name ) ) {
 
return  _STR("v_%.*s", name.len, name.str) ;
 
 }
  else { 
 
return  name ;
 
 }
 ;
 
 
 }
 void Table_register_module(Table* t, string mod) {
 
 if ( array_string_contains( t ->modules , mod ) ) {
 
 return ;
 
 }
 ;
 
_PUSH(& t ->modules , ( mod ), tmp11, string) ;
 
 
 }
 void Parser_register_array(Parser* p, string typ) {
 
 if ( string_contains( typ , tos2((byte*)"*") ) ) {
 
printf( "bad arr %.*s\n", typ.len, typ.str ) ;
 
 return ;
 
 }
 ;
 
 if ( ! Table_known_type(& /* ? */* p ->table , typ ) ) {
 
 Parser_register_type_with_parent( p , typ , tos2((byte*)"array") ) ;
 
_PUSH(& p ->cgen ->typedefs , ( _STR("typedef array %.*s;", typ.len, typ.str) ), tmp12, string) ;
 
 }
 ;
 
 
 }
 void Parser_register_map(Parser* p, string typ) {
 
 if ( string_contains( typ , tos2((byte*)"*") ) ) {
 
printf( "bad map %.*s\n", typ.len, typ.str ) ;
 
 return ;
 
 }
 ;
 
 if ( ! Table_known_type(& /* ? */* p ->table , typ ) ) {
 
 Parser_register_type_with_parent( p , typ , tos2((byte*)"map") ) ;
 
_PUSH(& p ->cgen ->typedefs , ( _STR("typedef map %.*s;", typ.len, typ.str) ), tmp13, string) ;
 
 }
 ;
 
 
 }
 bool Table_known_mod(Table* table, string mod) {
 
return _IN(string,  mod ,  table ->modules ) ;
 
 
 }
 void Table_register_const(Table* t, string name, string typ, string mod, bool is_imported) {
 
_PUSH(& t ->consts , ( (Var) { .name =  name , .typ =  typ , .is_const =  1 , .is_import_const =  is_imported , .mod =  mod , .is_arg = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ), tmp14, Var) ;
 
 
 }
 void Parser_register_global(Parser* p, string name, string typ) {
 
_PUSH(& p ->table ->consts , ( (Var) { .name =  name , .typ =  typ , .is_const =  1 , .is_global =  1 , .mod =  p ->mod , .is_mut =  1 , .is_arg = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .line_nr = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ), tmp15, Var) ;
 
 
 }
 void Table_register_fn(Table* t, Fn new_fn) {
  
 Fn tmp16 =  new_fn; 

map__set(& t ->fns , new_fn .name , & tmp16) ;
 
 
 }
 bool Table_known_type(Table* table, string typ) {
 
 if ( string_ends_with( typ , tos2((byte*)"*") )  &&  ! string_contains( typ , tos2((byte*)" ") ) ) {
 
 typ  =  string_left( typ , typ .len - 1 ) ;
 
 }
 ;
 
 array_Type tmp17 =  table ->types;
 ;
for (int tmp18 = 0; tmp18 < tmp17 .len; tmp18 ++) {
 Type t = ((Type *) tmp17.data)[tmp18];
 
 
 if (string_eq( t .name , typ )  &&  ! t .is_placeholder ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 Fn Table_find_fn(Table* t, string name) {
  
 Fn tmp19 = {0}; bool tmp20 = map_get( t ->fns , name, & tmp19); 

Fn f= tmp19 ;
 
 if ( ! isnil ( f .name .str ) ) {
 
return  f ;
 
 }
 ;
 
return  (Fn) { .name = tos("", 0) , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
 
 }
 bool Table_known_fn(Table* t, string name) {
 
Fn f= Table_find_fn(& /* ? */* t , name ) ;
 
return string_ne( f .name , tos2((byte*)"") ) ;
 
 
 }
 bool Table_known_const(Table* t, string name) {
 
Var v= Table_find_const(& /* ? */* t , name ) ;
 
return  v .name .len > 0 ;
 
 
 }
 void Table_register_type(Table* t, string typ) {
 
 if ( typ .len == 0 ) {
 
 return ;
 
 }
 ;
 
 array_Type tmp24 =  t ->types;
 ;
for (int tmp25 = 0; tmp25 < tmp24 .len; tmp25 ++) {
 Type typ2 = ((Type *) tmp24.data)[tmp25];
 
 
 if (string_eq( typ2 .name , typ ) ) {
 
 return ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& t ->types , ( (Type) { .name =  typ , .mod = tos("", 0) , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .parent = tos("", 0) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ), tmp26, Type) ;
 
 
 }
 void Parser_register_type_with_parent(Parser* p, string strtyp, string parent) {
 
Type typ= (Type) { .name =  strtyp , .parent =  parent , .mod =  p ->mod , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ;
 
 Table_register_type2( p ->table , typ ) ;
 
 
 }
 void Table_register_type_with_parent(Table* t, string typ, string parent) {
 
 if ( typ .len == 0 ) {
 
 return ;
 
 }
 ;
 
 array_Type tmp28 =  t ->types;
 ;
for (int tmp29 = 0; tmp29 < tmp28 .len; tmp29 ++) {
 Type typ2 = ((Type *) tmp28.data)[tmp29];
 
 
 if (string_eq( typ2 .name , typ ) ) {
 
 return ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& t ->types , ( (Type) { .name =  typ , .parent =  parent , .mod = tos("", 0) , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ), tmp30, Type) ;
 
 
 }
 void Table_register_type2(Table* t, Type typ) {
 
 if ( typ .name .len == 0 ) {
 
 return ;
 
 }
 ;
 
 array_Type tmp31 =  t ->types;
 ;
for (int tmp32 = 0; tmp32 < tmp31 .len; tmp32 ++) {
 Type typ2 = ((Type *) tmp31.data)[tmp32];
 
 
 if (string_eq( typ2 .name , typ .name ) ) {
 
 return ;
 
 }
 ;
 
 }
 ;
 
_PUSH(& t ->types , ( typ ), tmp33, Type) ;
 
 
 }
 void Type_add_field(Type* t, string name, string typ, bool is_mut, string attr, AccessMod access_mod) {
 
Var v= (Var) { .name =  name , .typ =  typ , .is_mut =  is_mut , .attr =  attr , .access_mod =  access_mod , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
_PUSH(& t ->fields , ( v ), tmp35, Var) ;
 
 
 }
 bool Type_has_field(Type* t, string name) {
 
Var field= Type_find_field(& /* ? */* t , name ) ;
 
return  (string_ne( field .name , tos2((byte*)"") ) ) ;
 
 
 }
 bool Type_has_enum_val(Type* t, string name) {
 
return _IN(string,  name ,  t ->enum_vals ) ;
 
 
 }
 Var Type_find_field(Type* t, string name) {
 
 array_Var tmp37 =  t ->fields;
 ;
for (int tmp38 = 0; tmp38 < tmp37 .len; tmp38 ++) {
 Var field = ((Var *) tmp37.data)[tmp38];
 
 
 if (string_eq( field .name , name ) ) {
 
return  field ;
 
 }
 ;
 
 }
 ;
 
return  (Var) { .typ = tos("", 0) , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
 
 }
 bool Table_type_has_field(Table* table, Type* typ, string name) {
 
Var field= Table_find_field(& /* ? */* table , typ , name ) ;
 
return  (string_ne( field .name , tos2((byte*)"") ) ) ;
 
 
 }
 Var Table_find_field(Table* table, Type* typ, string name) {
 
Var field= Type_find_field(& /* ? */* typ , name ) ;
 
 if ( field .name .len == 0  &&  typ ->parent .len > 0 ) {
 
Type* parent= Table_find_type(& /* ? */* table , typ ->parent ) ;
 
return  Type_find_field(& /* ? */* parent , name ) ;
 
 }
 ;
 
return  field ;
 
 
 }
 void Type_add_method(Type* t, Fn f) {
 
_PUSH(& t ->methods , ( f ), tmp42, Fn) ;
 
 
 }
 bool Type_has_method(Type* t, string name) {
 
Fn method= Type_find_method(& /* ? */* t , name ) ;
 
return  (string_ne( method .name , tos2((byte*)"") ) ) ;
 
 
 }
 bool Table_type_has_method(Table* table, Type* typ, string name) {
 
Fn method= Table_find_method(& /* ? */* table , typ , name ) ;
 
return  (string_ne( method .name , tos2((byte*)"") ) ) ;
 
 
 }
 Fn Table_find_method(Table* table, Type* typ, string name) {
 
Fn method= Type_find_method(& /* ? */* typ , name ) ;
 
 if ( method .name .len == 0  &&  typ ->parent .len > 0 ) {
 
Type* parent= Table_find_type(& /* ? */* table , typ ->parent ) ;
 
return  Type_find_method(& /* ? */* parent , name ) ;
 
 }
 ;
 
return  method ;
 
 
 }
 Fn Type_find_method(Type* t, string name) {
 
 array_Fn tmp47 =  t ->methods;
 ;
for (int tmp48 = 0; tmp48 < tmp47 .len; tmp48 ++) {
 Fn method = ((Fn *) tmp47.data)[tmp48];
 
 
 if (string_eq( method .name , name ) ) {
 
return  method ;
 
 }
 ;
 
 }
 ;
 
return  (Fn) { .name = tos("", 0) , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } ;
 
 
 }
 Type* Parser_find_type(Parser* p, string name) {
 
Type* typ= Table_find_type(& /* ? */* p ->table , name ) ;
 
 if ( typ ->name .len == 0 ) {
 
return  Table_find_type(& /* ? */* p ->table , Parser_prepend_mod(& /* ? */* p , name ) ) ;
 
 }
 ;
 
return  typ ;
 
 
 }
 Type* Table_find_type(Table* t, string name) {
 
 if ( string_ends_with( name , tos2((byte*)"*") )  &&  ! string_contains( name , tos2((byte*)" ") ) ) {
 
 name  =  string_left( name , name .len - 1 ) ;
 
 }
 ;
 
 array_Type tmp50 =  t ->types ;
 ;
for (int i = 0; i < tmp50 .len; i ++) {
 Type typ = ((Type *) tmp50 . data)[i];
 
 
 if (string_eq( typ .name , name ) ) {
 
return  & /*vvar*/  ( *(Type*) array__get( t ->types , i) ) ;
 
 }
 ;
 
 }
 ;
 
return  ALLOC_INIT(Type, { .mod = tos("", 0) , .name = tos("", 0) , .fields = new_array(0, 1, sizeof(Var)) , .methods = new_array(0, 1, sizeof(Fn)) , .parent = tos("", 0) , .is_c = 0 , .is_interface = 0 , .is_enum = 0 , .enum_vals = new_array(0, 1, sizeof(string)) , .gen_types = new_array(0, 1, sizeof(string)) , .is_placeholder = 0 } ) ;
 
 
 }
 bool Parser__check_types(Parser* p, string got, string expected, bool throw) {
 
 Parser_log(& /* ? */* p , _STR("check types got=\"%.*s\" exp=\"%.*s\"  ", got.len, got.str, expected.len, expected.str) ) ;
 
 if ( p ->pref ->translated ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"f32") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"f64") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"f64") )  && string_eq( expected , tos2((byte*)"f32") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"f32") )  && string_eq( expected , tos2((byte*)"f64") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"i64") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"void*") )  &&  string_starts_with( expected , tos2((byte*)"fn ") ) ) {
 
return  1 ;
 
 }
 ;
 
 if ( string_starts_with( got , tos2((byte*)"[") )  && string_eq( expected , tos2((byte*)"byte*") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"void*") )  || string_eq( expected , tos2((byte*)"void*") ) ) {
 
 if ( p ->pref ->is_play ) {
 
return  0 ;
 
 }
 ;
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"byte") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"byteptr") )  && string_eq( expected , tos2((byte*)"byte*") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"byte*") )  && string_eq( expected , tos2((byte*)"byteptr") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"byte*") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"int") )  && string_eq( expected , tos2((byte*)"byteptr") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"Option") )  &&  string_starts_with( expected , tos2((byte*)"Option_") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( got , tos2((byte*)"array") )  &&  string_starts_with( expected , tos2((byte*)"array_") ) ) {
 
return  1 ;
 
 }
 ;
 
 if ( string_starts_with( expected , tos2((byte*)"Option_") )  &&  string_ends_with( expected , got ) ) {
 
return  1 ;
 
 }
 ;
 
 if ( ! p ->pref ->is_play ) {
 
 if ( string_ends_with( expected , tos2((byte*)"*") )  && string_eq( got , tos2((byte*)"int") ) ) {
 
return  1 ;
 
 }
 ;
 
 if (string_eq( expected , tos2((byte*)"void*") )  && string_eq( got , tos2((byte*)"int") ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
 expected  =  string_replace( expected , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 got  =  string_replace( got , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 if (string_ne( got , expected ) ) {
 
 if ( string_ends_with( expected , tos2((byte*)"er") ) ) {
 
 if ( Parser_satisfies_interface( p , expected , got , throw ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
 if ( ! throw ) {
 
return  0 ;
 
 }
  else { 
 
 Parser_error( p , _STR("expected type `%.*s`, but got `%.*s`", expected.len, expected.str, got.len, got.str) ) ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 bool Parser_check_types(Parser* p, string got, string expected) {
 
return  Parser__check_types( p , got , expected , 1 ) ;
 
 
 }
 bool Parser_check_types_no_throw(Parser* p, string got, string expected) {
 
return  Parser__check_types( p , got , expected , 0 ) ;
 
 
 }
 bool Parser_satisfies_interface(Parser* p, string interface_name, string _typ, bool throw) {
 
Type* int_typ= Table_find_type(& /* ? */* p ->table , interface_name ) ;
 
Type* typ= Table_find_type(& /* ? */* p ->table , _typ ) ;
 
 array_Fn tmp55 =  int_typ ->methods;
 ;
for (int tmp56 = 0; tmp56 < tmp55 .len; tmp56 ++) {
 Fn method = ((Fn *) tmp55.data)[tmp56];
 
 
 if ( ! Type_has_method(& /* ? */* typ , method .name ) ) {
 
 Parser_error( p , _STR("Type \"%.*s\" doesn\'t satisfy interface \"%.*s\" (method \"%.*s\" is not implemented)", _typ.len, _typ.str, interface_name.len, interface_name.str, method .name.len, method .name.str) ) ;
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 string type_default(string typ) {
 
 if ( string_starts_with( typ , tos2((byte*)"array_") ) ) {
 
 typ  =  string_right( typ , 6 ) ;
 
return  _STR("new_array(0, 1, sizeof(%.*s))", typ.len, typ.str) ;
 
 }
 ;
 
 if ( string_ends_with( typ , tos2((byte*)"*") ) ) {
 
return  tos2((byte*)"0") ;
 
 }
 ;
 
 if ( string_contains( typ , tos2((byte*)"__") ) ) {
 
return  tos2((byte*)"STRUCT_DEFAULT_VALUE") ;
 
 }
 ;
 
 if ( string_eq( typ,  tos2((byte*)"bool") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"string") )) { /* case */
 
return  tos2((byte*)"tos(\"\", 0)") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i8") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i16") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i32") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i64") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"u8") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"u16") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"u32") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"u64") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"byte") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"int") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"rune") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"f32") )) { /* case */
 
return  tos2((byte*)"0.0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"f64") )) { /* case */
 
return  tos2((byte*)"0.0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"byteptr") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"voidptr") )) { /* case */
 
return  tos2((byte*)"0") ;
 
 }
 ;
 
return  tos2((byte*)"STRUCT_DEFAULT_VALUE") ;
 
 
 }
 bool Table_is_interface(Table* t, string name) {
 
 array_Type tmp57 =  t ->types;
 ;
for (int tmp58 = 0; tmp58 < tmp57 .len; tmp58 ++) {
 Type typ = ((Type *) tmp57.data)[tmp58];
 
 
 if ( typ .is_interface  && string_eq( typ .name , name ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 bool Table_main_exists(Table* t) {
 
 map_Fn tmp59 =  t ->fns ;
 array_string keys_tmp59 = map_keys(& tmp59 ); 
 for (int l = 0; l < keys_tmp59 .len; l++) {
   string _ = ((string*)keys_tmp59 .data)[l];
 Fn f = {0}; map_get(tmp59, _, & f);
 
 
 if (string_eq( f .name , tos2((byte*)"main") ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 Var Table_find_const(Table* t, string name) {
 
 array_Var tmp60 =  t ->consts;
 ;
for (int tmp61 = 0; tmp61 < tmp60 .len; tmp61 ++) {
 Var c = ((Var *) tmp60.data)[tmp61];
 
 
 if (string_eq( c .name , name ) ) {
 
return  c ;
 
 }
 ;
 
 }
 ;
 
return  (Var) { .typ = tos("", 0) , .name = tos("", 0) , .is_arg = 0 , .is_const = 0 , .is_import_const = 0 , .args = new_array(0, 1, sizeof(Var)) , .attr = tos("", 0) , .is_mut = 0 , .is_alloc = 0 , .ptr = 0 , .ref = 0 , .parent_fn = tos("", 0) , .mod = tos("", 0) , .line_nr = 0 , .is_global = 0 , .is_used = 0 , .is_changed = 0 , .scope_level = 0 } ;
 
 
 }
 string Table_cgen_name(Table* table, Fn* f) {
 
string name= f ->name ;
 
 if ( f ->is_method ) {
 
 name  =  _STR("%.*s_%.*s", f ->receiver_typ.len, f ->receiver_typ.str, f ->name.len, f ->name.str) ;
 
 name  =  string_replace( name , tos2((byte*)" ") , tos2((byte*)"") ) ;
 
 name  =  string_replace( name , tos2((byte*)"*") , tos2((byte*)"") ) ;
 
 name  =  string_replace( name , tos2((byte*)"+") , tos2((byte*)"plus") ) ;
 
 name  =  string_replace( name , tos2((byte*)"-") , tos2((byte*)"minus") ) ;
 
 }
 ;
 
 if (string_eq( f ->mod , tos2((byte*)"builtin") )  &&  array_string_contains( main__CReserved , f ->name ) ) {
 
return  _STR("v_%.*s", name.len, name.str) ;
 
 }
 ;
 
 if ( table ->obfuscate  && string_ne( f ->name , tos2((byte*)"main") )  && string_ne( f ->name , tos2((byte*)"WinMain") )  && string_ne( f ->mod , tos2((byte*)"builtin") )  &&  ! f ->is_c  && string_ne( f ->mod , tos2((byte*)"darwin") )  && string_ne( f ->mod , tos2((byte*)"os") )  &&  ! string_contains( f ->name , tos2((byte*)"window_proc") )  && string_ne( f ->name , tos2((byte*)"gg__vec2") )  && string_ne( f ->name , tos2((byte*)"build_token_str") )  && string_ne( f ->name , tos2((byte*)"build_keys") )  && string_ne( f ->mod , tos2((byte*)"json") )  &&  ! string_ends_with( name , tos2((byte*)"_str") )  &&  ! string_contains( name , tos2((byte*)"contains") ) ) {
  
 int tmp63 = 0; bool tmp64 = map_get( table ->obf_ids , name, & tmp63); 

int idx= tmp63 ;
 
 if ( idx == 0 ) {
 
 table ->fn_cnt ++ ;
  
 int tmp66 =  table ->fn_cnt; 

map__set(& table ->obf_ids , name , & tmp66) ;
 
 idx  =  table ->fn_cnt ;
 
 }
 ;
 
string old= name ;
 
 name  =  _STR("f_%d", idx) ;
 
printf( "%.*s ==> %.*s\n", old.len, old.str, name.len, name.str ) ;
 
 }
 ;
 
return  name ;
 
 
 }
 string Table_cgen_name_type_pair(Table* table, string name, string typ) {
 
 if ( typ .len > 0  &&  string_at( typ , 0) == '[' ) {
 
string tmp= string_all_after( typ , tos2((byte*)"]") ) ;
 
string size= string_all_before( typ , tos2((byte*)"]") ) ;
 
return  _STR("%.*s %.*s  %.*s ]", tmp.len, tmp.str, name.len, name.str, size.len, size.str) ;
 
 }
  else  if ( string_starts_with( typ , tos2((byte*)"fn (") ) ) {
 
Type* T= Table_find_type(& /* ? */* table , typ ) ;
 
 if (string_eq( T ->name , tos2((byte*)"") ) ) {
 
 println ( tos2((byte*)"this should never happen") ) ;
 
 v_exit ( 1 ) ;
 
 }
 ;
 
string str_args= Fn_str_args(& /* ? */ T ->func , table ) ;
 
return  _STR("%.*s (*%.*s)( %.*s /*FFF*/ )", T ->func .typ.len, T ->func .typ.str, name.len, name.str, str_args.len, str_args.str) ;
 
 }
  else  if (string_eq( typ , tos2((byte*)"tm") ) ) {
 
return  _STR("struct /*TM*/ tm %.*s", name.len, name.str) ;
 
 }
 ;
 
return  _STR("%.*s %.*s", typ.len, typ.str, name.len, name.str) ;
 
 
 }
 bool is_valid_int_const(string val, string typ) {
 
int x= string_int( val ) ;
 
 if ( string_eq( typ,  tos2((byte*)"byte") ) ||   string_eq( typ,  tos2((byte*)"u8") )) { /* case */
 
return  0 <= x  &&  x <= math__MaxU8 ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"u16") )) { /* case */
 
return  0 <= x  &&  x <= math__MaxU16 ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i8") )) { /* case */
 
return  math__MinI8 <= x  &&  x <= math__MaxI8 ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i16") )) { /* case */
 
return  math__MinI16 <= x  &&  x <= math__MaxI16 ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"int") ) ||   string_eq( typ,  tos2((byte*)"i32") )) { /* case */
 
return  math__MinI32 <= x  &&  x <= math__MaxI32 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 void Table_register_generic_fn(Table* t, string fn_name) {
 
_PUSH(& t ->generic_fns , ( (GenTable) { fn_name ,new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) } ), tmp75, GenTable) ;
 
 
 }
 array_string Table_fn_gen_types(Table* t, string fn_name) {
 
 array_GenTable tmp76 =  t ->generic_fns ;
 ;
for (int _ = 0; _ < tmp76 .len; _ ++) {
 GenTable f = ((GenTable *) tmp76 . data)[_];
 
 
 if (string_eq( f .fn_name , fn_name ) ) {
 
return  f .types ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void Table_register_generic_fn_type(Table* t, string fn_name, string typ) {
 
 array_GenTable tmp77 =  t ->generic_fns ;
 ;
for (int i = 0; i < tmp77 .len; i ++) {
 GenTable f = ((GenTable *) tmp77 . data)[i];
 
 
 if (string_eq( f .fn_name , fn_name ) ) {
 
_PUSH(& ( *(GenTable*) array__get( t ->generic_fns , i) ) .types , ( typ ), tmp80, string) ;
 
 return ;
 
 }
 ;
 
 }
 ;
 
 
 }
 string Parser_typ_to_fmt(Parser* p, string typ, int level) {
 
Type* t= Table_find_type(& /* ? */* p ->table , typ ) ;
 
 if ( t ->is_enum ) {
 
return  tos2((byte*)"%d") ;
 
 }
 ;
 
 if ( string_eq( typ,  tos2((byte*)"string") )) { /* case */
 
return  tos2((byte*)"%.*s") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"ustring") )) { /* case */
 
return  tos2((byte*)"%.*s") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"byte") ) ||   string_eq( typ,  tos2((byte*)"int") ) ||   string_eq( typ,  tos2((byte*)"char") ) ||   string_eq( typ,  tos2((byte*)"byte") ) ||   string_eq( typ,  tos2((byte*)"bool") ) ||   string_eq( typ,  tos2((byte*)"u32") ) ||   string_eq( typ,  tos2((byte*)"i32") ) ||   string_eq( typ,  tos2((byte*)"i16") ) ||   string_eq( typ,  tos2((byte*)"u16") ) ||   string_eq( typ,  tos2((byte*)"i8") ) ||   string_eq( typ,  tos2((byte*)"u8") )) { /* case */
 
return  tos2((byte*)"%d") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"f64") ) ||   string_eq( typ,  tos2((byte*)"f32") )) { /* case */
 
return  tos2((byte*)"%f") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"i64") ) ||   string_eq( typ,  tos2((byte*)"u64") )) { /* case */
 
return  tos2((byte*)"%lld") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"byte*") ) ||   string_eq( typ,  tos2((byte*)"byteptr") )) { /* case */
 
return  tos2((byte*)"%s") ;
 
 }
 else  if ( string_eq( typ,  tos2((byte*)"void") )) { /* case */
 
 Parser_error( p , tos2((byte*)"cannot interpolate this value") ) ;
 
 }
 else  { // default:
 
 if ( string_ends_with( typ , tos2((byte*)"*") ) ) {
 
return  tos2((byte*)"%p") ;
 
 }
 ;
 
 }
 ;
 
 if (string_ne( t ->parent , tos2((byte*)"") )  &&  level == 0 ) {
 
return  Parser_typ_to_fmt( p , t ->parent , level + 1 ) ;
 
 }
 ;
 
return  tos2((byte*)"") ;
 
 
 }
 bool is_compile_time_const(string s) {
 
 s  =  string_trim_space( s ) ;
 
 if (string_eq( s , tos2((byte*)"") ) ) {
 
return  0 ;
 
 }
 ;
 
 if ( string_contains( s , tos2((byte*)"\'") ) ) {
 
return  1 ;
 
 }
 ;
 
 string tmp82 =  s;
 ;
for (int tmp83 = 0; tmp83 < tmp82 .len; tmp83 ++) {
 byte c = ((byte *) tmp82.str)[tmp83];
 
 
 if ( ! ( ( c >= '0'  &&  c <= '9' )  ||  c == '.' ) ) {
 
return  0 ;
 
 }
 ;
 
 }
 ;
 
return  1 ;
 
 
 }
 string Table_qualify_module(Table* table, string mod, string file_path) {
 
 array_string tmp84 =  table ->imports;
 ;
for (int tmp85 = 0; tmp85 < tmp84 .len; tmp85 ++) {
 string m = ((string *) tmp84.data)[tmp85];
 
 
 if ( string_contains( m , tos2((byte*)".") )  &&  string_contains( m , mod ) ) {
 
array_string m_parts= string_split( m , tos2((byte*)".") ) ;
 
string m_path= array_string_join( m_parts , tos2((byte*)"/") ) ;
 
 if (string_eq( mod , ( *(string*) array__get( m_parts , m_parts .len - 1) ) )  &&  string_contains( file_path , m_path ) ) {
 
return  m ;
 
 }
 ;
 
 }
 ;
 
 }
 ;
 
return  mod ;
 
 
 }
 FileImportTable* new_file_import_table(string file_path) {
 
return  ALLOC_INIT(FileImportTable, { .file_path =  file_path , .imports =  new_map(1, sizeof(string)) , .module_name = tos("", 0) , } ) ;
 
 
 }
 bool FileImportTable_known_import(FileImportTable* fit, string mod) {
 
return _IN_MAP(  mod ,  fit ->imports )  ||  FileImportTable_is_aliased(& /* ? */* fit , mod ) ;
 
 
 }
 void FileImportTable_register_import(FileImportTable* fit, string mod) {
 
 FileImportTable_register_alias( fit , mod , mod ) ;
 
 
 }
 void FileImportTable_register_alias(FileImportTable* fit, string alias, string mod) {
 
 if (_IN_MAP(  alias ,  fit ->imports ) ) {
 
 v_panic ( _STR("cannot import %.*s as %.*s: import name %.*s already in use in \"%.*s\".", mod.len, mod.str, alias.len, alias.str, alias.len, alias.str, fit ->file_path.len, fit ->file_path.str) ) ;
 
 return ;
 
 }
 ;
 
 if ( string_contains( mod , tos2((byte*)".internal.") ) ) {
 
array_string mod_parts= string_split( mod , tos2((byte*)".") ) ;
 
array_string internal_mod_parts=new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   }) ;
 
 array_string tmp92 =  mod_parts;
 ;
for (int tmp93 = 0; tmp93 < tmp92 .len; tmp93 ++) {
 string part = ((string *) tmp92.data)[tmp93];
 
 
 if (string_eq( part , tos2((byte*)"internal") ) ) {
 
 break
 ;
 
 }
 ;
 
_PUSH(& internal_mod_parts , ( part ), tmp94, string) ;
 
 }
 ;
 
string internal_parent= array_string_join( internal_mod_parts , tos2((byte*)".") ) ;
 
 if ( ! string_starts_with( fit ->module_name , internal_parent ) ) {
 
 v_panic ( _STR("module %.*s can only be imported internally by libs.", mod.len, mod.str) ) ;
 
 }
 ;
 
 }
 ;
  
 string tmp96 =  mod; 

map__set(& fit ->imports , alias , & tmp96) ;
 
 
 }
 bool FileImportTable_known_alias(FileImportTable* fit, string alias) {
 
return _IN_MAP(  alias ,  fit ->imports ) ;
 
 
 }
 bool FileImportTable_is_aliased(FileImportTable* fit, string mod) {
 
 map_string tmp97 =  fit ->imports ;
 array_string keys_tmp97 = map_keys(& tmp97 ); 
 for (int l = 0; l < keys_tmp97 .len; l++) {
   string _ = ((string*)keys_tmp97 .data)[l];
 string val = {0}; map_get(tmp97, _, & val);
 
 
 if (string_eq( val , mod ) ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 string FileImportTable_resolve_alias(FileImportTable* fit, string alias) {
  
 string tmp98 = tos("", 0); bool tmp99 = map_get( fit ->imports , alias, & tmp98); 
 
 if (!tmp99) tmp98 = tos("", 0); 

return  tmp98 ;
 
 
 }
 map_int build_keys() {
 
map_int res= new_map(1, sizeof(int)) ;
 
 for (
int t= ((int)( main__Token_keyword_beg ) ) + 1  ;  t < ((int)( main__Token_keyword_end ) )  ;  t ++ ) { 
 
 
string key= ( *(string*) array__get( main__TokenStr , t) ) ;
  
 int tmp6 =  ((int)( t ) ); 

map__set(& res , key , & tmp6) ;
 
 }
 ;
 
return  res ;
 
 
 }
 array_string build_token_str() {
  
 string tmp7 =  tos2((byte*)""); 

array_string s= array_repeat(&tmp7,  main__NrTokens , sizeof(string) ) ;
  
 string tmp9 =  tos2((byte*)""); 

array_set(&/*q*/ s , main__Token_keyword_beg , & tmp9) ;
  
 string tmp10 =  tos2((byte*)""); 

array_set(&/*q*/ s , main__Token_keyword_end , & tmp10) ;
  
 string tmp11 =  tos2((byte*)".eof"); 

array_set(&/*q*/ s , main__Token_eof , & tmp11) ;
  
 string tmp12 =  tos2((byte*)".name"); 

array_set(&/*q*/ s , main__Token_name , & tmp12) ;
  
 string tmp13 =  tos2((byte*)".number"); 

array_set(&/*q*/ s , main__Token_number , & tmp13) ;
  
 string tmp14 =  tos2((byte*)"STR"); 

array_set(&/*q*/ s , main__Token_str , & tmp14) ;
  
 string tmp15 =  tos2((byte*)".chartoken"); 

array_set(&/*q*/ s , main__Token_chartoken , & tmp15) ;
  
 string tmp16 =  tos2((byte*)"+"); 

array_set(&/*q*/ s , main__Token_plus , & tmp16) ;
  
 string tmp17 =  tos2((byte*)"-"); 

array_set(&/*q*/ s , main__Token_minus , & tmp17) ;
  
 string tmp18 =  tos2((byte*)"*"); 

array_set(&/*q*/ s , main__Token_mul , & tmp18) ;
  
 string tmp19 =  tos2((byte*)"/"); 

array_set(&/*q*/ s , main__Token_div , & tmp19) ;
  
 string tmp20 =  tos2((byte*)"%"); 

array_set(&/*q*/ s , main__Token_mod , & tmp20) ;
  
 string tmp21 =  tos2((byte*)"^"); 

array_set(&/*q*/ s , main__Token_xor , & tmp21) ;
  
 string tmp22 =  tos2((byte*)"~"); 

array_set(&/*q*/ s , main__Token_bit_not , & tmp22) ;
  
 string tmp23 =  tos2((byte*)"|"); 

array_set(&/*q*/ s , main__Token_pipe , & tmp23) ;
  
 string tmp24 =  tos2((byte*)"#"); 

array_set(&/*q*/ s , main__Token_hash , & tmp24) ;
  
 string tmp25 =  tos2((byte*)"&"); 

array_set(&/*q*/ s , main__Token_amp , & tmp25) ;
  
 string tmp26 =  tos2((byte*)"++"); 

array_set(&/*q*/ s , main__Token_inc , & tmp26) ;
  
 string tmp27 =  tos2((byte*)"--"); 

array_set(&/*q*/ s , main__Token_dec , & tmp27) ;
  
 string tmp28 =  tos2((byte*)"&&"); 

array_set(&/*q*/ s , main__Token_and , & tmp28) ;
  
 string tmp29 =  tos2((byte*)"||"); 

array_set(&/*q*/ s , main__Token_logical_or , & tmp29) ;
  
 string tmp30 =  tos2((byte*)"!"); 

array_set(&/*q*/ s , main__Token_not , & tmp30) ;
  
 string tmp31 =  tos2((byte*)"."); 

array_set(&/*q*/ s , main__Token_dot , & tmp31) ;
  
 string tmp32 =  tos2((byte*)".."); 

array_set(&/*q*/ s , main__Token_dotdot , & tmp32) ;
  
 string tmp33 =  tos2((byte*)","); 

array_set(&/*q*/ s , main__Token_comma , & tmp33) ;
  
 string tmp34 =  tos2((byte*)";"); 

array_set(&/*q*/ s , main__Token_semicolon , & tmp34) ;
  
 string tmp35 =  tos2((byte*)":"); 

array_set(&/*q*/ s , main__Token_colon , & tmp35) ;
  
 string tmp36 =  tos2((byte*)"=>"); 

array_set(&/*q*/ s , main__Token_arrow , & tmp36) ;
  
 string tmp37 =  tos2((byte*)"="); 

array_set(&/*q*/ s , main__Token_assign , & tmp37) ;
  
 string tmp38 =  tos2((byte*)":="); 

array_set(&/*q*/ s , main__Token_decl_assign , & tmp38) ;
  
 string tmp39 =  tos2((byte*)"+="); 

array_set(&/*q*/ s , main__Token_plus_assign , & tmp39) ;
  
 string tmp40 =  tos2((byte*)"-="); 

array_set(&/*q*/ s , main__Token_minus_assign , & tmp40) ;
  
 string tmp41 =  tos2((byte*)"*="); 

array_set(&/*q*/ s , main__Token_mult_assign , & tmp41) ;
  
 string tmp42 =  tos2((byte*)"/="); 

array_set(&/*q*/ s , main__Token_div_assign , & tmp42) ;
  
 string tmp43 =  tos2((byte*)"^="); 

array_set(&/*q*/ s , main__Token_xor_assign , & tmp43) ;
  
 string tmp44 =  tos2((byte*)"%="); 

array_set(&/*q*/ s , main__Token_mod_assign , & tmp44) ;
  
 string tmp45 =  tos2((byte*)"|="); 

array_set(&/*q*/ s , main__Token_or_assign , & tmp45) ;
  
 string tmp46 =  tos2((byte*)"&="); 

array_set(&/*q*/ s , main__Token_and_assign , & tmp46) ;
  
 string tmp47 =  tos2((byte*)">>="); 

array_set(&/*q*/ s , main__Token_righ_shift_assign , & tmp47) ;
  
 string tmp48 =  tos2((byte*)"<<="); 

array_set(&/*q*/ s , main__Token_left_shift_assign , & tmp48) ;
  
 string tmp49 =  tos2((byte*)"{"); 

array_set(&/*q*/ s , main__Token_lcbr , & tmp49) ;
  
 string tmp50 =  tos2((byte*)"}"); 

array_set(&/*q*/ s , main__Token_rcbr , & tmp50) ;
  
 string tmp51 =  tos2((byte*)"("); 

array_set(&/*q*/ s , main__Token_lpar , & tmp51) ;
  
 string tmp52 =  tos2((byte*)")"); 

array_set(&/*q*/ s , main__Token_rpar , & tmp52) ;
  
 string tmp53 =  tos2((byte*)"["); 

array_set(&/*q*/ s , main__Token_lsbr , & tmp53) ;
  
 string tmp54 =  tos2((byte*)"]"); 

array_set(&/*q*/ s , main__Token_rsbr , & tmp54) ;
  
 string tmp55 =  tos2((byte*)"=="); 

array_set(&/*q*/ s , main__Token_eq , & tmp55) ;
  
 string tmp56 =  tos2((byte*)"!="); 

array_set(&/*q*/ s , main__Token_ne , & tmp56) ;
  
 string tmp57 =  tos2((byte*)">"); 

array_set(&/*q*/ s , main__Token_gt , & tmp57) ;
  
 string tmp58 =  tos2((byte*)"<"); 

array_set(&/*q*/ s , main__Token_lt , & tmp58) ;
  
 string tmp59 =  tos2((byte*)">="); 

array_set(&/*q*/ s , main__Token_ge , & tmp59) ;
  
 string tmp60 =  tos2((byte*)"<="); 

array_set(&/*q*/ s , main__Token_le , & tmp60) ;
  
 string tmp61 =  tos2((byte*)"?"); 

array_set(&/*q*/ s , main__Token_question , & tmp61) ;
  
 string tmp62 =  tos2((byte*)"<<"); 

array_set(&/*q*/ s , main__Token_left_shift , & tmp62) ;
  
 string tmp63 =  tos2((byte*)">>"); 

array_set(&/*q*/ s , main__Token_righ_shift , & tmp63) ;
  
 string tmp64 =  tos2((byte*)"NLL"); 

array_set(&/*q*/ s , main__Token_nl , & tmp64) ;
  
 string tmp65 =  tos2((byte*)"$"); 

array_set(&/*q*/ s , main__Token_dollar , & tmp65) ;
  
 string tmp66 =  tos2((byte*)"assert"); 

array_set(&/*q*/ s , main__Token_key_assert , & tmp66) ;
  
 string tmp67 =  tos2((byte*)"struct"); 

array_set(&/*q*/ s , main__Token_key_struct , & tmp67) ;
  
 string tmp68 =  tos2((byte*)"if"); 

array_set(&/*q*/ s , main__Token_key_if , & tmp68) ;
  
 string tmp69 =  tos2((byte*)"else"); 

array_set(&/*q*/ s , main__Token_key_else , & tmp69) ;
  
 string tmp70 =  tos2((byte*)"return"); 

array_set(&/*q*/ s , main__Token_key_return , & tmp70) ;
  
 string tmp71 =  tos2((byte*)"module"); 

array_set(&/*q*/ s , main__Token_key_module , & tmp71) ;
  
 string tmp72 =  tos2((byte*)"sizeof"); 

array_set(&/*q*/ s , main__Token_key_sizeof , & tmp72) ;
  
 string tmp73 =  tos2((byte*)"go"); 

array_set(&/*q*/ s , main__Token_key_go , & tmp73) ;
  
 string tmp74 =  tos2((byte*)"goto"); 

array_set(&/*q*/ s , main__Token_key_goto , & tmp74) ;
  
 string tmp75 =  tos2((byte*)"const"); 

array_set(&/*q*/ s , main__Token_key_const , & tmp75) ;
  
 string tmp76 =  tos2((byte*)"mut"); 

array_set(&/*q*/ s , main__Token_key_mut , & tmp76) ;
  
 string tmp77 =  tos2((byte*)"type"); 

array_set(&/*q*/ s , main__Token_key_type , & tmp77) ;
  
 string tmp78 =  tos2((byte*)"for"); 

array_set(&/*q*/ s , main__Token_key_for , & tmp78) ;
  
 string tmp79 =  tos2((byte*)"switch"); 

array_set(&/*q*/ s , main__Token_key_switch , & tmp79) ;
  
 string tmp80 =  tos2((byte*)"case"); 

array_set(&/*q*/ s , main__Token_key_case , & tmp80) ;
  
 string tmp81 =  tos2((byte*)"fn"); 

array_set(&/*q*/ s , main__Token_func , & tmp81) ;
  
 string tmp82 =  tos2((byte*)"true"); 

array_set(&/*q*/ s , main__Token_key_true , & tmp82) ;
  
 string tmp83 =  tos2((byte*)"false"); 

array_set(&/*q*/ s , main__Token_key_false , & tmp83) ;
  
 string tmp84 =  tos2((byte*)"continue"); 

array_set(&/*q*/ s , main__Token_key_continue , & tmp84) ;
  
 string tmp85 =  tos2((byte*)"break"); 

array_set(&/*q*/ s , main__Token_key_break , & tmp85) ;
  
 string tmp86 =  tos2((byte*)"import"); 

array_set(&/*q*/ s , main__Token_key_import , & tmp86) ;
  
 string tmp87 =  tos2((byte*)"embed"); 

array_set(&/*q*/ s , main__Token_key_embed , & tmp87) ;
  
 string tmp88 =  tos2((byte*)"default"); 

array_set(&/*q*/ s , main__Token_key_default , & tmp88) ;
  
 string tmp89 =  tos2((byte*)"enum"); 

array_set(&/*q*/ s , main__Token_key_enum , & tmp89) ;
  
 string tmp90 =  tos2((byte*)"interface"); 

array_set(&/*q*/ s , main__Token_key_interface , & tmp90) ;
  
 string tmp91 =  tos2((byte*)"pub"); 

array_set(&/*q*/ s , main__Token_key_pub , & tmp91) ;
  
 string tmp92 =  tos2((byte*)"import_const"); 

array_set(&/*q*/ s , main__Token_key_import_const , & tmp92) ;
  
 string tmp93 =  tos2((byte*)"in"); 

array_set(&/*q*/ s , main__Token_key_in , & tmp93) ;
  
 string tmp94 =  tos2((byte*)"atomic"); 

array_set(&/*q*/ s , main__Token_key_atomic , & tmp94) ;
  
 string tmp95 =  tos2((byte*)"or"); 

array_set(&/*q*/ s , main__Token_key_orelse , & tmp95) ;
  
 string tmp96 =  tos2((byte*)"__global"); 

array_set(&/*q*/ s , main__Token_key_global , & tmp96) ;
  
 string tmp97 =  tos2((byte*)"union"); 

array_set(&/*q*/ s , main__Token_key_union , & tmp97) ;
  
 string tmp98 =  tos2((byte*)"static"); 

array_set(&/*q*/ s , main__Token_key_static , & tmp98) ;
  
 string tmp99 =  tos2((byte*)"as"); 

array_set(&/*q*/ s , main__Token_key_as , & tmp99) ;
  
 string tmp100 =  tos2((byte*)"defer"); 

array_set(&/*q*/ s , main__Token_key_defer , & tmp100) ;
  
 string tmp101 =  tos2((byte*)"match"); 

array_set(&/*q*/ s , main__Token_key_match , & tmp101) ;
 
return  s ;
 
 
 }
 Token key_to_token(string key) {
  
 int tmp102 = 0; bool tmp103 = map_get( main__KEYWORDS , key, & tmp102); 

Token a= ((Token)( tmp102 ) ) ;
 
return  a ;
 
 
 }
 bool is_key(string key) {
 
return  ((int)( key_to_token ( key ) ) ) > 0 ;
 
 
 }
 string Token_str(Token t) {
 
return  ( *(string*) array__get( main__TokenStr , ((int)( t ) )) ) ;
 
 
 }
 bool Token_is_decl(Token t) {
 
return  t == main__Token_key_enum  ||  t == main__Token_key_interface  ||  t == main__Token_func  ||  t == main__Token_key_struct  ||  t == main__Token_key_type  ||  t == main__Token_key_const  ||  t == main__Token_key_import_const  ||  t == main__Token_key_pub  ||  t == main__Token_eof ;
 
 
 }
 bool Token_is_assign(Token t) {
 
return _IN(Token,  t ,  main__AssignTokens ) ;
 
 
 }
 bool array_Token_contains(array_Token t, Token val) {
 
 array_Token tmp107 =  t;
 ;
for (int tmp108 = 0; tmp108 < tmp107 .len; tmp108 ++) {
 Token tt = ((Token *) tmp107.data)[tmp108];
 
 
 if ( tt == val ) {
 
return  1 ;
 
 }
 ;
 
 }
 ;
 
return  0 ;
 
 
 }
 void Scanner_fgen(Scanner* scanner, string s) {
 
 if ( scanner ->fmt_line_empty ) {
 
 s  = string_add( strings__repeat ( '\t' , scanner ->fmt_indent ) , s ) ;
 
 }
 ;
 
 strings__Builder_write(& /* ? */ scanner ->fmt_out , s ) ;
 
 scanner ->fmt_line_empty  =  0 ;
 
 
 }
 void Scanner_fgenln(Scanner* scanner, string s) {
 
 if ( scanner ->fmt_line_empty ) {
 
 s  = string_add( strings__repeat ( '\t' , scanner ->fmt_indent ) , s ) ;
 
 }
 ;
 
 strings__Builder_writeln(& /* ? */ scanner ->fmt_out , s ) ;
 
 scanner ->fmt_line_empty  =  1 ;
 
 
 }
 void Parser_fgen(Parser* p, string s) {
 
 Scanner_fgen( p ->scanner , s ) ;
 
 
 }
 void Parser_fspace(Parser* p) {
 
 Parser_fgen( p , tos2((byte*)" ") ) ;
 
 
 }
 void Parser_fgenln(Parser* p, string s) {
 
 Scanner_fgenln( p ->scanner , s ) ;
 
 
 }
 Token Parser_peek(Parser* p) {
 
 while (1) { 
 
 p ->cgen ->line  =  p ->scanner ->line_nr + 1 ;
 
Token tok= Scanner_peek( p ->scanner ) ;
 
 if ( tok != main__Token_nl ) {
 
return  tok ;
 
 }
 ;
 
 }
 ;
 
 
 }
 void Parser_fmt_inc(Parser* p) {
 
 p ->scanner ->fmt_indent ++ ;
 
 
 }
 void Parser_fmt_dec(Parser* p) {
 
 p ->scanner ->fmt_indent -- ;
 
 
 }
 void init_consts() { 
#ifdef _WIN32
 _setmode(_fileno(stdout), _O_U8TEXT);
SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | 0x0004); 
// ENABLE_VIRTUAL_TERMINAL_PROCESSING
#endif
 g_str_buf=malloc(1000);
os__FILE_ATTR_READONLY =  0x1;
os__FILE_ATTR_HIDDEN =  0x2;
os__FILE_ATTR_SYSTEM =  0x4;
os__FILE_ATTR_DIRECTORY =  0x10;
os__FILE_ATTR_ARCHIVE =  0x20;
os__FILE_ATTR_DEVICE =  0x40;
os__FILE_ATTR_NORMAL =  0x80;
os__FILE_ATTR_TEMPORARY =  0x100;
os__FILE_ATTR_SPARSE_FILE =  0x200;
os__FILE_ATTR_REPARSE_POINT =  0x400;
os__FILE_ATTR_COMPRESSED =  0x800;
os__FILE_ATTR_OFFLINE =  0x1000;
os__FILE_ATTR_NOT_CONTENT_INDEXED =  0x2000;
os__FILE_ATTR_ENCRYPTED =  0x4000;
os__FILE_ATTR_INTEGRITY_STREAM =  0x8000;
os__FILE_ATTR_VIRTUAL =  0x10000;
os__FILE_ATTR_NO_SCRUB_DATA =  0x20000;
os__FILE_TYPE_DISK =  0x1;
os__FILE_TYPE_CHAR =  0x2;
os__FILE_TYPE_PIPE =  0x3;
os__FILE_TYPE_UNKNOWN =  0x0;
os__FILE_INVALID_FILE_ID =  ( - 1 );
os__S_IFMT =  0xF000;
os__S_IFDIR =  0x4000;
os__INVALID_HANDLE_VALUE =  - 1;
os__STD_INPUT_HANDLE =  - 10;
os__STD_OUTPUT_HANDLE =  - 11;
os__STD_ERROR_HANDLE =  - 12;
os__ENABLE_ECHO_INPUT =  0x0004;
os__ENABLE_EXTENDED_FLAGS =  0x0080;
os__ENABLE_INSERT_MODE =  0x0020;
os__ENABLE_LINE_INPUT =  0x0002;
os__ENABLE_MOUSE_INPUT =  0x0010;
os__ENABLE_PROCESSED_INPUT =  0x0001;
os__ENABLE_QUICK_EDIT_MODE =  0x0040;
os__ENABLE_WINDOW_INPUT =  0x0008;
os__ENABLE_VIRTUAL_TERMINAL_INPUT =  0x0200;
os__ENABLE_PROCESSED_OUTPUT =  0x0001;
os__ENABLE_WRAP_AT_EOL_OUTPUT =  0x0002;
os__ENABLE_VIRTUAL_TERMINAL_PROCESSING =  0x0004;
os__DISABLE_NEWLINE_AUTO_RETURN =  0x0008;
os__ENABLE_LVB_GRID_WORLDWIDE =  0x0010;
os__args = new_array_from_c_array(0, 0, sizeof(string), (string[]) {EMPTY_STRUCT_INIT   });
os__PathSeparator =  tos2((byte*)"/");
math__Log2E =  1.0 / math__Ln2;
math__Log10E =  1.0 / math__Ln10;
math__MaxI8 =  ( 1  <<  7 ) - 1;
math__MinI8 =  - 1  <<  7;
math__MaxI16 =  ( 1  <<  15 ) - 1;
math__MinI16 =  - 1  <<  15;
math__MaxI32 =  ( 1  <<  31 ) - 1;
math__MinI32 =  - 1  <<  31;
math__MaxU8 =  ( 1  <<  8 ) - 1;
math__MaxU16 =  ( 1  <<  16 ) - 1;
math__MaxU32 =  ( 1  <<  32 ) - 1;
math__MaxU64 =  ( 1  <<  64 ) - 1;
time__MonthDays = new_array_from_c_array(12, 12, sizeof(int), (int[]) {  31 ,  28 ,  31 ,  30 ,  31 ,  30 ,  31 ,  31 ,  30 ,  31 ,  30 ,  31  });
time__absoluteZeroYear =  ((i64)( - 292277022399 ) );
time__secondsPerHour =  60 * time__secondsPerMinute;
time__secondsPerDay =  24 * time__secondsPerHour;
time__secondsPerWeek =  7 * time__secondsPerDay;
time__daysPer400Years =  365 * 400 + 97;
time__daysPer100Years =  365 * 100 + 24;
time__daysPer4Years =  365 * 4 + 1;
time__daysBefore = new_array_from_c_array(13, 13, sizeof(int), (int[]) {  0 ,  31 ,  31 + 28 ,  31 + 28 + 31 ,  31 + 28 + 31 + 30 ,  31 + 28 + 31 + 30 + 31 ,  31 + 28 + 31 + 30 + 31 + 30 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 ,  31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30 + 31 ,   });
time__Months =  tos2((byte*)"JanFebMarAprMayJunJulAugSepOctNovDec");
time__Days =  tos2((byte*)"MonTueWedThuFriSatSun");
main__Version =  tos2((byte*)"0.1.17");
main__SupportedPlatforms = new_array_from_c_array(8, 8, sizeof(string), (string[]) {  tos2((byte*)"windows") ,  tos2((byte*)"mac") ,  tos2((byte*)"linux") ,  tos2((byte*)"freebsd") ,  tos2((byte*)"openbsd") ,  tos2((byte*)"netbsd") ,  tos2((byte*)"dragonfly") ,  tos2((byte*)"msvc")  });
main__ModPath =  modules_path ( );
main__HelpText =  tos2((byte*)"\nUsage: v [options] [file | directory]\n\nOptions:\n  -                 Read from stdin (Default; Interactive mode if in a tty)\n  -h, help          Display this information.\n  -v, version       Display compiler version.\n  -lib              Generate object file.\n  -prod             Build an optimized executable.\n  -o <file>         Place output into <file>.\n  -obf              Obfuscate the resulting binary.\n  -show_c_cmd       Print the full C compilation command and how much time it took. \n  -debug            Leave a C file for debugging in .program.c. \n  -live             Enable hot code reloading (required by functions marked with [live]). \n  fmt               Run vfmt to format the source code. \n  up                Update V. \n  run               Build and execute a V program. You can add arguments after the file name.\n\n\nFiles:\n  <file>_test.v     Test file.\n");
main__EmptyFn =  ALLOC_INIT(Fn, { .name = tos("", 0) , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } );
main__MainFn =  ALLOC_INIT(Fn, { .name =  tos2((byte*)"main") , .mod = tos("", 0) , .local_vars = new_array(0, 1, sizeof(Var)) , .var_idx = 0 , .args = new_array(0, 1, sizeof(Var)) , .is_interface = 0 , .scope_level = 0 , .typ = tos("", 0) , .is_c = 0 , .receiver_typ = tos("", 0) , .is_public = 0 , .is_method = 0 , .returns_error = 0 , .is_decl = 0 , .defer_text = tos("", 0) } );
main__and_or_error = string_add( tos2((byte*)"use `()` to make the boolean expression clear\n") , tos2((byte*)"for example: `(a && b) || c` instead of `a && b || c`") );
main__CReserved = new_array_from_c_array(10, 10, sizeof(string), (string[]) {  tos2((byte*)"exit") ,  tos2((byte*)"unix") ,  tos2((byte*)"print") ,  tos2((byte*)"error") ,  tos2((byte*)"malloc") ,  tos2((byte*)"calloc") ,  tos2((byte*)"char") ,  tos2((byte*)"free") ,  tos2((byte*)"panic") ,  tos2((byte*)"register")  });
main__number_types = new_array_from_c_array(13, 13, sizeof(string), (string[]) {  tos2((byte*)"number") ,  tos2((byte*)"int") ,  tos2((byte*)"i8") ,  tos2((byte*)"u8") ,  tos2((byte*)"i16") ,  tos2((byte*)"u16") ,  tos2((byte*)"i32") ,  tos2((byte*)"u32") ,  tos2((byte*)"byte") ,  tos2((byte*)"i64") ,  tos2((byte*)"u64") ,  tos2((byte*)"f32") ,  tos2((byte*)"f64")  });
main__float_types = new_array_from_c_array(2, 2, sizeof(string), (string[]) {  tos2((byte*)"f32") ,  tos2((byte*)"f64")  });
main__TokenStr =  build_token_str ( );
main__KEYWORDS =  build_keys ( );
main__AssignTokens = new_array_from_c_array(11, 11, sizeof(Token), (Token[]) {  main__Token_assign ,  main__Token_plus_assign ,  main__Token_minus_assign ,  main__Token_mult_assign ,  main__Token_div_assign ,  main__Token_xor_assign ,  main__Token_mod_assign ,  main__Token_or_assign ,  main__Token_and_assign ,  main__Token_righ_shift_assign ,  main__Token_left_shift_assign  }); 
}
 
string _STR(const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  
	va_end(argptr);
	byte* buf = malloc(len);  
	va_start(argptr, fmt);
	vsprintf(buf, fmt, argptr);
	va_end(argptr);
#ifdef DEBUG_ALLOC 
	puts("_STR:"); 
	puts(buf); 
#endif 
	return tos2(buf);
}

string _STR_TMP(const char *fmt, ...) {
	va_list argptr;
	va_start(argptr, fmt);
	size_t len = vsnprintf(0, 0, fmt, argptr) + 1;  
	va_end(argptr);
	va_start(argptr, fmt);
	vsprintf(g_str_buf, fmt, argptr);
	va_end(argptr);
#ifdef DEBUG_ALLOC 
	//puts("_STR_TMP:"); 
	//puts(g_str_buf); 
#endif 
	return tos2(g_str_buf);
}


