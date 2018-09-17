/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                                                  */
/*     Aircraft Plume Chemistry, Emission and Microphysics Model    */
/*                             (APCEMM)                             */
/*                                                                  */
/* Emission Program File                                            */
/*                                                                  */
/* Author               : Thibaud M. Fritz                          */
/* Time                 : 7/26/2018                                 */
/* File                 : Emission.cpp                              */
/* Working directory    : /home/fritzt/APCEMM-SourceCode            */
/*                                                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include "Emission.hpp"

Emission::Emission( )
{
    /* Default Constructor */

    CO2 = 0.0;
    H2O = 0.0;
    NOx = 0.0;
    NO  = 0.0;
    NO2 = 0.0;
    HNO2= 0.0;
    SO2 = 0.0;
    CO  = 0.0;
    HC  = 0.0;
    
    /* HC splitting */
    CH4  = 0.268248 * HC;
    C2H6 = 0.013750 * HC;
    PRPE = 0.384804 * HC;
    ALK4 = 0.013497 * HC;
    CH2O = 0.184800 * HC;
    ALD2 = 0.086150 * HC;
    GLYX = 0.017129 * HC;
    MGLY = 0.009899 * HC;

} /* End of Emission::Emission */

Emission::Emission( const Engine &engine, const Fuel &fuel )
{
    /* Constructor */

    Populate_withEngine( engine );

    Populate_withFuel( fuel );
    
    /* Carbon footprint */
    double carbContent = 0.95; 
    CO2 -= ( 44.095 / 28.010 * CO + 44.095 / (82.0/5.0) * HC + 44.095 / 12.0 * carbContent * Soot);
    /* Assume that soot is 95% carbon by weight */
    /* Add organic carbon .. TBD */

    /* HC splitting */
    CH4  = 0.268248 * HC;
    C2H6 = 0.013750 * HC;
    PRPE = 0.384804 * HC;
    ALK4 = 0.013497 * HC;
    CH2O = 0.184800 * HC;
    ALD2 = 0.086150 * HC;
    GLYX = 0.017129 * HC;
    MGLY = 0.009899 * HC;

    if ( CO2 <= 0.0 ) {
        std::cout << "CO2 emissions are negative: EI(CO_2) = " << CO2 << "g/kg" << std::endl;
        CO2 = 0.0;
    }
    if ( H2O <= 0.0 ) {
        std::cout << "H2O emissions are negative: EI(H_2O) = " << H2O << "g/kg" << std::endl;
        H2O = 0.0;
    }
    if ( SO2 <= 0.0 ) {
        std::cout << "SO2 emissions are negative: EI(SO_2) = " << SO2 << "g/kg" << std::endl;
        SO2 = 0.0;
    }
    if ( NOx <= 0.0 ) {
        std::cout << "NOx emissions are negative: EI(NO_x) = " << NOx << "g/kg" << std::endl;
        NOx = 0.0;
    }
    if ( CO <= 0.0 ) {
        std::cout << "CO emissions are negative: EI(CO) = " << CO << "g/kg" << std::endl;
        CO = 0.0;
    }
    if ( HC <= 0.0 ) {
        std::cout << "HC emissions are negative: EI(HC) = " << HC << "g/kg" << std::endl;
        HC = 0.0;
    }

    if ( Soot <= 0.0 ) {
        std::cout << "Soot emissions are negative: EI(Soot) = " << Soot << "g/kg" << std::endl;
        Soot = 0.0;
    }
    if ( SootRad <= 1.0E-09 ) {
        std::cout << "Soot emissions are negative: Rad_Soot = " << SootRad << std::endl;
        SootRad = 1.0E-09;
    }

    engineName = engine.getName();

    fuelChem =  fuel.getChemFormula();

} /* End of Emission::Emission */

