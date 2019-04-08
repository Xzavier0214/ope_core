import python.opepy as opepy
from numpy import deg2rad, sqrt

if __name__ == '__main__':

    RE = 6378.137e3
    MU = 3.986004418e14

    DU = RE
    TU = sqrt(DU*DU*DU / MU)

    GU = DU / (TU*TU)

    state_p = tuple([6578.165e3, 7.784e3, 0, deg2rad(10.0), 0, deg2rad(30.0)])
    state_e = tuple([6578.165e3, 7.784e3, 0, deg2rad(36.5), deg2rad(7.6), deg2rad(49.6)])
    costate_p = tuple([1, 1, 1, 1, 1, 1])
    costate_e = tuple([1, 1, 1, 1, 1, 1])
    ext_state = state_p + state_e + costate_p + costate_e
    control = tuple([0, 0])
    individual = tuple([1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
    k = tuple([1, DU, DU, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])
    tm_p = 0.1 * GU
    tm_e = 0.05 * GU
    mu = MU
    print(opepy.spherical_state_fcn(state_p, control, tm_p, mu))
    print((0, 0.979829, -7.45453e-08, 0.00102478, 0.000591654, 0))

    print(opepy.spherical_state_fcn(state_p, None, tm_p, mu))
    print((0, -0, -7.45453e-08, 0.00102478, 0.000591654, -0))

    print(opepy.spherical_costate_fcn(state_p, costate_p, control, tm_p, mu))
    print((6.58196e-11, -5.11706e-07, -7774.79,0, 0.00102478, -0.000433121))

    print(opepy.spherical_control_fcn(state_p, costate_p, 1))
    print((0.000128469, 0.000128469))

    print(opepy.spherical_control_fcn(state_p, costate_p, -1))
    print((0.000128469, -3.14146))

    print(opepy.spherical_hamilton_fcn(state_p, costate_p, control, tm_p, mu))
    print(0.981445)

    print(opepy.spherical_ext_state_fcn(ext_state, tm_p, tm_e, mu))
    print((0, -0.979829, -9.07165e-08, 0.00102478, 0.000591654, -1.61713e-08, 0, 0.489914, -6.64596e-08, 0.000773723,
           0.000901135, -0.000102322, 6.58196e-11, -5.1171e-07, -7774.79, 0, 0.00102478, -0.000433121, 5.91457e-11,
           -5.06064e-07, -7774.79, 0, 0.000677343, 2.19581e-05))

    print(opepy.spherical_boundary_fcn(ext_state, tm_p, tm_e, mu))
    print((0, -0.462512, -0.132645, 2, 2, 2, 1, 1, 1, 1, 1, 1, 0.513275))

    print(opepy.spherical_fitness_fcn(individual, k, state_p, state_e, tm_p, tm_e, DU, TU))
    print(4.83225e+06)

    lb = -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, -5, 0
    ub = 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
    print(opepy.solve_spherical_fcn(state_p, state_e, tm_p, tm_e, lb, ub, k, DU, TU, False))
