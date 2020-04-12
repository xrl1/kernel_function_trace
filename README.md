## kernel_function_trace
kernel_function_trace is a small utility that shows you all the function calling stack graph inside the kernel, for a specific process invocation.

If strace records all the syscalls entry and exit calls of a process, kernel_function_trace will record all the function calls inside the kernel, and how long they took. Unlike strace, kernel_function_trace won't show the arguments passed to the function.

It is a wrapper around the 'trace-cmd' utility, and 'trace-cmd' should be installed on the system.

## Compile
```
gcc -o kernel_function_trace kernel_function_trace.c
```

## Usage
Run as root
 ```
 # ./kernel_function_trace [COMMAND TO TRACE]
 ```
For example:
 ```
 # ./kernel_function_trace insmod my_kernel_module.ko
 ```
 trace-cmd will create a trace file called ```trace.dat``` in the same directory.
 To inspect the output, simply run 
 ```
 trace-cmd report
 ```
 A sample from the output:
 ```
 root@ubuntu:~/work# trace-cmd report | head -30
CPU 0 is empty
CPU 1 is empty
CPU 3 is empty
cpus=4
          <idle>-0     [002] 30213.960195: funcgraph_entry:                   |  switch_mm_irqs_off() {
          <idle>-0     [002] 30213.960197: funcgraph_entry:        1.199 us   |    load_new_mm_cr3();
          <idle>-0     [002] 30213.960199: funcgraph_exit:         5.185 us   |  }
          insmod-18954 [002] 30213.960201: funcgraph_entry:        0.856 us   |  finish_task_switch();
          insmod-18954 [002] 30213.960202: funcgraph_entry:                   |  _cond_resched() {
          insmod-18954 [002] 30213.960203: funcgraph_entry:        0.402 us   |    rcu_all_qs();
          insmod-18954 [002] 30213.960203: funcgraph_exit:         1.190 us   |  }
          insmod-18954 [002] 30213.960204: funcgraph_entry:        0.727 us   |  _raw_spin_lock_irq();
          insmod-18954 [002] 30213.960205: funcgraph_entry:        0.506 us   |  _raw_read_lock();
          insmod-18954 [002] 30213.960206: funcgraph_entry:                   |  do_notify_parent_cldstop() {
          insmod-18954 [002] 30213.960207: funcgraph_entry:        0.951 us   |    task_active_pid_ns();
          insmod-18954 [002] 30213.960208: funcgraph_entry:        0.740 us   |    __task_pid_nr_ns();
          insmod-18954 [002] 30213.960209: funcgraph_entry:                   |    from_kuid_munged() {
          insmod-18954 [002] 30213.960210: funcgraph_entry:        0.528 us   |      map_id_up();
          insmod-18954 [002] 30213.960211: funcgraph_exit:         1.370 us   |    }
          insmod-18954 [002] 30213.960211: funcgraph_entry:        0.420 us   |    nsec_to_clock_t();
          insmod-18954 [002] 30213.960212: funcgraph_entry:        0.408 us   |    nsec_to_clock_t();
          insmod-18954 [002] 30213.960213: funcgraph_entry:        0.826 us   |    _raw_spin_lock_irqsave();
          insmod-18954 [002] 30213.960214: funcgraph_entry:                   |    send_signal() {
          insmod-18954 [002] 30213.960215: funcgraph_entry:        0.520 us   |      siginfo_layout();
          insmod-18954 [002] 30213.960216: funcgraph_entry:        0.401 us   |      task_active_pid_ns();
          insmod-18954 [002] 30213.960216: funcgraph_entry:        0.463 us   |      __task_pid_nr_ns();
          insmod-18954 [002] 30213.960217: funcgraph_entry:                   |      __send_signal() {
          insmod-18954 [002] 30213.960218: funcgraph_entry:        0.822 us   |        prepare_signal();
          insmod-18954 [002] 30213.960219: funcgraph_exit:         1.673 us   |      }
          insmod-18954 [002] 30213.960219: funcgraph_exit:         5.018 us   |    }

 root@ubuntu:~/work# trace-cmd report | grep -A 15 load_module
          insmod-18954 [002] 30213.994129: funcgraph_entry:                   |      load_module() {
          insmod-18954 [002] 30213.994130: funcgraph_entry:        0.593 us   |        find_sec();
          insmod-18954 [002] 30213.994131: funcgraph_entry:        0.681 us   |        get_next_modinfo();
          insmod-18954 [002] 30213.994132: funcgraph_entry:        0.480 us   |        find_sec();
          insmod-18954 [002] 30213.994132: funcgraph_entry:        0.497 us   |        find_sec();
          insmod-18954 [002] 30213.994133: funcgraph_entry:        0.490 us   |        find_sec();
          insmod-18954 [002] 30213.994134: funcgraph_entry:                   |        mod_verify_sig() {
          insmod-18954 [002] 30213.994134: funcgraph_entry:        0.213 us   |          mod_check_sig();
          insmod-18954 [002] 30213.994134: funcgraph_entry:                   |          verify_pkcs7_signature() {
          insmod-18954 [002] 30213.994135: funcgraph_entry:                   |            pkcs7_parse_message() {
          insmod-18954 [002] 30213.994135: funcgraph_entry:                   |              kmem_cache_alloc_trace() {
          insmod-18954 [002] 30213.994135: funcgraph_entry:                   |                _cond_resched() {
          insmod-18954 [002] 30213.994135: funcgraph_entry:        0.202 us   |                  rcu_all_qs();
          insmod-18954 [002] 30213.994136: funcgraph_exit:         0.571 us   |                }
          insmod-18954 [002] 30213.994136: funcgraph_entry:        0.202 us   |                should_failslab();
          insmod-18954 [002] 30213.994136: funcgraph_entry:        0.294 us   |                memcg_kmem_put_cache();

 ```

Enjoy.