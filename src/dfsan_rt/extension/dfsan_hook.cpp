#include "dtaint.h"
#include "types.h" 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "dfsan_union_t.h"
#include "config.h"
typedef unsigned __int128 uint128_t;

extern struct dfsan_label_info __dfsan_label_info;
extern struct dtaint_map *__afl_dtaint_map;

/**
 * Call hook.
 * __dfsan_hook1 (unsigned id, dfsan_label ptr_label);
 * ex. load inst.
 * __dfsan_hook2 (unsigned id, dfsan_label value_label, dfsan_label ptr_label);
 * ex. store inst.
 * __dfsan_hook2_int128 (unsigned id, dfsan_label value_label, dfsan_label ptr_label);
 * deal with 16 byte value
 * __dfsan_hook3 (unsigned id, dfsan_label ptr_label, dfsan_label c_label, dfsan_label size_label);
 * ex. memset
 * __dfsan_hook4 (unsigned id, dfsan_label dst_label, dfsan_label src_label, dfsan_label size_label);
 * ex. memcpy
 * __dfsan_hook5 (unsigned id, dfsan_label size_label);
 * ex. malloc
 * __dfsan_hook6 (unsigned id, dfsan_label ptr_label);
 * ex. free
 * __dfsan_hook7 (unsigned id, dfsan_label ptr_label, dfsan_label size_label);
 * ex. realloc
 * __dfsan_va_arg_hook1 (unsigned id, dfsan_label ptr_label, unsigned num_of_idx, ...);
 * ex. get_element_ptr inst.
 * 
 */

#ifdef DTAINT_DEBUG

extern "C" __attribute__((visibility("default")))
void __dfsan_hook_debug_dump_offset_t() {

  for (int i = 0; i < DTAINT_MAP_W; i++) {

    if (__afl_dtaint_map->label_info[i].num == 0) continue;

    // fprintf(stderr, "label info: label: %u len: %u num: %u\n", i, 
    //   __afl_dtaint_map->label_info[i].len,
    //   __afl_dtaint_map->label_info[i].num);

    fprintf(stderr, "offset_t: ");
    for (int j = 0; j < __afl_dtaint_map->label_info[i].num; j++) {
      fprintf(stderr, "pos: %u len: %u ", __afl_dtaint_map->offset_t[i][j].pos,
        __afl_dtaint_map->offset_t[i][j].len);
    } fprintf(stderr, "\n");

  }
}

extern "C" __attribute__((constructor(100))) 
void __dfsan_hook_debug_init() {
      
  fprintf(stderr, "__dfsan_debug_init\n");

  if(!__afl_dtaint_map) {
      __afl_dtaint_map = (struct dtaint_map *)malloc(sizeof(struct dtaint_map));
    memset(__afl_dtaint_map, 0, sizeof(struct dtaint_map));
  }

}

extern "C" __attribute__((destructor)) 
void __dfsan_hook_debug_fini() {

  fprintf(stderr, "__dfsan_hook_debug_fini\n");
  if (__afl_dtaint_map) {
  
    __dfsan_hook_debug_dump_offset_t();

  }
  if(__afl_dtaint_map && !getenv(DTAINT_SHM_ENV_VAR)) { 
    free(__afl_dtaint_map);
    __afl_dtaint_map = NULL;
  }

}

#endif

extern "C" __attribute__((visibility("default")))
void __dfsan_hook_debug(unsigned int id, void* ptr, unsigned int src_type, unsigned int rst_type, 
  unsigned int num_of_idx, ...) {
  
  //deal with vararg
  va_list args;
  int size, logged;
  struct hook_va_arg_operand *__hook_va_arg;
  #ifdef DTAINT_DEBUG
 
  #endif
}

extern "C" __attribute__((destructor(0)))
void ___dfsan_hook_fini() {

  if (__afl_dtaint_map && __afl_dtaint_map->status != 1)
    __afl_dtaint_map->status = 9487;
}
/**
 * Copy offset to shm.
 */
void offset_cpy(dfsan_label label) {

  struct offset_node* node = (struct offset_node *)dfsan_union_t_get_offset(label);

  __afl_dtaint_map->label_info[label].num = node->num;
  __afl_dtaint_map->label_info[label].len = node->len;
  
  //move offset
  u32 num;
  if (node->num > DTAINT_MAP_H)
    num = DTAINT_MAP_H;
  else 
    num = node->num;
  
  for (int j = 0; j < num; j++) {

    __afl_dtaint_map->offset_t[label][j].pos = node->tainted[j].pos;
    __afl_dtaint_map->offset_t[label][j].len = node->tainted[j].len;
    
  }

}

/**
 * ex. 1 argument hook.
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook1 (unsigned id, dfsan_label n_label) {
  #ifdef DTAINT_DEBUG

  #endif 
  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (n_label == 0) return;

  if (__afl_dtaint_map->label_info[n_label].num == 0) offset_cpy(n_label);
}
/**
 * ex. store inst.
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook2 (unsigned id, dfsan_label value_label, dfsan_label ptr_label) {
  #ifdef DTAINT_DEBUG
  printf("hook2\n");

  #endif 

  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (value_label != 0 && __afl_dtaint_map->label_info[value_label].num == 0) offset_cpy(value_label);
  if (ptr_label != 0 && __afl_dtaint_map->label_info[ptr_label].num == 0) offset_cpy(ptr_label);

}

extern "C" __attribute__((visibility("default")))
void __dfsan_test () {
  printf("\033[31m out of bound!!!\033[0m\n");
}

/**
 * ex. store inst.
 * deal with 16 byte value
 */
