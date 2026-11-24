//Can each student reach 75% attendance? (at least 10 students, same class)//

#include <stdio.h>

/* Reads a whole number between lo and hi. */
int ask(const char *p, int lo, int hi) {
    double v;
    int r, c;
    while (1) {
        printf("%s", p);
        r = scanf("%lf", &v);
        c = (r == 1) ? getchar() : 0;
        while (c != '\n' && c != EOF) c = getchar();   /* discard rest of line */
        if (r == EOF) return lo;
        if (r == 1 && v >= lo && v <= hi && v == (int)v) return (int)v;
        printf("Invalid input. Enter a whole number from %d to %d.\n", lo, hi);
    }
}

/* Asks whether another student wants to enter details. Returns 1 for y, 0 for n. */
int again() {
    char yn;
    int r, c;
    while (1) {
        printf("\nIs there another student? Type y for next student, n to finish: ");
        r = scanf(" %c", &yn);
        c = (r == 1) ? getchar() : 0;
        while (c != '\n' && c != EOF) c = getchar();   /* discard rest of line */
        if (r == EOF) return 0;
        if (yn == 'y' || yn == 'Y') return 1;
        if (yn == 'n' || yn == 'N') return 0;
        printf("Invalid input. Please type y or n.\n");
    }
}

/* Returns 1 if two texts are the same, ignoring capital/small letters. */
int same(const char *a, const char *b) {
    int i = 0, x, y;
    while (a[i] != '\0' || b[i] != '\0') {
        x = a[i];
        y = b[i];
        if (x >= 'A' && x <= 'Z') x = x + 32;
        if (y >= 'A' && y <= 'Z') y = y + 32;
        if (x != y) return 0;
        i++;
    }
    return 1;
}

/* Prints text centred in a column of width w, followed by one space. */
void cell(const char *t, int w) {
    int len = 0, left, i;
    while (t[len] != '\0') len++;
    left = (w - len) / 2;
    for (i = 0; i < left; i++) printf(" ");
    printf("%s", t);
    for (i = 0; i < w - len - left; i++) printf(" ");
    printf(" ");
}

