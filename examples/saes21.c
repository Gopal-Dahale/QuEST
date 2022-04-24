// cmake .. -DUSER_SOURCE="../examples/saes21.c" && make && ./demo

#include <QuEST.h>
#include <stdio.h>
#include <stdlib.h>

void init_key(char *key, Qureg *reg) {
  // Initialize key
  for (int i = 0; i < 16; i++) {
    if (key[i] == '1') {
      pauliX(*reg, i);
    }
  }
}

void init_msg(char *msg, Qureg *reg) {
  // Initialize message
  for (int i = 0; i < 16; i++) {
    if (msg[i] == '1') {
      pauliX(*reg, i + 16);
    }
  }
}

int main() {
  QuESTEnv env = createQuESTEnv();
  int workspace_qubits = 32;
  Qureg reg = createQureg(workspace_qubits, env);

  char msg[16] = "0110111101101011";
  char key[16] = "1010011100111011";
  char cipher[16] = "0000011100111000";

  int res = 0;
  for (int i = 0; i < 16; i++) {
    res += ((cipher[i] - 48) * (1 << (15 - i)));
  }

  initZeroState(reg);

  init_key(key, &reg);
  init_msg(msg, &reg);
  // encrypt(&reg);

  hadamard(reg, 0);
  controlledNot(reg, 0, 1);
  pauliX(reg, 2);

  int result[32];
  for (int i = 0; i < 32; i++) {
    result[i] = measure(reg, i);
  }
  // Display result
  for (int i = 0; i < 16; i++) {
    printf("%d", result[i]);
  }

  // printf("Qubit 0 was measured in state %d\n", outcome);

  return 0;
}