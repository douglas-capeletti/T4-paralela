## PRIMEIROS TESTES

---

## 2 processos

```bash
cp03@grad05:~$ ladcomp -env mpicc test.c -o app ; ladrun -np 2 app
mpicc test.c -o app
Tempo de execucao: 142.8128 s
```

---

## 4 processos

```bash
cp03@grad05:~$ ladcomp -env mpicc test.c -o app ; ladrun -np 4 app
mpicc test.c -o app
Tempo de execucao: 71.6463 s
```

---

## 8 processos

```bash
cp03@grad05:~$ ladcomp -env mpicc test.c -o app ; ladrun -np 8 app
mpicc test.c -o app
Tempo de execucao: 30.5672 s
```

---

## 16 processos

```bash
cp03@grad05:~$ ladcomp -env mpicc test.c -o app ; ladrun -np 16 app
mpicc test.c -o app
srun: Force Terminated job 3736
srun: Job step aborted: Waiting up to 32 seconds for job step to finish.
srun: Job step aborted: Waiting up to 32 seconds for job step to finish.
slurmstepd-grad05: error: *** STEP 3736.4 ON grad05 CANCELLED AT 2022-06-25T19:13:55 DUE TO TIME LIMIT ***
srun: error: grad06: tasks 1,3,5,7,9,11,13,15: Terminated
srun: error: grad05: tasks 0,2,4,6,8,10,12,14: Terminated
cp03@grad05:~$ srun: error: grad05: task 0: Killed
```
