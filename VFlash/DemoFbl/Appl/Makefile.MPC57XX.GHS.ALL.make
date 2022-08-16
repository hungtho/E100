#######################################################################################################################
# File Name  : Makefile.MPC57XX.GHS.ALL.make                                                                          #
# Description: Linker/Symbol Preprocessor command file generation                                                     #
# Project    : Vector Basic Runtime System                                                                            #
# Module     : BrsHw for Platform Freescale/ST MPC57xx                                                                #
#              and Compiler GreenHills                                                                                #
#                                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# COPYRIGHT                                                                                                           #
#---------------------------------------------------------------------------------------------------------------------#
# Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved. #
#                                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# AUTHOR IDENTITY                                                                                                     #
#---------------------------------------------------------------------------------------------------------------------#
# Name                          Initials      Company                                                                 #
# ----------------------------  ------------  ------------------------------------------------------------------------#
# Benjamin Walter               visbwa        Vector Informatik GmbH                                                  #
#---------------------------------------------------------------------------------------------------------------------#
# REVISION HISTORY                                                                                                    #
#---------------------------------------------------------------------------------------------------------------------#
# Version   Date        Author  Description                                                                           #
# --------  ----------  ------  --------------------------------------------------------------------------------------#
# 01.00.00  2016-07-01  visbwa  Initial creation for separation of Default and SafeCtx UseCase                        #
# 01.01.00  2017-02-08  visbwa  Added support for OsGen7                                                              #
#######################################################################################################################

#------------------------------------------------------------------------------
# include the memory map (RAM/ROM area)
#------------------------------------------------------------------------------
include Makefile.derivative.memorymap

##########################################################################################################
# LINKER FILE GENERATION
##########################################################################################################
#Linker script generation moved to external file
ifeq ($(OS_USECASE),$(filter $(OS_USECASE),BRS OS))
  include Makefile.MPC57XX.GHS.ALL.LinkerScriptDefault.make
endif

ifeq ($(OS_USECASE),SAFECTX)
  include Makefile.MPC57XX.GHS.ALL.LinkerScriptSafeContext.make
endif

ifeq ($(OS_USECASE),OSGEN7)
  include Makefile.MPC57XX.GHS.ALL.LinkerScriptOsGen7.make
endif