Emission::Emission( const Emission &e )
{

    /* Constructor */

    CO2 = e.CO2;
    H2O = e.H2O;
    NOx = e.NOx;
    NO  = e.NO;
    NO2 = e.NO2;
    HNO2= e.HNO2;
    SO2 = e.SO2;
    CO  = e.CO;
    HC  = e.HC;
    
    /* HC splitting */
    CH4  = e.CH4;
    C2H6 = e.C2H6;
    PRPE = e.PRPE;
    ALK4 = e.ALK4;
    CH2O = e.CH2O;
    ALD2 = e.ALD2;
    GLYX = e.GLYX;
    MGLY = e.MGLY;

    Soot = e.Soot;
    SootRad = e.SootRad;

    engineName = e.engineName;
    fuelChem = e.fuelChem;

} /* End of Emission::Emission */


Emission::~Emission( )
{
    /* Destructor */

} /* End of Emission::~Emission */

void Emission::Populate_withEngine( const Engine &engine )
{
    /* Gaseous species */
    /*** Engine characteristics */
    NOx  = engine.getEI_NOx();
    NO   = engine.getEI_NO();
    NO2  = engine.getEI_NO2();
    HNO2 = engine.getEI_HNO2();
    CO   = engine.getEI_CO();
    HC   = engine.getEI_HC();

    /* BC */
    Soot = engine.getEI_Soot();
    SootRad = engine.getSootRad();

} /* End of Emission::Populate_withEngine */

void Emission::Populate_withFuel( const Fuel &fuel )
{
    /*** Fuel characteristics */
    CO2 = ( 12.0107 * fuel.getAtomC() ) / ( 12.0107 * fuel.getAtomC() + 1.0079 * fuel.getAtomH() + 10.0067 * fuel.getAtomN() + 32.065 * fuel.getAtomS() ) * ( 44.0095 / ( 1 * 12.0107 ) ); /* [ g/g fuel ] */
    H2O = (  1.0079 * fuel.getAtomH() ) / ( 12.0107 * fuel.getAtomC() + 1.0079 * fuel.getAtomH() + 10.0067 * fuel.getAtomN() + 32.065 * fuel.getAtomS() ) * ( 18.0153 / ( 2 *  1.0079 ) ); /* [ g/g fuel ] */
    /* Convert to g/kg */
    CO2 *= 1000; /* [ g/kg fuel ]*/
    H2O *= 1000; /* [ g/kg fuel ]*/
    /* getFSC from fuel */
    SO2 = fuel.getFSC() / 2.0 / 1000.0;

} /* End of Emission::Populate_withFuel */

Emission& Emission::operator=( const Emission &em )
{

    if ( &em == this )
        return *this;

    CO2 = em.CO2 ;
    H2O = em.H2O ;
    NOx = em.NOx ;
    NO  = em.NO  ;
    NO2 = em.NO2 ;
    HNO2= em.HNO2;
    SO2 = em.SO2 ;
    CO  = em.CO  ;
    HC  = em.HC  ;
    CH4 = em.CH4 ;
    C2H6= em.C2H6;
    PRPE= em.PRPE;
    ALK4= em.ALK4;
    CH2O= em.CH2O;
    ALD2= em.ALD2;
    GLYX= em.GLYX;
    MGLY= em.MGLY;
    Soot= em.Soot;

    SootRad= em.SootRad;
    return *this;

} /* End of Emission::operator= */

Emission& Emission::operator+( const Emission &em )
{

    this->CO2  += em.CO2 ;
    this->H2O  += em.H2O ;
    this->NOx  += em.NOx ;
    this->NO   += em.NO  ;
    this->NO2  += em.NO2 ;
    this->HNO2 += em.HNO2;
    this->SO2  += em.SO2 ;
    this->CO   += em.CO  ;
    this->HC   += em.HC  ;
    this->CH4  += em.CH4 ;
    this->C2H6 += em.C2H6;
    this->PRPE += em.PRPE;
    this->ALK4 += em.ALK4;
    this->CH2O += em.CH2O;
    this->ALD2 += em.ALD2;
    this->GLYX += em.GLYX;
    this->MGLY += em.MGLY;
    this->Soot += em.Soot;

    if ( this->SootRad != em.SootRad )
        std::cout << " Emission:operator+: SootRad differs for both Emission instances" << std::endl;

    return *this;

} /* End of Emission::operator+ */


double Emission::GetCO2( ) const
{

    return CO2;

} /* End of Emission::GetCO2 */