int main() {
    char sname[100][64], subj[10][64], q[64], buf[32];
    int held[10], rem[10];
    int att[100][10], ok[100][10], safe[100][10], pa[100][10], ps[100][10];
    int bad[100], allSafe[100];
    double pct[100][10], best[100][10];
    int cnt = 0, n, i, k, fin, s, found, nSafe = 0, nRecover = 0, nCannot = 0;

    printf("=== Can You Reach 75%% Attendance? (same class, at least 10 students) ===\n");

    /* ---- Class setup: same for every student ---- */
    printf("\n--- Class setup (same for all students) ---\n");
    n = ask("Number of subjects (1-10): ", 1, 10);
    for (i = 0; i < n; i++) {
        printf("\nSubject %d of %d name: ", i + 1, n);
        scanf(" %63[^\n]", subj[i]);
        held[i] = ask("  Classes held so far: ", 0, 1000);
        rem[i]  = ask("  Classes still left this semester: ", 0, 1000);
    }

    /* ---- Each student enters details, one by one (everything is stored) ---- */
    while (1) {
        s = cnt;
        cnt++;
        printf("\n==================== Student %d ====================\n", cnt);
        printf("Your name: ");
        scanf(" %63[^\n]", sname[s]);

        bad[s] = 0;
        allSafe[s] = 1;
        for (i = 0; i < n; i++) {
            printf("%s - %s (%d classes held)\n", sname[s], subj[i], held[i]);
            att[s][i] = ask("  How many did you attend? ", 0, held[i]);

            pct[s][i] = held[i] > 0 ? att[s][i] * 100.0 / held[i] : 0;   /* attendance % */
            safe[s][i] = (att[s][i] * 4 >= 3 * held[i]);                  /* at or above 75% now */
            fin = held[i] + rem[i];
            k = (3 * fin + 3) / 4 - att[s][i];                            /* must attend out of the left ones */
            if (k < 0) k = 0;
            ok[s][i] = (k <= rem[i]);
            pa[s][i] = ok[s][i] ? k : 0;
            ps[s][i] = ok[s][i] ? rem[i] - k : 0;
            best[s][i] = fin > 0 ? (att[s][i] + rem[i]) * 100.0 / fin : 0;

            if (!ok[s][i]) bad[s]++;
            if (!safe[s][i]) allSafe[s] = 0;
        }

        if (cnt == 100) {
            printf("\nMaximum of 100 students reached.\n");
            break;
        }
        if (cnt >= 10 && !again()) break;       /* y/n is asked only after the first 10 students */
        for (i = 0; i < 40; i++) printf("\n");  /* hide this student's entries from the next one */
    }

    /* ---- Summary of everyone ---- */
    for (s = 0; s < cnt; s++) {
        if (allSafe[s]) nSafe++;
        else if (bad[s] == 0) nRecover++;
        else nCannot++;
    }
    printf("\n=============== Summary of %d Students ===============\n", cnt);
    printf("%d are safe and %d are not safe out of %d students.\n\n", nSafe, cnt - nSafe, cnt);
    printf("%-52s: %d\n", "Safe (75% or above in every subject right now)", nSafe);
    printf("%-52s: %d\n", "Not safe", cnt - nSafe);
    printf("%-52s: %d\n", "   - can still reach 75% in all subjects", nRecover);
    printf("%-52s: %d\n", "   - cannot reach 75% in at least one subject", nCannot);

    /* ---- Look up any student's report by name ---- */
    while (1) {
        printf("\n--- Students ---\n");
        for (s = 0; s < cnt; s++) printf("  %d. %s\n", s + 1, sname[s]);
        printf("\nWhose report do you want? (type a name, or type exit to finish): ");
        if (scanf(" %63[^\n]", q) != 1) break;
        if (same(q, "exit")) break;

        found = 0;
        for (s = 0; s < cnt; s++) {
            if (!same(q, sname[s])) continue;
            found = 1;

            printf("\n--- Report for %s ---\n", sname[s]);
            cell("No.", 4);  printf("%-14s ", "Subject");  cell("Attended", 10);  cell("Held", 6);
            cell("Remaining", 11);  cell("Now", 7);  cell("Must attend", 13);  cell("Can skip", 10);
            cell("Best max", 10);  printf("Verdict\n");
            printf("-------------------------------------------------------------------------------------------------------------------\n");
            for (i = 0; i < n; i++) {
                sprintf(buf, "%d", i + 1);           cell(buf, 4);
                printf("%-14.14s ", subj[i]);
                sprintf(buf, "%d", att[s][i]);       cell(buf, 10);
                sprintf(buf, "%d", held[i]);         cell(buf, 6);
                sprintf(buf, "%d", rem[i]);          cell(buf, 11);
                sprintf(buf, "%.1f%%", pct[s][i]);   cell(buf, 7);
                if (ok[s][i]) {
                    sprintf(buf, "%d", pa[s][i]);    cell(buf, 13);
                    sprintf(buf, "%d", ps[s][i]);    cell(buf, 10);
                } else {
                    cell("-", 13);
                    cell("-", 10);
                }
                sprintf(buf, "%.2f%%", best[s][i]);  cell(buf, 10);
                if (!ok[s][i]) printf("CANNOT REACH 75%%\n");
                else if (safe[s][i]) printf("SAFE\n");
                else printf("AT RISK - can recover\n");
            }
            printf("-------------------------------------------------------------------------------------------------------------------\n");
            printf("Now means, your current %%.\n");
            printf("Remaining means, classes still left this semester.\n");
            printf("Must attend means, classes to attend out of the ones left.\n");
            printf("Can skip means, the rest.\n");
            printf("Best max means, final %% if you attend every remaining class.\n");
            printf("-------------------------------------------------------------------------------------------------------------------\n\n");

            printf("\n%s, here is what it means for you:\n", sname[s]);
            for (i = 0; i < n; i++) {
                if (!ok[s][i])
                    printf("  - %s: you cannot reach 75%% (best possible is %.2f%%).\n", subj[i], best[s][i]);
                else if (safe[s][i])
                    printf("  - %s: you are safe! You can skip up to %d of the %d remaining classes.\n", subj[i], ps[s][i], rem[i]);
                else
                    printf("  - %s: you are below 75%%, but attend at least %d of the %d remaining classes.\n", subj[i], pa[s][i], rem[i]);
            }

            if (bad[s] == 0)
                printf("\n%s, good news! You can reach 75%% in ALL subjects. Follow the 'Must attend' numbers.\n", sname[s]);
            else {
                printf("\n%s, you cannot reach 75%% in %d subject(s) even by attending every remaining class.\n", sname[s], bad[s]);
                printf("Attend all remaining classes there and talk to your teacher about it.\n");
            }
        }

        if (!found) printf("\nNo student named \"%s\" was entered. Please type a name from the list.\n", q);
    }

    printf("\nThank you! Program finished.\n");
    return 0;
}