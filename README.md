
# README: System Call to Create Exactly `n` Children in xv6

## Note: 
This repository may have some mistakes or poor implementation which may not align with your requirements. Feels free to fork/clone and raise a pr if found valuable.

## Overview
This document provides details about the implementation and usage of a custom system call in the xv6 operating system. The new system call allows a process to create exactly `n` child processes.

## Purpose
The default `fork()` system call in xv6 creates a single child process. In scenarios where a process needs to spawn multiple children simultaneously, this custom system call provides an efficient and convenient mechanism to achieve that goal.

## System Call Name
`create_n_children`

## Function Signature
```c
int create_n_children(int n);
```

## Parameters
- `n` (int): The number of child processes to create.

## Return Value
- On success: Returns `n` (the number of children created).
- On failure: Returns `-1` and sets an appropriate error code.

## Error Codes
- **EINVAL**: Invalid value for `n`. For example, if `n <= 0`.
- **ENOMEM**: Not enough memory to create the requested number of children.
- **EAGAIN**: System limit on the number of processes has been reached.

## Implementation Details
### Kernel Modifications
1. **System Call Definition:** 
   - Added the function `int sys_create_n_children(void)` in the kernel to handle the new system call.

2. **Process Creation Loop:**
   - Inside the `sys_create_n_children` function, a loop iterates `n` times, invoking `fork()` during each iteration.
   - On each iteration, the return value of `fork()` is checked to ensure successful child creation. If an error occurs, the process creation halts, and the system call returns `-1`.

3. **Validation:**
   - The input parameter `n` is validated to ensure it is greater than zero.

4. **Process Limits:**
   - The function respects system-imposed limits on the number of processes to prevent resource exhaustion.

### User Space Interface
A wrapper function is added in `user.h` for convenience:
```c
int create_n_children(int n);
```
This function invokes the `create_n_children` system call and can be used by user programs.

### System Call Table Update
The system call number for `create_n_children` is added to `syscall.h` and mapped in the `syscall.c` table.

## Example Usage
Here is an example program demonstrating the use of `create_n_children`:

```c
#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
    int n = 3; // Number of children to create
    int result = create_n_children(n);

    if (result == -1) {
        printf("Failed to create %d children\n", n);
    } else {
        printf("Successfully created %d children\n", result);
    }

    // Child processes will also execute this code
    printf("Process ID: %d\n", getpid());

    exit();
}
```

## Testing
### Test Scenarios
1. **Valid Input:**
   - Input `n > 0`. Verify that the correct number of children is created.

2. **Invalid Input:**
   - Input `n <= 0`. Verify that the system call returns `-1` with error code `EINVAL`.

3. **Resource Limitations:**
   - Exceed system-imposed limits (e.g., process count or memory). Verify proper handling of `ENOMEM` or `EAGAIN` errors.

### Expected Output
For `n = 3`, the output should look like:
```
Successfully created 3 children
Process ID: 5
Process ID: 6
Process ID: 7
Process ID: 4
```
(Note: Process IDs will vary.)

## Limitations
- If one or more `fork()` calls fail during execution, no cleanup is performed for already created children.
- The parent and children share the same code and data space until explicitly separated by the user program.

## Future Enhancements
- Add functionality to optionally execute different code in child processes.
- Implement cleanup for partial failures to ensure system resources are not exhausted.
- Extend support for process priorities or custom attributes during child creation.

## Conclusion
The `create_n_children` system call provides a powerful and user-friendly mechanism to spawn multiple child processes in xv6. Its efficient implementation ensures reliable operation within the constraints of the operating system.

