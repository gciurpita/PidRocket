## model:    3.4 angY | x  0.15 m  0.60 m/s  1.50 m/s/s   2.99 F | y   1.3 deg  0.10 r/s  0.36 r/s/s   0.18 F

awk '
BEGIN {
    A = 3
    printf "color=%s\nnext\n", "black"
    printf " %8.4f %8.4f\n",  -A, 0
    printf " %8.4f %8.4f\n",   A, 0
    N = 0
}

/model:/  {
    alpha [N] = $2
    rndY  [N] = $4
    xPos  [N] = $8
    yAng  [N] = $18
    N++
}

function plotDevi (vecX, vecY, N, col, lbl)  {
    printf "\n# %s\n", lbl
    printf "color=%s\n", col

    for (n = 0; n < N; n++)
        if (vecX [n])  {
            printf "next\n"
            printf " %8.4f %8.4f\n", 0,        vecY [n]
            printf " %8.4f %8.4f\n", vecX [n], vecY [n]
        }
}

function plot (vecX, vecY, N, col, lbl)  {
    printf "\n# %s\n", lbl
    printf "color=%s\nnext\n", col

    for (n = 0; n < N; n++)
        printf " %8.4f %8.4f\n", vecX [n], vecY [n]
}

END  {
    printf "title   PID Rocket\n"
    printf "title_x Angle: Y (yellow), (Perturbation (red)\n"

    printf "thickness = 2.5\n",
    plot(yAng, xPos, N, "yellow", "yAng")

    plotDevi(rndY, xPos, N, "red",  "rndY")

}' $*
