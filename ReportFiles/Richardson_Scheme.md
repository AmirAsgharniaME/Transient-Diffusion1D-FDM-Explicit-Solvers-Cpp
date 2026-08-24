# Explicit Richardson Scheme

As a second explicit approach, the Richardson scheme can be applied to the one-dimensional transient diffusion equation. Unlike the FTCS scheme, which uses a forward difference in time, the Richardson scheme employs a central difference in time and a central difference in space.

The central temporal discretization provides second-order accuracy in time. However, despite its second-order accuracy in both time and space, the Richardson scheme is unconditionally unstable for the one-dimensional diffusion equation. Therefore, it has no practical value for the present transient Plane Couette Flow problem.

The governing diffusion equation is evaluated at the grid point $(y_j,t^n)$, giving:

$$
\left(\frac{\partial u}{\partial t}\right)_j^n
=
\nu
\left(\frac{\partial^2 u}{\partial y^2}\right)_j^n
$$ {#eq:richardson-governing-discrete}

The Richardson scheme uses:

- a second-order central difference in time;
- a second-order central difference in space;
- three consecutive time levels: $n-1$, $n$, and $n+1$.

## A. Discretization of the First-Order Temporal Derivative

To approximate the first-order temporal derivative $\left(\frac{\partial u}{\partial t}\right)_j^n$, Taylor series expansions of $u_j^{n+1}$ and $u_j^{n-1}$ are developed about the point $(y_j,t^n)$.

### Forward Temporal Taylor Expansion

The Taylor series expansion of $u(y_j,t^{n+1})$ about $(y_j,t^n)$ is:

$$
u_j^{n+1}
=
u_j^n
+
\left(\frac{\partial u}{\partial t}\right)_j^n
\Delta t
+
\frac{1}{2!}
\left(\frac{\partial^2 u}{\partial t^2}\right)_j^n
(\Delta t)^2
+
\frac{1}{3!}
\left(\frac{\partial^3 u}{\partial t^3}\right)_j^n
(\Delta t)^3
+
\frac{1}{4!}
\left(\frac{\partial^4 u}{\partial t^4}\right)_j^n
(\Delta t)^4
+
\cdots
$$ {#eq:richardson-forward-temporal-taylor}

### Backward Temporal Taylor Expansion

Similarly, the Taylor series expansion of $u(y_j,t^{n-1})$ about $(y_j,t^n)$ is:

$$
u_j^{n-1}
=
u_j^n
-
\left(\frac{\partial u}{\partial t}\right)_j^n
\Delta t
+
\frac{1}{2!}
\left(\frac{\partial^2 u}{\partial t^2}\right)_j^n
(\Delta t)^2
-
\frac{1}{3!}
\left(\frac{\partial^3 u}{\partial t^3}\right)_j^n
(\Delta t)^3
+
\frac{1}{4!}
\left(\frac{\partial^4 u}{\partial t^4}\right)_j^n
(\Delta t)^4
-
\cdots
$$ {#eq:richardson-backward-temporal-taylor}

Subtracting Equation ([-@eq:richardson-backward-temporal-taylor]) from Equation ([-@eq:richardson-forward-temporal-taylor]) eliminates the even-order temporal derivative terms:

$$
u_j^{n+1}
-
u_j^{n-1}
=
2
\left(\frac{\partial u}{\partial t}\right)_j^n
\Delta t
+
\frac{1}{3}
\left(\frac{\partial^3 u}{\partial t^3}\right)_j^n
(\Delta t)^3
+
\mathcal{O}\left((\Delta t)^5\right)
$$ {#eq:richardson-temporal-taylor-difference}

Rearranging Equation ([-@eq:richardson-temporal-taylor-difference]) to isolate the first-order temporal derivative gives:

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
$$ {#eq:richardson-central-time}

The central difference approximation is therefore second-order accurate in time. The temporal truncation error is $\mathcal{O}\left((\Delta t)^2\right)$.

## B. Discretization of the Second-Order Spatial Derivative

For the second-order spatial derivative, the same central difference approximation used in the FTCS scheme is applied. The Taylor expansions about $(y_j,t^n)$ lead to:

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
$$ {#eq:richardson-central-space}

The spatial approximation is second-order accurate because its truncation error is $\mathcal{O}\left((\Delta y)^2\right)$.

## C. Discrete Algebraic Equation

Substituting the central temporal approximation from Equation ([-@eq:richardson-central-time]) and the central spatial approximation from Equation ([-@eq:richardson-central-space]) into the governing equation in Equation ([-@eq:richardson-governing-discrete]) gives:

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
2u_j^n
+
u_{j-1}^n
}{
(\Delta y)^2
}
\right)
$$ {#eq:richardson-discrete-substitution}

Multiplying both sides of Equation ([-@eq:richardson-discrete-substitution]) by $2\Delta t$ yields:

$$
u_j^{n+1}
-
u_j^{n-1}
=
\frac{
2\nu\Delta t
}{
(\Delta y)^2
}
\left(
u_{j+1}^n
-
2u_j^n
+
u_{j-1}^n
\right)
$$ {#eq:richardson-time-multiplication}

Rearranging Equation ([-@eq:richardson-time-multiplication]) to isolate the unknown value $u_j^{n+1}$ gives:

$$
u_j^{n+1}
=
u_j^{n-1}
+
\frac{
2\nu\Delta t
}{
(\Delta y)^2
}
\left(
u_{j+1}^n
-
2u_j^n
+
u_{j-1}^n
\right)
$$ {#eq:richardson-rearranged}

The dimensionless diffusion number is defined as:

$$
d
=
\frac{\nu\Delta t}{(\Delta y)^2}
$$ {#eq:richardson-diffusion-number}

Using the diffusion number defined in Equation ([-@eq:richardson-diffusion-number]), the Richardson scheme becomes:

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
$$ {#eq:richardson-final-update}

Equation ([-@eq:richardson-final-update]) is the final explicit Richardson update equation. It calculates the unknown value at time level $n+1$ using the known solution values at time levels $n$ and $n-1$.

For a grid containing $N$ nodes, Equation ([-@eq:richardson-final-update]) is applied at all interior nodes:

$$
j=1,2,\ldots,N-2
$$

The boundary values at $j=0$ and $j=N-1$ are assigned directly from the prescribed physical boundary conditions.

Because Equation ([-@eq:richardson-final-update]) uses two previous time levels, the Richardson method is classified as an explicit three-time-level scheme. No algebraic system needs to be solved at each time step.

## D. Accuracy of the Richardson Scheme

According to Equation ([-@eq:richardson-central-time]), the temporal discretization is second-order accurate:

$$
\text{Temporal truncation error}
=
\mathcal{O}\left((\Delta t)^2\right)
$$

According to Equation ([-@eq:richardson-central-space]), the spatial discretization is also second-order accurate:

$$
\text{Spatial truncation error}
=
\mathcal{O}\left((\Delta y)^2\right)
$$

Therefore, the Richardson scheme is second-order accurate in both time and space. Its combined local truncation error can be expressed as:

$$
\mathcal{T}_{\mathrm{Richardson}}
=
\mathcal{O}\left((\Delta t)^2\right)
+
\mathcal{O}\left((\Delta y)^2\right)
$$ {#eq:richardson-local-truncation-error}

Although this formal accuracy is higher than the first-order temporal accuracy of the FTCS scheme, accuracy alone does not guarantee numerical stability.

## E. Stability Analysis of the Explicit Richardson Scheme

Despite its second-order accuracy in both time and space, the Richardson scheme is unconditionally unstable for the one-dimensional diffusion equation.

This behavior can be demonstrated using a von Neumann Fourier stability analysis. Consider a Fourier error mode of the form:

$$
\epsilon_j^n
=
G^n e^{ij\theta}
$$ {#eq:richardson-fourier-error-mode}

where $G$ is the amplification factor, $\theta$ is the phase angle, and $i=\sqrt{-1}$.

Substituting the Fourier mode from Equation ([-@eq:richardson-fourier-error-mode]) into the Richardson update equation in Equation ([-@eq:richardson-final-update]) gives:

$$
G^{n+1}e^{ij\theta}
=
G^{n-1}e^{ij\theta}
+
2dG^n
\left(
e^{i(j+1)\theta}
-
2e^{ij\theta}
+
e^{i(j-1)\theta}
\right)
$$ {#eq:richardson-fourier-substitution}

Dividing Equation ([-@eq:richardson-fourier-substitution]) by $G^{n-1}e^{ij\theta}$ gives:

$$
G^2
=
1
+
2dG
\left(
e^{i\theta}
-
2
+
e^{-i\theta}
\right)
$$ {#eq:richardson-amplification-relation}

Using the identities $e^{i\theta}+e^{-i\theta}=2\cos\theta$ and $\cos\theta-1=-2\sin^2\left(\frac{\theta}{2}\right)$, Equation ([-@eq:richardson-amplification-relation]) becomes:

$$
G^2
+
8d
\sin^2\left(\frac{\theta}{2}\right)G
-
1
=
0
$$ {#eq:richardson-characteristic-equation}

The two roots of the characteristic equation in Equation ([-@eq:richardson-characteristic-equation]) are:

$$
G_{\pm}
=
-4d\sin^2\left(\frac{\theta}{2}\right)
\pm
\sqrt{
1
+
16d^2\sin^4\left(\frac{\theta}{2}\right)
}
$$ {#eq:richardson-amplification-roots}

For every $d>0$ and every nonzero wave number, one of these roots has a magnitude greater than unity. In particular, the negative root satisfies:

$$
\left|G_{-}\right|
=
4d\sin^2\left(\frac{\theta}{2}\right)
+
\sqrt{
1
+
16d^2\sin^4\left(\frac{\theta}{2}\right)
}
>
1
$$ {#eq:richardson-unstable-root}

Therefore, at least one numerical error mode grows with successive time levels for any positive diffusion number $d$. The Richardson scheme is consequently unconditionally unstable:

$$
\left|G_{-}\right|>1
\qquad
\text{for } d>0
\text{ and }
\sin\left(\frac{\theta}{2}\right)\neq 0
$$ {#eq:richardson-unconditional-instability}

This result means that reducing the time step cannot eliminate the instability. Even when $d$ is very small, one of the two amplification-factor roots remains greater than unity in magnitude for at least one nonzero Fourier mode.

Consequently, the Richardson scheme produces growing numerical disturbances and eventually leads to non-physical solutions. It is therefore unsuitable for practical transient diffusion simulations, including the present Plane Couette Flow problem.

## F. Summary of the Richardson Scheme

The main properties of the explicit Richardson scheme are summarized as follows:

- It uses central differencing in time.
- It uses central differencing in space.
- It is second-order accurate in time.
- It is second-order accurate in space.
- It is an explicit three-time-level method.
- It is unconditionally unstable for the one-dimensional diffusion equation.
- It is not suitable for practical transient diffusion calculations.

Therefore, the Richardson scheme is included in this report as an important numerical example. It demonstrates that a scheme may possess a high formal order of accuracy while still being unsuitable because of its stability characteristics.
