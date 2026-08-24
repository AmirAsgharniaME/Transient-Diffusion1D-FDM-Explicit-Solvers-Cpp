# Explicit DuFort-Frankel Scheme

The DuFort-Frankel scheme is a modified form of the Richardson method developed to improve the stability characteristics of explicit time-marching schemes for the one-dimensional diffusion equation.

The DuFort-Frankel method modifies the spatial discretization by replacing the central value at the current time level, $u_j^n$, with the average of the same spatial node at the adjacent time levels:

$$
u_j^n
\approx
\frac{u_j^{n+1}+u_j^{n-1}}{2}
$$

This modification introduces the unknown value $u_j^{n+1}$ into the spatial approximation. However, after rearrangement, the resulting equation remains explicit because $u_j^{n+1}$ can be calculated directly from previously known neighboring values.

The governing one-dimensional diffusion equation is evaluated at the grid point $(y_j,t^n)$, giving:

$$
\left(\frac{\partial u}{\partial t}\right)_j^n
=
\nu
\left(\frac{\partial^2 u}{\partial y^2}\right)_j^n
$$ {#eq:dufort-frankel-governing-discrete}

The DuFort-Frankel scheme uses:

- a central difference in time;
- a modified central difference in space;
- three consecutive time levels: $n-1$, $n$, and $n+1$;
- a direct explicit update after algebraic rearrangement.

## A. Temporal Discretization of the DuFort-Frankel Scheme

The temporal derivative is approximated using the same central difference employed in the Richardson scheme. The first-order temporal derivative at $(y_j,t^n)$ is:

$$
\left(\frac{\partial u}{\partial t}\right)_j^n
=
\frac{
u_j^{n+1}
-
u_j^{n-1}
}{
2\Delta t
}
+
\mathcal{O}\left((\Delta t)^2\right)
$$ {#eq:dufort-frankel-central-time}

Thus, the central temporal approximation is formally second-order accurate in time.

The same temporal approximation is also used by the Richardson scheme. Therefore, the principal difference between the Richardson and DuFort-Frankel methods is not the temporal discretization, but the modified treatment of the central spatial value.

## B. Modified Spatial Discretization

The conventional second-order central approximation for the second-order spatial derivative is:

$$
\left(\frac{\partial^2 u}{\partial y^2}\right)_j^n
=
\frac{
u_{j+1}^n
-
2u_j^n
+
u_{j-1}^n
}{
(\Delta y)^2
}
+
\mathcal{O}\left((\Delta y)^2\right)
$$ {#eq:dufort-frankel-conventional-central-space}

This is the same spatial approximation used by the FTCS and Richardson schemes.

However, directly using $u_j^n$ in Equation ([-@eq:dufort-frankel-conventional-central-space]) leads to the Richardson formulation. The DuFort-Frankel method replaces the central value $u_j^n$ with the average of the values at the same spatial node at time levels $n+1$ and $n-1$:

$$
u_j^n
\approx
\frac{
u_j^{n+1}
+
u_j^{n-1}
}{
2
}
$$ {#eq:dufort-frankel-central-value-average}

Substituting Equation ([-@eq:dufort-frankel-central-value-average]) into the conventional central approximation in Equation ([-@eq:dufort-frankel-conventional-central-space]) gives the modified spatial approximation:

$$
\left(\frac{\partial^2 u}{\partial y^2}\right)_j^n
\approx
\frac{
u_{j+1}^n
-
\left(u_j^{n+1}+u_j^{n-1}\right)
+
u_{j-1}^n
}{
(\Delta y)^2
}
+
\mathcal{O}\left((\Delta y)^2\right)
$$ {#eq:dufort-frankel-modified-central-space}

The key modification relative to the Richardson method is therefore:

$$
-2u_j^n
\quad\longrightarrow\quad
-\left(u_j^{n+1}+u_j^{n-1}\right)
$$

In this way, the current-time central value is replaced by values from the two adjacent time levels.

## C. Discrete Algebraic Equation

Substituting the central temporal approximation from Equation ([-@eq:dufort-frankel-central-time]) and the modified spatial approximation from Equation ([-@eq:dufort-frankel-modified-central-space]) into the governing diffusion equation in Equation ([-@eq:dufort-frankel-governing-discrete]) gives:

$$
\frac{
u_j^{n+1}
-
u_j^{n-1}
}{
2\Delta t
}
=
\nu
\left(
\frac{
u_{j+1}^n
-
u_j^{n+1}
-
u_j^{n-1}
+
u_{j-1}^n
}{
(\Delta y)^2
}
\right)
$$ {#eq:dufort-frankel-discrete-substitution}

Defining the dimensionless diffusion number as:

$$
d
=
\frac{\nu\Delta t}{(\Delta y)^2}
$$ {#eq:dufort-frankel-diffusion-number}

and multiplying Equation ([-@eq:dufort-frankel-discrete-substitution]) by $2\Delta t$, we obtain:

$$
u_j^{n+1}
-
u_j^{n-1}
=
2d
\left(
u_{j+1}^n
-
u_j^{n+1}
-
u_j^{n-1}
+
u_{j-1}^n
\right)
$$ {#eq:dufort-frankel-time-multiplication}

Collecting the terms at time levels $n+1$ and $n-1$ gives:

$$
(1+2d)u_j^{n+1}
=
(1-2d)u_j^{n-1}
+
2d
\left(
u_{j+1}^n
+
u_{j-1}^n
\right)
$$ {#eq:dufort-frankel-rearranged}

Finally, dividing Equation ([-@eq:dufort-frankel-rearranged]) by $(1+2d)$ yields the explicit DuFort-Frankel update equation:

$$
u_j^{n+1}
=
\frac{
(1-2d)u_j^{n-1}
+
2d\left(u_{j+1}^n+u_{j-1}^n\right)
}{
1+2d
}
$$ {#eq:dufort-frankel-final-update}

Equation ([-@eq:dufort-frankel-final-update]) is the final algebraic form of the DuFort-Frankel scheme.

Unlike the Richardson equation, the central value $u_j^n$ does not appear explicitly in the update equation. Instead, the current-time central value has been replaced by the average defined in Equation ([-@eq:dufort-frankel-central-value-average]).

For a grid containing $N$ nodes, Equation ([-@eq:dufort-frankel-final-update]) is applied at all interior nodes:

$$
j=1,2,\ldots,N-2
$$

The boundary values at $j=0$ and $j=N-1$ are assigned directly from the prescribed physical boundary conditions.

Because Equation ([-@eq:dufort-frankel-final-update]) directly provides $u_j^{n+1}$ from known values at time levels $n$ and $n-1$, the DuFort-Frankel method is classified as an explicit three-time-level scheme. Therefore, no tridiagonal or other algebraic system must be solved at each time step.

## D. Comparison with the FTCS and Richardson Schemes

The three explicit schemes considered so far differ in their temporal discretization, spatial treatment, and stability properties.

The FTCS scheme uses a forward difference in time and a conventional central difference in space. Its update equation is:

$$
u_j^{n+1}
=
u_j^n
+
d
\left(
u_{j+1}^n
-
2u_j^n
+
u_{j-1}^n
\right)
$$ {#eq:dufort-frankel-ftcs-comparison-ref}

The Richardson scheme uses central differences in both time and space. Its update equation is:

$$
u_j^{n+1}
=
u_j^{n-1}
+
2d
\left(
u_{j+1}^n
-
2u_j^n
+
u_{j-1}^n
\right)
$$

The DuFort-Frankel scheme retains the central temporal difference of Richardson but replaces the current-time central spatial value with the average in Equation ([-@eq:dufort-frankel-central-value-average]), resulting in Equation ([-@eq:dufort-frankel-final-update]).

The principal differences among the three explicit schemes are summarized below:

| Scheme | Temporal discretization | Spatial discretization | Time levels | Formal accuracy | Stability |
|---|---|---|---:|---|---|
| FTCS | Forward, first-order | Central, second-order | 2 | First-order in time and second-order in space | Conditionally stable, $d\leq\frac{1}{2}$ |
| Richardson | Central, second-order | Central, second-order | 3 | Second-order in time and space | Unconditionally unstable |
| DuFort-Frankel | Central, second-order | Modified central | 3 | Nominally second-order spatial treatment | Unconditionally stable for the diffusion equation |

The comparison shows that the Richardson scheme and the DuFort-Frankel scheme share the same central temporal discretization and three-time-level structure. Their main difference is the treatment of the central spatial value:

- Richardson uses $u_j^n$ directly.
- DuFort-Frankel replaces $u_j^n$ with $\frac{1}{2}(u_j^{n+1}+u_j^{n-1})$.

This apparently small modification changes the stability behavior substantially. The Richardson method is unconditionally unstable, whereas the DuFort-Frankel method is unconditionally stable for the one-dimensional diffusion equation.

Compared with FTCS, DuFort-Frankel removes the restrictive condition $d\leq\frac{1}{2}$. Consequently, larger time steps can be used without the classical FTCS instability. However, unconditional stability does not imply unlimited accuracy. Very large values of $d$ may still introduce excessive numerical damping or temporal distortion.

## E. Stability Analysis of the DuFort-Frankel Scheme

The stability of the DuFort-Frankel scheme can be examined using a von Neumann Fourier analysis. Consider a Fourier error mode of the form:

$$
\epsilon_j^n
=
G^n e^{ij\theta}
$$ {#eq:dufort-frankel-fourier-error-mode}

where $G$ is the amplification factor, $\theta$ is the phase angle, and $i=\sqrt{-1}$.

Substituting Equation ([-@eq:dufort-frankel-fourier-error-mode]) into the update equation in Equation ([-@eq:dufort-frankel-final-update]) gives:

$$
(1+2d)G^{n+1}e^{ij\theta}
=
(1-2d)G^{n-1}e^{ij\theta}
+
2dG^n
\left(
e^{i(j+1)\theta}
+
e^{i(j-1)\theta}
\right)
$$ {#eq:dufort-frankel-fourier-substitution}

Dividing Equation ([-@eq:dufort-frankel-fourier-substitution]) by $G^{n-1}e^{ij\theta}$ gives:

$$
(1+2d)G^2
=
(1-2d)
+
2dG
\left(
e^{i\theta}
+
e^{-i\theta}
\right)
$$ {#eq:dufort-frankel-amplification-relation}

Using the identity $e^{i\theta}+e^{-i\theta}=2\cos\theta$, Equation ([-@eq:dufort-frankel-amplification-relation]) becomes:

$$
(1+2d)G^2
-
4d\cos\theta\,G
-
(1-2d)
=
0
$$ {#eq:dufort-frankel-characteristic-equation}

The two amplification-factor roots are:

$$
G_{\pm}
=
\frac{
2d\cos\theta
\pm
\sqrt{
1-4d^2\sin^2\theta
}
}{
1+2d
}
$$ {#eq:dufort-frankel-amplification-roots}

When $1-4d^2\sin^2\theta\geq0$, the roots are real. When $1-4d^2\sin^2\theta<0$, the roots form a complex-conjugate pair. In the latter case, the squared magnitude of each root is:

$$
\left|G_{\pm}\right|^2
=
\frac{2d-1}{2d+1}
<
1,
\qquad
d>\frac{1}{2}
$$ {#eq:dufort-frankel-complex-root-magnitude}

For the real-root case, the roots also satisfy:

$$
\left|G_{\pm}\right|
\leq
1
$$ {#eq:dufort-frankel-stability-bound}

Therefore, all Fourier modes remain bounded for every positive diffusion number:

$$
\left|G_{\pm}\right|
\leq
1,
\qquad
d>0
$$ {#eq:dufort-frankel-unconditional-stability}

Thus, the DuFort-Frankel scheme is unconditionally stable for the one-dimensional diffusion equation. This is the principal advantage of DuFort-Frankel over both FTCS and Richardson:

- FTCS is stable only when $d\leq\frac{1}{2}$.
- Richardson is unstable for every $d>0$.
- DuFort-Frankel remains stable for every positive $d$.

Nevertheless, unconditional stability does not mean that an arbitrarily large time step produces an accurate solution. The value of $\Delta t$ should still be selected according to the desired temporal resolution and accuracy.

## F. Initialization of the Three-Time-Level Scheme

The DuFort-Frankel method uses the three time levels $n-1$, $n$, and $n+1$. Therefore, the solution must be available at two initial time levels before Equation ([-@eq:dufort-frankel-final-update]) can be applied.

The initial condition provides the solution at time level $n=0$. The solution at time level $n=1$ is then required to start the three-time-level DuFort-Frankel update.

A common initialization approach is to compute $u_j^1$ using the FTCS scheme:

$$
u_j^1
=
u_j^0
+
d
\left(
u_{j+1}^0
-
2u_j^0
+
u_{j-1}^0
\right)
$$ {#eq:dufort-frankel-initialization-ftcs}

However, this FTCS start-up step must itself satisfy the FTCS stability condition. Therefore, the corresponding diffusion number must obey:

$$
d
\leq
\frac{1}{2}
$$ {#eq:dufort-frankel-initialization-stability}

If the desired global time step is too large to satisfy Equation ([-@eq:dufort-frankel-initialization-stability]), the first time interval should be divided into smaller substeps. In that case, $u_j^1$ is obtained by applying FTCS repeatedly with a reduced sub-time-step $\Delta t_{\text{sub}}$ such that:

$$
d_{\text{sub}}
=
\frac{\nu \Delta t_{\text{sub}}}{(\Delta y)^2}
\leq
\frac{1}{2}
$$ {#eq:dufort-frankel-substep-condition}

This substepping procedure ensures that the initialization remains numerically stable. It is important because an unstable or overly diffusive FTCS start-up can contaminate the initial value $u_j^1$, and that error is then propagated into the subsequent DuFort-Frankel time levels.

In other words, although the DuFort-Frankel scheme itself is unconditionally stable for the diffusion equation, its first computed time level still acts as input data for all later steps. Therefore, a poor initialization may degrade the accuracy of the entire solution, even if the DuFort-Frankel marching formula remains stable.

For this reason, using FTCS only as a start-up method is acceptable only when its stability restriction can be respected. Otherwise, it is preferable to generate $u_j^1$ using one of the implicit methods introduced in the following sections, such as the Implicit Euler (Laasonen) scheme or the Crank-Nicolson scheme. This avoids the FTCS start-up restriction entirely and provides a more robust initialization for the DuFort-Frankel method.

After $u_j^1$ has been obtained, the DuFort-Frankel update in Equation ([-@eq:dufort-frankel-final-update]) is applied for subsequent time levels.

## G. Final Comparison of the Explicit Schemes

The final comparison of the three explicit methods is summarized in the following table:

| Property | FTCS | Richardson | DuFort-Frankel |
|---|---|---|---|
| Temporal discretization | Forward difference | Central difference | Central difference |
| Spatial discretization | Conventional central difference | Conventional central difference | Modified central difference |
| Number of time levels | Two | Three | Three |
| Explicit formulation | Yes | Yes | Yes |
| Temporal accuracy | First-order | Second-order | Central, formally second-order |
| Spatial accuracy | Second-order | Second-order | Central spatial treatment |
| Stability condition | $d\leq\frac{1}{2}$ | No stable positive $d$ | Unconditionally stable |
| Need for initialization | No additional time level | Yes | Yes |
| Practical use in this project | Suitable with time-step restriction | Not suitable | Suitable |
| Main limitation | Restricted time step | Unconditional instability | Possible numerical damping for large $d$ |

The three methods illustrate an important principle in numerical analysis: formal accuracy and stability must be considered together.

The FTCS scheme is simple and accurate in space, but its time step is restricted by:

$$
d\leq\frac{1}{2}
$$

The Richardson scheme improves the formal temporal order from first to second order, but this improvement is accompanied by unconditional instability. Therefore, Richardson is not suitable for practical computation despite its high formal accuracy.

The DuFort-Frankel scheme modifies the Richardson formulation by replacing the current-time central value with an average of the adjacent time levels. This modification preserves an explicit update structure while eliminating the unconditional instability of Richardson.

Consequently, among the three explicit schemes considered in this report:

- FTCS is appropriate when the stability restriction is acceptable.
- Richardson is included for comparison but is not used in the numerical implementation.
- DuFort-Frankel is attractive when larger time steps are desired because it is unconditionally stable for the one-dimensional diffusion equation.

For the present transient Plane Couette Flow problem, the FTCS and DuFort-Frankel schemes provide practical explicit alternatives, whereas the Richardson scheme serves primarily as a theoretical comparison demonstrating that higher formal accuracy does not necessarily guarantee numerical stability.
