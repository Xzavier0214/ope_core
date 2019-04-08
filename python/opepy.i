%module opepy
%{
#define SWIG_FILE_WITH_INIT
%}

extern void spherical_state_fcn();
extern void spherical_costate_fcn();
extern void spherical_control_fcn();
extern void spherical_hamilton_fcn();
extern void spherical_ext_state_fcn();
extern void spherical_boundary_fcn();
extern void spherical_fitness_fcn();