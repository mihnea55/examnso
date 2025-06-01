#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int i, n = 7; // Poți modifica valoarea lui n aici
    int status, pid;
    int total = 1; // Contor pentru procesul curent

    for (i = 0; i < n; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0) {
            // Suntem în copil – continuăm bucla
            continue;
        } else {
            // Suntem în părinte – așteptăm copilul
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int child_count = WEXITSTATUS(status);
                total += child_count;
            }

            // După ce un părinte creează un copil, el nu mai creează alții
            break;
        }
    }

    // Transmite totalul către părinte
    if (i == n || pid == 0) {
        // Ultimul proces (care nu a mai creat copii) – se termină cu 1 (doar el însuși)
        exit(1);
    }

    // Doar procesul inițial ajunge aici
    if (getppid() != 1) {
        printf("Numar total de procese create: %d\n", total);
    }

    return 0;
}
