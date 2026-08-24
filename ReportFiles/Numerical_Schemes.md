# Numerical Schemes

In this section, the transition from the continuous partial differential equation to discrete algebraic forms suitable for C++ implementation is presented.

To solve the one-dimensional transient diffusion equation, previously introduced in Theoretical Background as Equation ([-@eq:diffusion-final]):

$$
\frac{\partial u}{\partial t}
=
\nu \frac{\partial^2 u}{\partial y^2}
$$ {#eq:diffusion-final}

the continuous temporal and spatial derivatives must be approximated using finite difference expressions. Explicit numerical schemes are therefore introduced to obtain discrete formulations of the governing equation. The FTCS scheme serves as the basic explicit method, while additional explicit schemes are included to assess numerical behavior, stability, and implementation structure.

## Explicit Numerical Schemes

1. **FTCS Scheme**
2. **Richardson Scheme**
3. **DuFort-Frankel Scheme**
