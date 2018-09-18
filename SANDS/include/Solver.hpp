/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/*              Spectral Advection aNd Diffusion Solver             */
/*                             (SANDS)                              */
/*                                                                  */
/* Solver Header File                                               */
/*                                                                  */
/* Author               : Thibaud M. Fritz                          */
/* Time                 : 8/12/2018                                 */
/* File                 : Solver.hpp                                */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

#include <iostream>
#include <vector>
#include <complex>
#include <fftw3.h>
#include <fstream>

#include "../../Core/include/Parameters.hpp"
#include "../../Core/include/Interface.hpp"


    typedef double RealDouble;
    typedef fftw_complex FFTW_ComplexDouble;
    typedef std::complex<RealDouble> ComplexDouble;
    typedef std::vector<RealDouble> Real_1DVector;
    typedef std::vector<ComplexDouble> Complex_1DVector;
    typedef std::vector<Real_1DVector> Real_2DVector;
    typedef std::vector<Complex_1DVector> Complex_2DVector;

    const ComplexDouble _1j ( 0.0, 1.0 );          /* j^2 = -1 */
    const RealDouble PI = 3.141592653589793238460; /* \pi */

    void SANDS( Real_2DVector &V, Real_2DVector &diff, Complex_2DVector &adv, \
                const char* fileName_FFTW, const bool realInput );
    void SaveWisdom( Real_2DVector &V, const char* fileName_FFTW );

    /* A class for solving the 2D-Avection Diffusion equation */

    class Solver
    {

        public:
            
            /* Base constructor  */
            Solver( );

            /* Constructor */
            Solver( bool fill = 0, RealDouble fillValue = 0.0, unsigned flag = FFTW_ESTIMATE );

            /* Copy constructor */
            /*
             * Parameter s to be copied
             */
            Solver( const Solver &s );

            /* Assignment operator */
            /*
             * Parameter s reference to the solver to be copied
             */
            Solver& operator=( const Solver &s );

            /* Destructor */
            ~Solver( );

            void AssignFreq( );

//            RealDouble MassCheck( Real_2DVector &v );

            Real_2DVector getDiffFactor( ) const;

            Complex_2DVector getAdvFactor( ) const;

            /* Update time step */
            void UpdateTimeStep( double T );

            /* Update diffusion field */
            void UpdateDiff( double dH, double dV );

            /* Update advection field */
            void UpdateAdv( double vH, double vV );
           
            void Solve( Real_2DVector &V, const bool realInput );

            void Wisdom( Real_2DVector &V );

            unsigned int getNx() const;
            unsigned int getNy() const;
            RealDouble getXlim() const;
            RealDouble getYlim() const;
            RealDouble getDt() const;

        protected:

            unsigned int n_x, n_y;
            RealDouble xlim, ylim;
            bool doFill;
            RealDouble fillVal;
            unsigned FFTW_flag;
            double dt;

        private:

            static const char *wisdomFile;
            Real_2DVector DiffFactor;
            Complex_2DVector AdvFactor;
            Real_1DVector kx, ky, kxx, kyy;
            

    };

#endif /* SOLVER_H_INCLUDED */
