!EOC
!------------------------------------------------------------------------------
!     NASA/GSFC, Global Modeling and Assimilation Office, Code 910.1 and      !
!          Harvard University Atmospheric Chemistry Modeling Group            !
!------------------------------------------------------------------------------
!BOP
!
! !INCLUDE: Includes_After_Run.H
!
! !DESCRIPTION: This include file contains the array assignments that need
!  to be made BEFORE the call to the Run method of the 
!  GEOSCHEMchem\_GridCompMod.F90 code.  These array assignments take data out 
!  of the import and internal states and saves them into derived-type objects
!  that are used to pass information between GEOS-Chem and the ESMF interface.
!\\
!\\
!  These assignments were placed into this separate include file to avoid 
!  bogging down the GEOSCHEMchem\_GridCompMod.F90 module.
!\\
!\\
! !REVISION HISTORY: 
!  10 Oct 2012 - M. Long     - Initial version, for grid-independent model
!  10 Oct 2012 - R. Yantosca - Added ProTeX headers, updated comments
!  10 Oct 2012 - R. Yantosca - Converted to F90 free-format
!  10 Oct 2012 - R. Yantosca - Added Bromine species for v9-01-03
!  16 Oct 2012 - R. Yantosca - Changed GC_MET to State_Met
!  16 Oct 2012 - R. Yantosca - Changed GC_STATE to State_Chm
!  16 Oct 2012 - R. Yantosca - Changed GC_STATE%CSPEC to State_Chm%Species
!  16 Oct 2012 - R. Yantosca - Renamed to Includes_After_Run.H (freeform)
!  07 Mar 2013 - R. Yantosca - Now add error checks to prevent OOB errors
!  27 Oct 2014 - C. Keller   - Removed species copying into internal state.
!                              This is only required upon finalization.
!EOP
!------------------------------------------------------------------------------
!BOC

  !=========================================================================
  ! Advected tracers and chemical species
  ! (Coge generated with Perl script gcIncAft)
  !=========================================================================

  !=========================================================================
  ! Pass advected tracers from GEOS-Chem tracers array to internal state
  !=========================================================================

  ! Flip tracers & species in the vertical
  State_Chm%Species = State_Chm%Species( :, :, LM:1:-1, : )

  DO I = 1, SIZE(Int2Chm,1)
    IF ( Int2Chm(I)%TrcID <= 0 ) CYCLE
    Int2Chm(I)%Internal = State_Chm%Species(:,:,:,Int2Chm(I)%TrcID)
  ENDDO