double Emission::GetH2O( ) const
{

    return H2O;

} /* End of Emission::GetH2O */

double Emission::GetNOx( ) const
{

    return NOx;

} /* End of Emission::GetNOx */

double Emission::GetNO( ) const
{

    return NO;

} /* End of Emission::GetNO */

double Emission::GetNO2( ) const
{

    return NO2;

} /* End of Emission::GetNO2 */

double Emission::GetHNO2( ) const
{

    return HNO2;

} /* End of Emission::GetHNO2 */

double Emission::GetSO2( ) const
{

    return SO2;

} /* End of Emission::GetSO2 */

double Emission::GetCO( ) const
{

    return CO;

} /* End of Emission::GetCO */

double Emission::GetHC( ) const
{

    return HC;

} /* End of Emission::GetHC */

double Emission::GetCH4( ) const
{

    return CH4;

} /* End of Emission::GetCH4 */

double Emission::GetC2H6( ) const
{

    return C2H6;

} /* End of Emission::GetC2H6 */

double Emission::GetPRPE( ) const
{

    return PRPE;

} /* End of Emission::GetPRPE */

double Emission::GetALK4( ) const
{

    return ALK4;

} /* End of Emission::GetALK4 */

double Emission::GetCH2O( ) const
{

    return CH2O;

} /* End of Emission::GetCH2O */

double Emission::GetALD2( ) const
{

    return ALD2;

} /* End of Emission::GetALD2 */

double Emission::GetGLYX( ) const
{

    return GLYX;

} /* End of Emission::GetGLYX */

double Emission::GetMGLY( ) const
{

    return MGLY;

} /* End of Emission::GetMGLY */

double Emission::GetSoot( ) const
{

    return Soot;

} /* End of Emission::GetSoot */

double Emission::GetSootRad( ) const
{

    return SootRad;

} /* End of Emission::GetSootRad */

std::string Emission::GetEngineName( ) const
{

    return engineName;

} /* End of Emission::GetEngineName */

std::string Emission::GetFuelChem( ) const
{

    return fuelChem;

} /* End of Emission::GetFuelChem */


void Emission::Debug( ) const
{
    std::cout << std::endl;
    std::cout << "**** Input Debugger ****" << std::endl;
    std::cout << "Emission indices: " << std::endl;
    std::cout << std::endl;
    std::cout << std::setw(10);
    std::cout << "Species";
    std::cout << std::setw(13);
    std::cout << "Value";
    std::cout << std::setw(14);
    std::cout << "Units " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> CO2 : ";
    std::cout << std::setw(12);
    std::cout << CO2 << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> H2O : ";
    std::cout << std::setw(12);
    std::cout << H2O << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> NOx : ";
    std::cout << std::setw(12);
    std::cout << NOx << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> NO  : ";
    std::cout << std::setw(10);
    std::cout << NO << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> NO2 : ";
    std::cout << std::setw(10);
    std::cout << NO2 << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> HNO2: ";
    std::cout << std::setw(10);
    std::cout << HNO2 << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> SO2 : ";
    std::cout << std::setw(12);
    std::cout << SO2 << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> CO  : ";
    std::cout << std::setw(12);
    std::cout << CO << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> HC  : ";
    std::cout << std::setw(12);
    std::cout << HC << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> CH4 : ";
    std::cout << std::setw(10);
    std::cout << CH4 << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> C2H6: ";
    std::cout << std::setw(10);
    std::cout << C2H6 << "  [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> PRPE: ";
    std::cout << std::setw(10);
    std::cout << PRPE << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> ALK4: ";
    std::cout << std::setw(10);
    std::cout << ALK4 << "  [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> GLYX: ";
    std::cout << std::setw(10);
    std::cout << GLYX << "  [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(14);
    std::cout << " ---> MGLY: ";
    std::cout << std::setw(10);
    std::cout << MGLY << "  [ g/kg fuel ] " << std::endl;
    std::cout << std::setw(12);
    std::cout << " -> Soot: ";
    std::cout << std::setw(12);
    std::cout << Soot << "   [ g/kg fuel ] " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

} /* End of Emission::Debug */

/* End of Emission.cpp */