extern "C" __attribute__((visibility("default")))
void  __dfsan_hook2_int128 (unsigned id, dfsan_label value_label, dfsan_label ptr_label) {
  
  #ifdef DTAINT_DEBUG

  #endif 

}
/**
 * ex.memset
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook3 (unsigned id, dfsan_label ptr_label, dfsan_label c_label, 
  dfsan_label size_label) {
  
  #ifdef DTAINT_DEBUG
  //fprintf(stderr, "__dfsan_hook3: id: %u ptr_label: %u c_label: %u size_label: %u\n", 
  //  id, ptr_label, c_label, size_label);
  #endif 

  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (ptr_label == 0 && c_label  == 0 && size_label == 0) return;

  if (ptr_label != 0 && __afl_dtaint_map->label_info[ptr_label].num == 0) offset_cpy(ptr_label);
  if (c_label != 0 && __afl_dtaint_map->label_info[c_label].num == 0) offset_cpy(c_label);
  if (size_label != 0 && __afl_dtaint_map->label_info[size_label].num == 0) offset_cpy(size_label);

}
/**
 * memcpy
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook4 (unsigned id, dfsan_label dst_label, dfsan_label src_label, 
  dfsan_label size_label) {

  #ifdef DTAINT_DEBUG
  //fprintf(stderr, "__dfsan_hook4: id: %u dst_label: %u src_label: %u size_label: %u\n", 
  //  id, dst_label, src_label, size_label);
  #endif 

  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (dst_label == 0 && src_label == 0 && size_label) return;

  if (dst_label != 0 && __afl_dtaint_map->label_info[dst_label].num == 0) offset_cpy(dst_label);
  if (src_label != 0 && __afl_dtaint_map->label_info[src_label].num == 0) offset_cpy(src_label);
  if (size_label != 0 && __afl_dtaint_map->label_info[size_label].num == 0) offset_cpy(size_label);

}
/**
 * ex. malloc
 */ 
extern "C" __attribute__((visibility("default")))
void __dfsan_hook5 (unsigned id, dfsan_label size_label) {
  
  #ifdef DTAINT_DEBUG
  //fprintf(stderr, "__dfsan_hook5: id: %u size_label: %u\n", id, size_label);
  #endif 
  
  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (size_label != 0 && __afl_dtaint_map->label_info[size_label].num == 0) offset_cpy(size_label);
  
}
/**
 *  ex. free
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook6 (unsigned id, dfsan_label ptr_label) {
  
  #ifdef DTAINT_DEBUG
  //fprintf(stderr, "__dfsan_hook6: id: %u ptr_label: %u\n", id, ptr_label);
  #endif 

  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (ptr_label == 0) return;

  if (ptr_label != 0 && __afl_dtaint_map->label_info[ptr_label].num == 0) offset_cpy(ptr_label);

}

/**
 * ex. realloc
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_hook7 (unsigned id, dfsan_label ptr_label, dfsan_label size_label) {

  #ifdef DTAINT_DEBUG
  //fprintf(stderr, "__dfsan_hook7: id: %u ptr_label: %u size_label: %u\n", id, ptr_label, size_label);
  #endif 
  
  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (ptr_label == 0 && size_label == 0) return;

  if (ptr_label != 0 && __afl_dtaint_map->label_info[ptr_label].num == 0) offset_cpy(ptr_label);
  if (size_label != 0 && __afl_dtaint_map->label_info[size_label].num == 0) offset_cpy(size_label);

}

/**
 * ex. get_element_ptr inst.
 */
extern "C" __attribute__((visibility("default")))
void __dfsan_va_arg_hook1 (unsigned id, dfsan_label ptr_label, unsigned num_of_idx, ...) {

  va_list args;
  int size, logged;
  #ifdef DTAINT_DEBUG
  /*fprintf(stderr, "__dfsan_vararg_hook1: id: %u ptr_label: %u, num: %u\n", 
  id, ptr_label, num_of_idx);

  if (num_of_idx > DTAINT_MAXiMUM_IDX_NUM)
    logged = DTAINT_MAXiMUM_IDX_NUM;
  else
    logged = num_of_idx;

  va_start(args, num_of_idx);
  for(int j = 0; j < logged; j++) {
    fprintf(stderr, "idx_label %u ", va_arg(args, int));
  }fprintf(stderr, "\n");

  va_end(args);*/
  #endif

  if (unlikely(!__afl_dtaint_map) || id >= DTAINT_MAP_W) return;

  if (num_of_idx > DTAINT_MAXiMUM_IDX_NUM)
    logged = DTAINT_MAXiMUM_IDX_NUM;
  else
    logged = num_of_idx;

  if (ptr_label != 0 && __afl_dtaint_map->label_info[ptr_label].num == 0) {
    offset_cpy(ptr_label);
    printf("get eleptr label0: %d\n", ptr_label);
  }

  dfsan_label label;
  va_start(args, num_of_idx);
  for(int i = 0; i < logged; i++) {
    
    label = va_arg(args, int);

    if (label != 0 && __afl_dtaint_map->label_info[label].num == 0) {
      offset_cpy(label);
    }

  }
  va_end(args);

}

