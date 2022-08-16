/****************************************************************************
*
* Copyright © 2018-2019 STMicroelectronics - All Rights Reserved
*
* License terms: STMicroelectronics Proprietary in accordance with licensing
* terms SLA0089 at www.st.com.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
* EVALUATION ONLY – NOT FOR USE IN PRODUCTION
*****************************************************************************/

#ifndef _SPC570S_H_
#define _SPC570S_H_

/**
 * @file    xpc570s.h
 * @brief   register set of SPC570Sxx microcontroller.
 */

#include <typedefs.h>

/**************************************************************************/
/*                 Module: CMU            */
/**************************************************************************/
struct CMU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:8;
            vuint32_t SFM:1;
            vuint32_t unused_1:13;
            vuint32_t CKSEL1:2;
            vuint32_t unused_0:5;
            vuint32_t RCDIV:2;
            vuint32_t CME:1;
        } B;
    } CSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t FD:20;
        } B;
    } FDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t HFREF:12;
        } B;
    } HFREFR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t LFREF:12;
        } B;
    } LFREFR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t FLCI:1;
            vuint32_t FHHI:1;
            vuint32_t FLLI:1;
            vuint32_t OLRI:1;
        } B;
    } ISR;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t MD:20;
        } B;
    } MDR;

};

/**************************************************************************/
/*                 Module: CRC            */
/**************************************************************************/
struct CRC_tag {
    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:26;
                vuint32_t SWAP_BYTEWISE:1;
                vuint32_t SWAP_BITWISE:1;
                vuint32_t POLYG:2;
                vuint32_t SWAP:1;
                vuint32_t INV:1;
            } B;
        } CFG;

        union {
            vuint32_t R;
            vuint16_t H[2];  /* Data buffer in Half-words (16 bits) */                           
            vuint8_t BYTE[4];  /* Data buffer in Bytes (8 bits) */
            struct {
                vuint32_t INP:32;
            } B;
        } INP;

        union {
            vuint32_t R;
            struct {
                vuint32_t CSTAT:32;
            } B;
        } CSTAT;

        union {
            vuint32_t R;
            struct {
                vuint32_t OUTP:32;
            } B;
        } OUTP;

    } CONTEXT[1];

};

/**************************************************************************/
/*                 Module: CTU            */
/**************************************************************************/
struct CTU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t I15_FE:1;
            vuint32_t I15_RE:1;
            vuint32_t unused_0:6;
            vuint32_t I11_FE:1;
            vuint32_t I11_RE:1;
            vuint32_t I10_FE:1;
            vuint32_t I10_RE:1;
            vuint32_t I9_FE:1;
            vuint32_t I9_RE:1;
            vuint32_t I8_FE:1;
            vuint32_t I8_RE:1;
            vuint32_t I7_FE:1;
            vuint32_t I7_RE:1;
            vuint32_t I6_FE:1;
            vuint32_t I6_RE:1;
            vuint32_t I5_FE:1;
            vuint32_t I5_RE:1;
            vuint32_t I4_FE:1;
            vuint32_t I4_RE:1;
            vuint32_t I3_FE:1;
            vuint32_t I3_RE:1;
            vuint32_t I2_FE:1;
            vuint32_t I2_RE:1;
            vuint32_t I1_FE:1;
            vuint32_t I1_RE:1;
            vuint32_t I0_FE:1;
            vuint32_t I0_RE:1;
        } B;
    } TGSISR;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:7;
            vuint16_t ET_TM:1;
            vuint16_t PRES:2;
            vuint16_t MRS_SM:5;
            vuint16_t TGS_M:1;
        } B;
    } TGSCR;

    union {
        vuint16_t R;
        struct {
            vuint16_t TNCRV:16;
        } B;
    } TCR[8];

    union {
        vuint16_t R;
        struct {
            vuint16_t TGSCCV:16;
        } B;
    } TGSCCR;

    union {
        vuint16_t R;
        struct {
            vuint16_t TGSCRV:16;
        } B;
    } TGSCRR;

    vuint8_t ADR_reserved0[2];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:3;
            vuint32_t T3_INDEX:5;
            vuint32_t unused_2:3;
            vuint32_t T2_INDEX:5;
            vuint32_t unused_1:3;
            vuint32_t T1_INDEX:5;
            vuint32_t unused_0:3;
            vuint32_t T0_INDEX:5;
        } B;
    } CLCR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:3;
            vuint32_t T7_INDEX:5;
            vuint32_t unused_2:3;
            vuint32_t T6_INDEX:5;
            vuint32_t unused_1:3;
            vuint32_t T5_INDEX:5;
            vuint32_t unused_0:3;
            vuint32_t T4_INDEX:5;
        } B;
    } CLCR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:3;
            vuint32_t T3_E:1;
            vuint32_t T3_ETE:1;
            vuint32_t T3_T1E:1;
            vuint32_t T3_T0E:1;
            vuint32_t T3_ADCE:1;
            vuint32_t unused_2:3;
            vuint32_t T2_E:1;
            vuint32_t T2_ETE:1;
            vuint32_t T2_T1E:1;
            vuint32_t T2_T0E:1;
            vuint32_t T2_ADCE:1;
            vuint32_t unused_1:3;
            vuint32_t T1_E:1;
            vuint32_t T1_ETE:1;
            vuint32_t T1_T1E:1;
            vuint32_t T1_T0E:1;
            vuint32_t T1_ADCE:1;
            vuint32_t unused_0:3;
            vuint32_t T0_E:1;
            vuint32_t T0_ETE:1;
            vuint32_t T0_T1E:1;
            vuint32_t T0_T0E:1;
            vuint32_t T0_ADCE:1;
        } B;
    } THCR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:3;
            vuint32_t T7_E:1;
            vuint32_t T7_ETE:1;
            vuint32_t T7_T1E:1;
            vuint32_t T7_T0E:1;
            vuint32_t T7_ADCE:1;
            vuint32_t unused_2:3;
            vuint32_t T6_E:1;
            vuint32_t T6_ETE:1;
            vuint32_t T6_T1E:1;
            vuint32_t T6_T0E:1;
            vuint32_t T6_ADCE:1;
            vuint32_t unused_1:3;
            vuint32_t T5_E:1;
            vuint32_t T5_ETE:1;
            vuint32_t T5_T1E:1;
            vuint32_t T5_T0E:1;
            vuint32_t T5_ADCE:1;
            vuint32_t unused_0:3;
            vuint32_t T4_E:1;
            vuint32_t T4_ETE:1;
            vuint32_t T4_T1E:1;
            vuint32_t T4_T0E:1;
            vuint32_t T4_ADCE:1;
        } B;
    } THCR2;

    union {
        vuint16_t R;
        union {
            vuint16_t R;
            struct {
                vuint16_t CIR:1;
                vuint16_t LC:1;
                vuint16_t CMS:1;
                vuint16_t unused_2:1;
                vuint16_t FIFO:2;
                vuint16_t unused_1:4;
                vuint16_t SU:1;
                vuint16_t unused_0:1;
                vuint16_t CH:4;
            } B;
        } B_CMS0;

        union {
            vuint16_t R;
            struct {
                vuint16_t CIR:1;
                vuint16_t LC:1;
                vuint16_t CMS:1;
                vuint16_t unused_2:1;
                vuint16_t FIFO:2;
                vuint16_t unused_1:1;
                vuint16_t CH_B:4;
                vuint16_t unused_0:1;
                vuint16_t CH_A:4;
            } B;
        } B_CMS1;
    } CLR[24];
    
    vuint8_t ADR_reserved2[16];

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:12;
            vuint16_t DE3:1;
            vuint16_t DE2:1;
            vuint16_t DE1:1;
            vuint16_t DE0:1;
        } B;
    } FDCR;

    vuint8_t ADR_reserved3[2];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t OR_EN3:1;
            vuint32_t OF_EN3:1;
            vuint32_t EMPTY_EN3:1;
            vuint32_t FULL_EN3:1;
            vuint32_t OR_EN2:1;
            vuint32_t OF_EN2:1;
            vuint32_t EMPTY_EN2:1;
            vuint32_t FULL_EN2:1;
            vuint32_t OR_EN1:1;
            vuint32_t OF_EN1:1;
            vuint32_t EMPTY_EN1:1;
            vuint32_t FULL_EN1:1;
            vuint32_t OR_EN0:1;
            vuint32_t OF_EN0:1;
            vuint32_t EMPTY_EN0:1;
            vuint32_t FULL_EN0:1;
        } B;
    } FCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t TH3:8;
            vuint32_t TH2:8;
            vuint32_t TH1:8;
            vuint32_t TH0:8;
        } B;
    } FTH;

    vuint8_t ADR_reserved4[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t OR3:1;
            vuint32_t OF3:1;
            vuint32_t EMP3:1;
            vuint32_t FULL3:1;
            vuint32_t OR2:1;
            vuint32_t OF2:1;
            vuint32_t EMP2:1;
            vuint32_t FULL2:1;
            vuint32_t OR1:1;
            vuint32_t OF1:1;
            vuint32_t EMP1:1;
            vuint32_t FULL1:1;
            vuint32_t OR0:1;
            vuint32_t OF0:1;
            vuint32_t EMP0:1;
            vuint32_t FULL0:1;
        } B;
    } FST;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:11;
            vuint32_t N_CH:5;
            vuint32_t unused_0:4;
            vuint32_t DATA:12;
        } B;
    } FR[4];

    vuint8_t ADR_reserved5[16];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t N_CH:5;
            vuint32_t unused_1:1;
            vuint32_t DATA:12;
            vuint32_t unused_0:3;
        } B;
    } FL[4];

    vuint8_t ADR_reserved6[16];

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:7;
            vuint16_t ET_OE:1;
            vuint16_t T1_OE:1;
            vuint16_t T0_OE:1;
            vuint16_t ADC_OE:1;
            vuint16_t TGS_OSM:1;
            vuint16_t MRS_O:1;
            vuint16_t ICE:1;
            vuint16_t SM_TO:1;
            vuint16_t MRS_RE:1;
        } B;
    } CTUEFR;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:6;
            vuint16_t ADC_I:1;
            vuint16_t T7_I:1;
            vuint16_t T6_I:1;
            vuint16_t T5_I:1;
            vuint16_t T4_I:1;
            vuint16_t T3_I:1;
            vuint16_t T2_I:1;
            vuint16_t T1_I:1;
            vuint16_t T0_I:1;
            vuint16_t MRS_I:1;
        } B;
    } CTUIFR;

    union {
        vuint16_t R;
        struct {
            vuint16_t T7_IE:1;
            vuint16_t T6_IE:1;
            vuint16_t T5_IE:1;
            vuint16_t T4_IE:1;
            vuint16_t T3_IE:1;
            vuint16_t T2_IE:1;
            vuint16_t T1_IE:1;
            vuint16_t T0_IE:1;
            vuint16_t unused_0:5;
            vuint16_t MRS_DMAE:1;
            vuint16_t MRS_IE:1;
            vuint16_t IEE:1;
        } B;
    } CTUIR;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:8;
            vuint16_t COTR:8;
        } B;
    } COTR;

    union {
        vuint16_t R;
        struct {
            vuint16_t T7_SG:1;
            vuint16_t T6_SG:1;
            vuint16_t T5_SG:1;
            vuint16_t T4_SG:1;
            vuint16_t T3_SG:1;
            vuint16_t T2_SG:1;
            vuint16_t T1_SG:1;
            vuint16_t T0_SG:1;
            vuint16_t CRU_ADC_R:1;
            vuint16_t CTU_ODIS:1;
            vuint16_t DFE:1;
            vuint16_t CGRE:1;
            vuint16_t FGRE:1;
            vuint16_t MRS_SG:1;
            vuint16_t GRE:1;
            vuint16_t TGSISR_RE:1;
        } B;
    } CTUCR;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:8;
            vuint16_t N:8;
        } B;
    } CTUDF;

};

/**************************************************************************/
/*                 Module: DMAMUX            */
/**************************************************************************/
struct DMAMUX_tag {
    union {
        vuint8_t R;
        struct {
            vuint8_t ENBL:1;
            vuint8_t TRIG:1;
            vuint8_t SOURCE:6;
        } B;
    } CHCFG[16];

};

/**************************************************************************/
/*                 Module: DSPI            */
/**************************************************************************/
struct DSPI_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t MSTR:1;
            vuint32_t CONT_SCKE:1;
            vuint32_t DCONF:2;
            vuint32_t FRZ:1;
            vuint32_t MTFE:1;
            vuint32_t PCSSE:1;
            vuint32_t ROOE:1;
            vuint32_t PCSIS7:1;
            vuint32_t PCSIS6:1;
            vuint32_t PCSIS5:1;
            vuint32_t PCSIS4:1;
            vuint32_t PCSIS3:1;
            vuint32_t PCSIS2:1;
            vuint32_t PCSIS1:1;
            vuint32_t PCSIS0:1;
            vuint32_t DOZE:1;
            vuint32_t MDIS:1;
            vuint32_t DIS_TXF:1;
            vuint32_t DIS_RXF:1;
            vuint32_t CLR_TXF:1;
            vuint32_t CLR_RXF:1;
            vuint32_t SMPL_PT:2;
            vuint32_t unused_0:4;
            vuint32_t XSPI:1;
            vuint32_t FCPCS:1;
            vuint32_t PES:1;
            vuint32_t HALT:1;
        } B;
    } MCR;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t SPI_TCNT:16;
            vuint32_t unused_0:16;
        } B;
    } TCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
        struct {
            vuint32_t FMSZ:5;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t PE:1;
            vuint32_t PP:1;
            vuint32_t unused_0:23;
        } B_SLAVE;
    } CTAR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
        struct {
            vuint32_t FMSZ:5;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t PE:1;
            vuint32_t PP:1;
            vuint32_t unused_0:23;
        } B_SLAVE;
    } CTAR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR3;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR4;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR5;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR6;

    union {
        vuint32_t R;
        struct {
            vuint32_t DBR:1;
            vuint32_t FMSZ:4;
            vuint32_t CPOL:1;
            vuint32_t CPHA:1;
            vuint32_t LSBFE:1;
            vuint32_t PCSSCK:2;
            vuint32_t PASC:2;
            vuint32_t PDT:2;
            vuint32_t PBR:2;
            vuint32_t CSSCK:4;
            vuint32_t ASC:4;
            vuint32_t DT:4;
            vuint32_t BR:4;
        } B;
    } CTAR7;

    union {
        vuint32_t R;
        struct {
            vuint32_t TCF:1;
            vuint32_t TXRXS:1;
            vuint32_t unused_3:1;
            vuint32_t EOQF:1;
            vuint32_t TFUF:1;
            vuint32_t unused_2:1;
            vuint32_t TFFF:1;
            vuint32_t BSYF:1;
            vuint32_t CMDTCF:1;
            vuint32_t unused_1:1;
            vuint32_t SPEF:1;
            vuint32_t unused_0:1;
            vuint32_t RFOF:1;
            vuint32_t TFIWF:1;
            vuint32_t RFDF:1;
            vuint32_t CMDFFF:1;
            vuint32_t TXCTR:4;
            vuint32_t TXNXTPTR:4;
            vuint32_t RXCTR:4;
            vuint32_t POPNXTPTR:4;
        } B;
    } SR;

    union {
        vuint32_t R;
        struct {
            vuint32_t TCF_RE:1;
            vuint32_t CMDFFF_RE:1;
            vuint32_t unused_4:1;
            vuint32_t EOQF_RE:1;
            vuint32_t TFUF_RE:1;
            vuint32_t unused_3:1;
            vuint32_t TFFF_RE:1;
            vuint32_t TFFF_DIRS:1;
            vuint32_t CMDTCF_RE:1;
            vuint32_t unused_2:1;
            vuint32_t SPEF_RE:1;
            vuint32_t unused_1:1;
            vuint32_t RFOF_RE:1;
            vuint32_t TFIWF_RE:1;
            vuint32_t RFDF_RE:1;
            vuint32_t RFDF_DIRS:1;
            vuint32_t CMDFFF_DIRS:1;
            vuint32_t unused_0:15;
        } B;
    } RSER;

    union {
        vuint32_t R;
        struct {
            vuint32_t CONT:1;
            vuint32_t CTAS:3;
            vuint32_t EOQ:1;
            vuint32_t CTCNT:1;
            vuint32_t PE_MASC:1;
            vuint32_t PP_MCSC:1;
            vuint32_t PCS7:1;
            vuint32_t PCS6:1;
            vuint32_t PCS5:1;
            vuint32_t PCS4:1;
            vuint32_t PCS3:1;
            vuint32_t PCS2:1;
            vuint32_t PCS1:1;
            vuint32_t PCS0:1;
            vuint32_t TXDATA:16;
        } B;
        struct {
            vuint32_t unused_0:16;
            vuint32_t TXDATA:16;
        } B_SLAVE;
    } PUSHR;

    union {
        vuint32_t R;
        struct {
            vuint32_t RXDATA:32;
        } B;
    } POPR;

    union {
        vuint32_t R;
        struct {
            vuint32_t TXCMD_TXDATA:16;
            vuint32_t TXDATA:16;
        } B;
    } TXFR[4];

    vuint8_t ADR_reserved4[48];

    union {
        vuint32_t R;
        struct {
            vuint32_t RXDATA:32;
        } B;
    } RXFR[4];

    vuint8_t ADR_reserved5[144];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t FMSZE:1;
            vuint32_t unused_0:5;
            vuint32_t DTCP:11;
        } B;
    } CTARE[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t CMDCTR:4;
            vuint32_t CMDNXTPTR:4;
        } B;
    } SREX;

};

/**************************************************************************/
/*                 Module: EDMA            */
/**************************************************************************/
struct EDMA_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:14;
            vuint32_t CX:1;
            vuint32_t ECX:1;
            vuint32_t unused_0:6;
            vuint32_t GRP0PRI:2;
            vuint32_t EMLM:1;
            vuint32_t CLM:1;
            vuint32_t HALT:1;
            vuint32_t HOE:1;
            vuint32_t ERGA:1;
            vuint32_t ERCA:1;
            vuint32_t EDBG:1;
            vuint32_t EBW:1;
        } B;
    } CR;

    union {
        vuint32_t R;
        struct {
            vuint32_t VLD:1;
            vuint32_t unused_1:13;
            vuint32_t UCE:1;
            vuint32_t ECX:1;
            vuint32_t unused_0:1;
            vuint32_t CPE:1;
            vuint32_t ERRCHN:6;
            vuint32_t SAE:1;
            vuint32_t SOE:1;
            vuint32_t DAE:1;
            vuint32_t DOE:1;
            vuint32_t NCE:1;
            vuint32_t SGE:1;
            vuint32_t SBE:1;
            vuint32_t DBE:1;
        } B;
    } ES;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t ERQ15:1;
            vuint32_t ERQ14:1;
            vuint32_t ERQ13:1;
            vuint32_t ERQ12:1;
            vuint32_t ERQ11:1;
            vuint32_t ERQ10:1;
            vuint32_t ERQ9:1;
            vuint32_t ERQ8:1;
            vuint32_t ERQ7:1;
            vuint32_t ERQ6:1;
            vuint32_t ERQ5:1;
            vuint32_t ERQ4:1;
            vuint32_t ERQ3:1;
            vuint32_t ERQ2:1;
            vuint32_t ERQ1:1;
            vuint32_t ERQ0:1;
        } B;
    } ERQL;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t EEI15:1;
            vuint32_t EEI14:1;
            vuint32_t EEI13:1;
            vuint32_t EEI12:1;
            vuint32_t EEI11:1;
            vuint32_t EEI10:1;
            vuint32_t EEI9:1;
            vuint32_t EEI8:1;
            vuint32_t EEI7:1;
            vuint32_t EEI6:1;
            vuint32_t EEI5:1;
            vuint32_t EEI4:1;
            vuint32_t EEI3:1;
            vuint32_t EEI2:1;
            vuint32_t EEI1:1;
            vuint32_t EEI0:1;
        } B;
    } EEIL;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t SAER:1;
            vuint8_t SERQ:6;
        } B;
    } SERQ;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t CAER:1;
            vuint8_t CERQ:6;
        } B;
    } CERQ;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t SAEE:1;
            vuint8_t SEEI:6;
        } B;
    } SEEI;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t CAEE:1;
            vuint8_t CEEI:6;
        } B;
    } CEEI;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t CAIR:1;
            vuint8_t CINT:6;
        } B;
    } CINT;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t CAEI:1;
            vuint8_t CERR:6;
        } B;
    } CERR;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t SAST:1;
            vuint8_t SSRT:6;
        } B;
    } SSRT;

    union {
        vuint8_t R;
        struct {
            vuint8_t NOP:1;
            vuint8_t CADN:1;
            vuint8_t CDNE:6;
        } B;
    } CDNE;

    vuint8_t ADR_reserved2[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t INT15:1;
            vuint32_t INT14:1;
            vuint32_t INT13:1;
            vuint32_t INT12:1;
            vuint32_t INT11:1;
            vuint32_t INT10:1;
            vuint32_t INT9:1;
            vuint32_t INT8:1;
            vuint32_t INT7:1;
            vuint32_t INT6:1;
            vuint32_t INT5:1;
            vuint32_t INT4:1;
            vuint32_t INT3:1;
            vuint32_t INT2:1;
            vuint32_t INT1:1;
            vuint32_t INT0:1;
        } B;
    } INTL;

    vuint8_t ADR_reserved3[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t ERR15:1;
            vuint32_t ERR14:1;
            vuint32_t ERR13:1;
            vuint32_t ERR12:1;
            vuint32_t ERR11:1;
            vuint32_t ERR10:1;
            vuint32_t ERR9:1;
            vuint32_t ERR8:1;
            vuint32_t ERR7:1;
            vuint32_t ERR6:1;
            vuint32_t ERR5:1;
            vuint32_t ERR4:1;
            vuint32_t ERR3:1;
            vuint32_t ERR2:1;
            vuint32_t ERR1:1;
            vuint32_t ERR0:1;
        } B;
    } ERRL;

    vuint8_t ADR_reserved4[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t HRS15:1;
            vuint32_t HRS14:1;
            vuint32_t HRS13:1;
            vuint32_t HRS12:1;
            vuint32_t HRS11:1;
            vuint32_t HRS10:1;
            vuint32_t HRS9:1;
            vuint32_t HRS8:1;
            vuint32_t HRS7:1;
            vuint32_t HRS6:1;
            vuint32_t HRS5:1;
            vuint32_t HRS4:1;
            vuint32_t HRS3:1;
            vuint32_t HRS2:1;
            vuint32_t HRS1:1;
            vuint32_t HRS0:1;
        } B;
    } HRSL;

    vuint8_t ADR_reserved5[200];

    union {
        vuint8_t R;
        struct {
            vuint8_t ECP:1;
            vuint8_t DPA:1;
            vuint8_t unused_0:2;
            vuint8_t CHPRI:4;
        } B;
    } DCHPRI[16];

    vuint8_t ADR_reserved6[48];

    union {
        vuint8_t R;
        struct {
            vuint8_t EMI:1;
            vuint8_t PAL:1;
            vuint8_t unused_0:2;
            vuint8_t MID:4;
        } B;
    } DCHMID[16];

    vuint8_t ADR_reserved7[3760];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t SADDR:32;
            } B;
        } TCD_SADDR;

        union {
            vuint16_t R;
            struct {
                vuint16_t SMOD:5;
                vuint16_t SSIZE:3;
                vuint16_t DMOD:5;
                vuint16_t DSIZE:3;
            } B;
        } TCD_ATTR;

        union {
            vuint16_t R;
            struct {
                vuint16_t SOFF:16;
            } B;
        } TCD_SOFF;

        union {
            vuint32_t R;
            struct {
                vuint32_t SMLOE:1;
                vuint32_t DMLOE:1;
                vuint32_t MLOFF:20;
                vuint32_t NBYTES:10;
            } B_MLOFFYES;
            struct {
                vuint32_t SMLOE:1;
                vuint32_t DMLOE:1;
                vuint32_t NBYTES:30;
            } B_MLOFFNO;
            struct {
                vuint32_t NBYTES:32;
            } B_MLNO;
        } TCD_NBYTES;

        union {
            vuint32_t R;
            struct {
                vuint32_t SLAST:32;
            } B;
        } TCD_SLAST;

        union {
            vuint32_t R;
            struct {
                vuint32_t DADDR:32;
            } B;
        } TCD_DADDR;

        union {
            vuint16_t R;
            struct {
                vuint16_t ELINK:1;
                vuint16_t unused_0:2;
                vuint16_t LINKCH:4;
                vuint16_t CITER:9;
            } B_ELINKYES;
            struct {
                vuint16_t ELINK:1;
                vuint16_t CITER:15;
            } B_ELINKNO;
        } TCD_CITER;

        union {
            vuint16_t R;
            struct {
                vuint16_t DOFF:16;
            } B;
        } TCD_DOFF;

        union {
            vuint32_t R;
            struct {
                vuint32_t DLASTSGA:32;
            } B;
        } TCD_DLASTSGA;

        union {
            vuint16_t R;
            struct {
                vuint16_t ELINK:1;
                vuint16_t unused_0:2;
                vuint16_t LINKCH:4;
                vuint16_t BITER:9;
            } B_ELINKYES;
            struct {
                vuint16_t ELINK:1;
                vuint16_t BITER:15;
            } B_ELINKNO;
        } TCD_BITER;

        union {
            vuint16_t R;
            struct {
                vuint16_t BWC:2;
                vuint16_t MAJORLINKCH:6;
                vuint16_t DONE:1;
                vuint16_t ACTIVE:1;
                vuint16_t MAJORELINK:1;
                vuint16_t ESG:1;
                vuint16_t DREQ:1;
                vuint16_t INTHALF:1;
                vuint16_t INTMAJOR:1;
                vuint16_t START:1;
            } B;
        } TCD_CSR;

    } CH[16];

};

/**************************************************************************/
/*                 Module: EIM            */
/**************************************************************************/
struct EIM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t EIMEN:1;
        } B;
    } CTRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA_MASK:32;
        } B;
    } DATA;

};

/**************************************************************************/
/*                 Module: ETIMER            */
/**************************************************************************/
struct ETIMER_tag {
    struct {
        union {
            vuint16_t R;
            struct {
                vuint16_t COMP1:16;
            } B;
        } COMP1;

        union {
            vuint16_t R;
            struct {
                vuint16_t COMP2:16;
            } B;
        } COMP2;

        union {
            vuint16_t R;
            struct {
                vuint16_t CAPT1:16;
            } B;
        } CAPT1;

        union {
            vuint16_t R;
            struct {
                vuint16_t CAPT2:16;
            } B;
        } CAPT2;

        union {
            vuint16_t R;
            struct {
                vuint16_t LOAD:16;
            } B;
        } LOAD;

        union {
            vuint16_t R;
            struct {
                vuint16_t HOLD:16;
            } B;
        } HOLD;

        union {
            vuint16_t R;
            struct {
                vuint16_t CNTR:16;
            } B;
        } CNTR;

        union {
            vuint16_t R;
            struct {
                vuint16_t CNTMODE:3;
                vuint16_t PRISRC:5;
                vuint16_t ONCE:1;
                vuint16_t LENGTH:1;
                vuint16_t DIR:1;
                vuint16_t SECSRC:5;
            } B;
        } CTRL1;

        union {
            vuint16_t R;
            struct {
                vuint16_t OEN:1;
                vuint16_t RDNT:1;
                vuint16_t INPUT:1;
                vuint16_t VAL:1;
                vuint16_t FORCE:1;
                vuint16_t COFRC:1;
                vuint16_t COINIT:2;
                vuint16_t SIPS:1;
                vuint16_t PIPS:1;
                vuint16_t OPS:1;
                vuint16_t MSTR:1;
                vuint16_t OUTMODE:4;
            } B;
        } CTRL2;

        union {
            vuint16_t R;
            struct {
                vuint16_t STPEN:1;
                vuint16_t ROC:2;
                vuint16_t FMODE:1;
                vuint16_t FDIS:4;
                vuint16_t C2FCNT:3;
                vuint16_t C1FCNT:3;
                vuint16_t DBGEN:2;
            } B;
        } CTRL3;

        union {
            vuint16_t R;
            struct {
                vuint16_t unused_0:6;
                vuint16_t WDF:1;
                vuint16_t RCF:1;
                vuint16_t ICF2:1;
                vuint16_t ICF1:1;
                vuint16_t IEHF:1;
                vuint16_t IELF:1;
                vuint16_t TOF:1;
                vuint16_t TCF2:1;
                vuint16_t TCF1:1;
                vuint16_t TCF:1;
            } B;
        } STS;

        union {
            vuint16_t R;
            struct {
                vuint16_t ICF2DE:1;
                vuint16_t ICF1DE:1;
                vuint16_t CMPLD2DE:1;
                vuint16_t CMPLD1DE:1;
                vuint16_t unused_0:2;
                vuint16_t WDFIE:1;
                vuint16_t RCFIE:1;
                vuint16_t ICF2IE:1;
                vuint16_t ICF1IE:1;
                vuint16_t IEHFIE:1;
                vuint16_t IELFIE:1;
                vuint16_t TOFIE:1;
                vuint16_t TCF2IE:1;
                vuint16_t TCF1IE:1;
                vuint16_t TCFIE:1;
            } B;
        } INTDMA;

        union {
            vuint16_t R;
            struct {
                vuint16_t CMPLD1:16;
            } B;
        } CMPLD1;

        union {
            vuint16_t R;
            struct {
                vuint16_t CMPLD2:16;
            } B;
        } CMPLD2;

        union {
            vuint16_t R;
            struct {
                vuint16_t CLC2:3;
                vuint16_t CLC1:3;
                vuint16_t CMPMODE:2;
                vuint16_t CPT2MODE:2;
                vuint16_t CPT1MODE:2;
                vuint16_t CFWM:2;
                vuint16_t ONESHOT:1;
                vuint16_t ARM:1;
            } B;
        } CCCTRL;

        union {
            vuint16_t R;
            struct {
                vuint16_t unused_0:5;
                vuint16_t FILT_CNT:3;
                vuint16_t FILT_PER:8;
            } B;
        } FILT;

    } CH[6];

    vuint8_t ADR_reserved0[64];

    union {
        vuint16_t R;
        struct {
            vuint16_t WDTOL:16;
        } B;
    } WDTOL;

    union {
        vuint16_t R;
        struct {
            vuint16_t WDTOH:16;
        } B;
    } WDTOH;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_1:3;
            vuint16_t FTEST:1;
            vuint16_t unused_0:8;
            vuint16_t FLVL:4;
        } B;
    } FCTRL;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_1:4;
            vuint16_t FFPIN:4;
            vuint16_t unused_0:4;
            vuint16_t FFLAG:4;
        } B;
    } FSTS;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:5;
            vuint16_t FFILT_CNT:3;
            vuint16_t FFILT_PER:8;
        } B;
    } FFILT;

    vuint8_t ADR_reserved1[2];

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:10;
            vuint16_t ENBL:6;
        } B;
    } ENBL;

    vuint8_t ADR_reserved2[2];

    union {
        vuint16_t R;
        struct {
            vuint16_t DREQ0_EN:1;
            vuint16_t unused_0:10;
            vuint16_t DREQ0:5;
        } B;
    } DREQ0;

    union {
        vuint16_t R;
        struct {
            vuint16_t DREQ1_EN:1;
            vuint16_t unused_0:10;
            vuint16_t DREQ1:5;
        } B;
    } DREQ1;

};

/**************************************************************************/
/*                 Module: FCCU            */
/**************************************************************************/
struct FCCU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:22;
            vuint32_t DEBUG:1;
            vuint32_t unused_1:1;
            vuint32_t OPS:2;
            vuint32_t unused_0:1;
            vuint32_t OPR:5;
        } B;
    } CTRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t CTRLK:32;
        } B;
    } CTRLK;

    union {
        vuint32_t R;
        struct {
            vuint32_t TGL:7;
            vuint32_t FCCU_SET_AFTER_RESET:1;
            vuint32_t FCCU_SET_CLEAR:2;
            vuint32_t unused_1:6;
            vuint32_t FOPE:1;
            vuint32_t FOME:2;
            vuint32_t OD:1;
            vuint32_t unused_0:1;
            vuint32_t SM:1;
            vuint32_t PS:1;
            vuint32_t FOM:3;
            vuint32_t FOP:6;
        } B;
    } CFG;

    vuint8_t ADR_reserved0[16];

    union {
        vuint32_t R;
        struct {
            vuint32_t RFC31:1;
            vuint32_t RFC30:1;
            vuint32_t RFC29:1;
            vuint32_t RFC28:1;
            vuint32_t RFC27:1;
            vuint32_t RFC26:1;
            vuint32_t RFC25:1;
            vuint32_t RFC24:1;
            vuint32_t RFC23:1;
            vuint32_t RFC22:1;
            vuint32_t RFC21:1;
            vuint32_t RFC20:1;
            vuint32_t RFC19:1;
            vuint32_t RFC18:1;
            vuint32_t RFC17:1;
            vuint32_t RFC16:1;
            vuint32_t RFC15:1;
            vuint32_t RFC14:1;
            vuint32_t RFC13:1;
            vuint32_t RFC12:1;
            vuint32_t RFC11:1;
            vuint32_t RFC10:1;
            vuint32_t RFC9:1;
            vuint32_t RFC8:1;
            vuint32_t RFC7:1;
            vuint32_t RFC6:1;
            vuint32_t RFC5:1;
            vuint32_t RFC4:1;
            vuint32_t RFC3:1;
            vuint32_t RFC2:1;
            vuint32_t RFC1:1;
            vuint32_t RFC0:1;
        } B;
    } RF_CFG[4];

    vuint8_t ADR_reserved1[32];

    union {
        vuint32_t R;
        struct {
            vuint32_t RFSC15:2;
            vuint32_t RFSC14:2;
            vuint32_t RFSC13:2;
            vuint32_t RFSC12:2;
            vuint32_t RFSC11:2;
            vuint32_t RFSC10:2;
            vuint32_t RFSC9:2;
            vuint32_t RFSC8:2;
            vuint32_t RFSC7:2;
            vuint32_t RFSC6:2;
            vuint32_t RFSC5:2;
            vuint32_t RFSC4:2;
            vuint32_t RFSC3:2;
            vuint32_t RFSC2:2;
            vuint32_t RFSC1:2;
            vuint32_t RFSC0:2;
        } B;
    } RFS_CFG[8];

    vuint8_t ADR_reserved2[20];

    union {
        vuint32_t R;
        struct {
            vuint32_t RFS31:1;
            vuint32_t RFS30:1;
            vuint32_t RFS29:1;
            vuint32_t RFS28:1;
            vuint32_t RFS27:1;
            vuint32_t RFS26:1;
            vuint32_t RFS25:1;
            vuint32_t RFS24:1;
            vuint32_t RFS23:1;
            vuint32_t RFS22:1;
            vuint32_t RFS21:1;
            vuint32_t RFS20:1;
            vuint32_t RFS19:1;
            vuint32_t RFS18:1;
            vuint32_t RFS17:1;
            vuint32_t RFS16:1;
            vuint32_t RFS15:1;
            vuint32_t RFS14:1;
            vuint32_t RFS13:1;
            vuint32_t RFS12:1;
            vuint32_t RFS11:1;
            vuint32_t RFS10:1;
            vuint32_t RFS9:1;
            vuint32_t RFS8:1;
            vuint32_t RFS7:1;
            vuint32_t RFS6:1;
            vuint32_t RFS5:1;
            vuint32_t RFS4:1;
            vuint32_t RFS3:1;
            vuint32_t RFS2:1;
            vuint32_t RFS1:1;
            vuint32_t RFS0:1;
        } B;
    } RF_S[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t RFK:32;
        } B;
    } RFK;

    union {
        vuint32_t R;
        struct {
            vuint32_t RFE31:1;
            vuint32_t RFE30:1;
            vuint32_t RFE29:1;
            vuint32_t RFE28:1;
            vuint32_t RFE27:1;
            vuint32_t RFE26:1;
            vuint32_t RFE25:1;
            vuint32_t RFE24:1;
            vuint32_t RFE23:1;
            vuint32_t RFE22:1;
            vuint32_t RFE21:1;
            vuint32_t RFE20:1;
            vuint32_t RFE19:1;
            vuint32_t RFE18:1;
            vuint32_t RFE17:1;
            vuint32_t RFE16:1;
            vuint32_t RFE15:1;
            vuint32_t RFE14:1;
            vuint32_t RFE13:1;
            vuint32_t RFE12:1;
            vuint32_t RFE11:1;
            vuint32_t RFE10:1;
            vuint32_t RFE9:1;
            vuint32_t RFE8:1;
            vuint32_t RFE7:1;
            vuint32_t RFE6:1;
            vuint32_t RFE5:1;
            vuint32_t RFE4:1;
            vuint32_t RFE3:1;
            vuint32_t RFE2:1;
            vuint32_t RFE1:1;
            vuint32_t RFE0:1;
        } B;
    } RF_E[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t RFTOE31:1;
            vuint32_t RFTOE30:1;
            vuint32_t RFTOE29:1;
            vuint32_t RFTOE28:1;
            vuint32_t RFTOE27:1;
            vuint32_t RFTOE26:1;
            vuint32_t RFTOE25:1;
            vuint32_t RFTOE24:1;
            vuint32_t RFTOE23:1;
            vuint32_t RFTOE22:1;
            vuint32_t RFTOE21:1;
            vuint32_t RFTOE20:1;
            vuint32_t RFTOE19:1;
            vuint32_t RFTOE18:1;
            vuint32_t RFTOE17:1;
            vuint32_t RFTOE16:1;
            vuint32_t RFTOE15:1;
            vuint32_t RFTOE14:1;
            vuint32_t RFTOE13:1;
            vuint32_t RFTOE12:1;
            vuint32_t RFTOE11:1;
            vuint32_t RFTOE10:1;
            vuint32_t RFTOE9:1;
            vuint32_t RFTOE8:1;
            vuint32_t RFTOE7:1;
            vuint32_t RFTOE6:1;
            vuint32_t RFTOE5:1;
            vuint32_t RFTOE4:1;
            vuint32_t RFTOE3:1;
            vuint32_t RFTOE2:1;
            vuint32_t RFTOE1:1;
            vuint32_t RFTOE0:1;
        } B;
    } RF_TOE[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t TO:32;
        } B;
    } RF_TO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t TO:3;
        } B;
    } CFG_TO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:26;
            vuint32_t EIN1:1;
            vuint32_t EIN0:1;
            vuint32_t unused_0:2;
            vuint32_t EOUT:2;
        } B;
    } EINOUT;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t PHYSICERRORPIN:2;
            vuint32_t ESTAT:1;
            vuint32_t STATUS:3;
        } B;
    } STAT;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t NAFS:8;
        } B;
    } N2AF_STATUS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:22;
            vuint32_t AF_SRC:2;
            vuint32_t AFFS:8;
        } B;
    } A2FF_STATUS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:22;
            vuint32_t NF_SRC:2;
            vuint32_t NFFS:8;
        } B;
    } N2FF_STATUS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t FAFS:8;
        } B;
    } F2A_STATUS;

    vuint8_t ADR_reserved3[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:25;
            vuint32_t FRFC:7;
        } B;
    } RFF;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t DMA_REQ:1;
            vuint32_t IRQ_EOUT:1;
            vuint32_t NMI_STAT:1;
            vuint32_t ALRM_STAT:1;
            vuint32_t CFG_TO_STAT:1;
        } B;
    } IRQ_STAT;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:28;
            vuint32_t IRQ_EOUT_EN:1;
            vuint32_t unused_0:2;
            vuint32_t CFG_TO_IEN:1;
        } B;
    } IRQ_EN;

    union {
        vuint32_t R;
        struct {
            vuint32_t XTMR:32;
        } B;
    } XTMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t VL3:1;
            vuint32_t FS3:1;
            vuint32_t unused_3:2;
            vuint32_t MCS3:4;
            vuint32_t VL2:1;
            vuint32_t FS2:1;
            vuint32_t unused_2:2;
            vuint32_t MCS2:4;
            vuint32_t VL1:1;
            vuint32_t FS1:1;
            vuint32_t unused_1:2;
            vuint32_t MCS1:4;
            vuint32_t VL0:1;
            vuint32_t FS0:1;
            vuint32_t unused_0:2;
            vuint32_t MCS0:4;
        } B;
    } MCS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t TRANSKEY:8;
        } B;
    } TRANS_LOCK;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t PERMNTKEY:8;
        } B;
    } PERMNT_LOCK;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:2;
            vuint32_t T_TRG:14;
            vuint32_t unused_0:2;
            vuint32_t DELTA_T:14;
        } B;
    } DELTA_T;

    union {
        vuint32_t R;
        struct {
            vuint32_t IRQEN31:1;
            vuint32_t IRQEN30:1;
            vuint32_t IRQEN29:1;
            vuint32_t IRQEN28:1;
            vuint32_t IRQEN27:1;
            vuint32_t IRQEN26:1;
            vuint32_t IRQEN25:1;
            vuint32_t IRQEN24:1;
            vuint32_t IRQEN23:1;
            vuint32_t IRQEN22:1;
            vuint32_t IRQEN21:1;
            vuint32_t IRQEN20:1;
            vuint32_t IRQEN19:1;
            vuint32_t IRQEN18:1;
            vuint32_t IRQEN17:1;
            vuint32_t IRQEN16:1;
            vuint32_t IRQEN15:1;
            vuint32_t IRQEN14:1;
            vuint32_t IRQEN13:1;
            vuint32_t IRQEN12:1;
            vuint32_t IRQEN11:1;
            vuint32_t IRQEN10:1;
            vuint32_t IRQEN9:1;
            vuint32_t IRQEN8:1;
            vuint32_t IRQEN7:1;
            vuint32_t IRQEN6:1;
            vuint32_t IRQEN5:1;
            vuint32_t IRQEN4:1;
            vuint32_t IRQEN3:1;
            vuint32_t IRQEN2:1;
            vuint32_t IRQEN1:1;
            vuint32_t IRQEN0:1;
        } B;
    } IRQ_ALARM_EN[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t NMIEN31:1;
            vuint32_t NMIEN30:1;
            vuint32_t NMIEN29:1;
            vuint32_t NMIEN28:1;
            vuint32_t NMIEN27:1;
            vuint32_t NMIEN26:1;
            vuint32_t NMIEN25:1;
            vuint32_t NMIEN24:1;
            vuint32_t NMIEN23:1;
            vuint32_t NMIEN22:1;
            vuint32_t NMIEN21:1;
            vuint32_t NMIEN20:1;
            vuint32_t NMIEN19:1;
            vuint32_t NMIEN18:1;
            vuint32_t NMIEN17:1;
            vuint32_t NMIEN16:1;
            vuint32_t NMIEN15:1;
            vuint32_t NMIEN14:1;
            vuint32_t NMIEN13:1;
            vuint32_t NMIEN12:1;
            vuint32_t NMIEN11:1;
            vuint32_t NMIEN10:1;
            vuint32_t NMIEN9:1;
            vuint32_t NMIEN8:1;
            vuint32_t NMIEN7:1;
            vuint32_t NMIEN6:1;
            vuint32_t NMIEN5:1;
            vuint32_t NMIEN4:1;
            vuint32_t NMIEN3:1;
            vuint32_t NMIEN2:1;
            vuint32_t NMIEN1:1;
            vuint32_t NMIEN0:1;
        } B;
    } NMI_EN[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t EOUTEN31:1;
            vuint32_t EOUTEN30:1;
            vuint32_t EOUTEN29:1;
            vuint32_t EOUTEN28:1;
            vuint32_t EOUTEN27:1;
            vuint32_t EOUTEN26:1;
            vuint32_t EOUTEN25:1;
            vuint32_t EOUTEN24:1;
            vuint32_t EOUTEN23:1;
            vuint32_t EOUTEN22:1;
            vuint32_t EOUTEN21:1;
            vuint32_t EOUTEN20:1;
            vuint32_t EOUTEN19:1;
            vuint32_t EOUTEN18:1;
            vuint32_t EOUTEN17:1;
            vuint32_t EOUTEN16:1;
            vuint32_t EOUTEN15:1;
            vuint32_t EOUTEN14:1;
            vuint32_t EOUTEN13:1;
            vuint32_t EOUTEN12:1;
            vuint32_t EOUTEN11:1;
            vuint32_t EOUTEN10:1;
            vuint32_t EOUTEN9:1;
            vuint32_t EOUTEN8:1;
            vuint32_t EOUTEN7:1;
            vuint32_t EOUTEN6:1;
            vuint32_t EOUTEN5:1;
            vuint32_t EOUTEN4:1;
            vuint32_t EOUTEN3:1;
            vuint32_t EOUTEN2:1;
            vuint32_t EOUTEN1:1;
            vuint32_t EOUTEN0:1;
        } B;
    } EOUT_SIG_EN[4];

};

/**************************************************************************/
/*                 Module: FLASH            */
/**************************************************************************/
struct FLASH_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t RRE:1;
            vuint32_t AEE:1;
            vuint32_t EEE:1;
            vuint32_t unused_3:2;
            vuint32_t DWEE:2;
            vuint32_t unused_2:8;
            vuint32_t EER:1;
            vuint32_t RWE:1;
            vuint32_t SBC:1;
            vuint32_t unused_1:1;
            vuint32_t PEAS:1;
            vuint32_t DONE:1;
            vuint32_t PEG:1;
            vuint32_t PECIE:1;
            vuint32_t FERS:1;
            vuint32_t unused_0:2;
            vuint32_t PGM:1;
            vuint32_t PSUS:1;
            vuint32_t ERS:1;
            vuint32_t ESUS:1;
            vuint32_t EHV:1;
        } B;
    } MCR;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:1;
            vuint32_t N8KH:2;
            vuint32_t N128K:5;
            vuint32_t N64KH:3;
            vuint32_t N32KH:2;
            vuint32_t N16KH:3;
            vuint32_t N64KM:3;
            vuint32_t N32KM:2;
            vuint32_t N16KM:3;
            vuint32_t N64KL:3;
            vuint32_t N32KL:2;
            vuint32_t N16KL:3;
        } B;
    } MCRE;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t TSLOCK:1;
            vuint32_t unused_0:1;
            vuint32_t LOWLOCK:14;
            vuint32_t MIDLOCK:16;
        } B;
    } LOCK0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t HIGHLOCK:16;
        } B;
    } LOCK1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:1;
            vuint32_t A128KLOCK:31;
        } B;
    } LOCK2;

    vuint8_t ADR_reserved2[28];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:2;
            vuint32_t LOWSEL:14;
            vuint32_t MIDSEL:16;
        } B;
    } SEL0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t HIGHSEL:16;
        } B;
    } SEL1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:1;
            vuint32_t A128KSEL:31;
        } B;
    } SEL2;

    vuint8_t ADR_reserved3[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t SAD:1;
            vuint32_t unused_1:7;
            vuint32_t ADDR:21;
            vuint32_t unused_0:3;
        } B;
    } ADR;

    union {
        vuint32_t R;
        struct {
            vuint32_t UTE:1;
            vuint32_t SBCE:1;
            vuint32_t unused_3:11;
            vuint32_t CPR:1;
            vuint32_t CPA:1;
            vuint32_t CPE:1;
            vuint32_t unused_2:6;
            vuint32_t NAIBP:1;
            vuint32_t AIBPE:1;
            vuint32_t unused_1:1;
            vuint32_t AISUS:1;
            vuint32_t MRE:1;
            vuint32_t MRV:1;
            vuint32_t unused_0:1;
            vuint32_t AIS:1;
            vuint32_t AIE:1;
            vuint32_t AID:1;
        } B;
    } UT0;

    union {
        vuint32_t R;
        struct {
            vuint32_t MISR31:1;
            vuint32_t MISR30:1;
            vuint32_t MISR29:1;
            vuint32_t MISR28:1;
            vuint32_t MISR27:1;
            vuint32_t MISR26:1;
            vuint32_t MISR25:1;
            vuint32_t MISR24:1;
            vuint32_t MISR23:1;
            vuint32_t MISR22:1;
            vuint32_t MISR21:1;
            vuint32_t MISR20:1;
            vuint32_t MISR19:1;
            vuint32_t MISR18:1;
            vuint32_t MISR17:1;
            vuint32_t MISR16:1;
            vuint32_t MISR15:1;
            vuint32_t MISR14:1;
            vuint32_t MISR13:1;
            vuint32_t MISR12:1;
            vuint32_t MISR11:1;
            vuint32_t MISR10:1;
            vuint32_t MISR9:1;
            vuint32_t MISR8:1;
            vuint32_t MISR7:1;
            vuint32_t MISR6:1;
            vuint32_t MISR5:1;
            vuint32_t MISR4:1;
            vuint32_t MISR3:1;
            vuint32_t MISR2:1;
            vuint32_t MISR1:1;
            vuint32_t MISR0:1;
        } B;
    } UM0;

    union {
        vuint32_t R;
        struct {
            vuint32_t MISR63:1;
            vuint32_t MISR62:1;
            vuint32_t MISR61:1;
            vuint32_t MISR60:1;
            vuint32_t MISR59:1;
            vuint32_t MISR58:1;
            vuint32_t MISR57:1;
            vuint32_t MISR56:1;
            vuint32_t MISR55:1;
            vuint32_t MISR54:1;
            vuint32_t MISR53:1;
            vuint32_t MISR52:1;
            vuint32_t MISR51:1;
            vuint32_t MISR50:1;
            vuint32_t MISR49:1;
            vuint32_t MISR48:1;
            vuint32_t MISR47:1;
            vuint32_t MISR46:1;
            vuint32_t MISR45:1;
            vuint32_t MISR44:1;
            vuint32_t MISR43:1;
            vuint32_t MISR42:1;
            vuint32_t MISR41:1;
            vuint32_t MISR40:1;
            vuint32_t MISR39:1;
            vuint32_t MISR38:1;
            vuint32_t MISR37:1;
            vuint32_t MISR36:1;
            vuint32_t MISR35:1;
            vuint32_t MISR34:1;
            vuint32_t MISR33:1;
            vuint32_t MISR32:1;
        } B;
    } UM1;

    union {
        vuint32_t R;
        struct {
            vuint32_t MISR95:1;
            vuint32_t MISR94:1;
            vuint32_t MISR93:1;
            vuint32_t MISR92:1;
            vuint32_t MISR91:1;
            vuint32_t MISR90:1;
            vuint32_t MISR89:1;
            vuint32_t MISR88:1;
            vuint32_t MISR87:1;
            vuint32_t MISR86:1;
            vuint32_t MISR85:1;
            vuint32_t MISR84:1;
            vuint32_t MISR83:1;
            vuint32_t MISR82:1;
            vuint32_t MISR81:1;
            vuint32_t MISR80:1;
            vuint32_t MISR79:1;
            vuint32_t MISR78:1;
            vuint32_t MISR77:1;
            vuint32_t MISR76:1;
            vuint32_t MISR75:1;
            vuint32_t MISR74:1;
            vuint32_t MISR73:1;
            vuint32_t MISR72:1;
            vuint32_t MISR71:1;
            vuint32_t MISR70:1;
            vuint32_t MISR69:1;
            vuint32_t MISR68:1;
            vuint32_t MISR67:1;
            vuint32_t MISR66:1;
            vuint32_t MISR65:1;
            vuint32_t MISR64:1;
        } B;
    } UM2;

    union {
        vuint32_t R;
        struct {
            vuint32_t MISR127:1;
            vuint32_t MISR126:1;
            vuint32_t MISR125:1;
            vuint32_t MISR124:1;
            vuint32_t MISR123:1;
            vuint32_t MISR122:1;
            vuint32_t MISR121:1;
            vuint32_t MISR120:1;
            vuint32_t MISR119:1;
            vuint32_t MISR118:1;
            vuint32_t MISR117:1;
            vuint32_t MISR116:1;
            vuint32_t MISR115:1;
            vuint32_t MISR114:1;
            vuint32_t MISR113:1;
            vuint32_t MISR112:1;
            vuint32_t MISR111:1;
            vuint32_t MISR110:1;
            vuint32_t MISR109:1;
            vuint32_t MISR108:1;
            vuint32_t MISR107:1;
            vuint32_t MISR106:1;
            vuint32_t MISR105:1;
            vuint32_t MISR104:1;
            vuint32_t MISR103:1;
            vuint32_t MISR102:1;
            vuint32_t MISR101:1;
            vuint32_t MISR100:1;
            vuint32_t MISR99:1;
            vuint32_t MISR98:1;
            vuint32_t MISR97:1;
            vuint32_t MISR96:1;
        } B;
    } UM3;

    vuint8_t ADR_reserved4[16];

    union {
        vuint32_t R;
        struct {
            vuint32_t MISR287:1;
            vuint32_t MISR286:1;
            vuint32_t MISR285:1;
            vuint32_t MISR284:1;
            vuint32_t MISR283:1;
            vuint32_t MISR282:1;
            vuint32_t MISR281:1;
            vuint32_t MISR280:1;
            vuint32_t MISR279:1;
            vuint32_t MISR278:1;
            vuint32_t MISR277:1;
            vuint32_t MISR276:1;
            vuint32_t MISR275:1;
            vuint32_t MISR274:1;
            vuint32_t MISR273:1;
            vuint32_t MISR272:1;
            vuint32_t MISR271:1;
            vuint32_t MISR270:1;
            vuint32_t MISR269:1;
            vuint32_t MISR268:1;
            vuint32_t MISR267:1;
            vuint32_t MISR266:1;
            vuint32_t MISR265:1;
            vuint32_t MISR264:1;
            vuint32_t MISR263:1;
            vuint32_t MISR262:1;
            vuint32_t MISR261:1;
            vuint32_t MISR260:1;
            vuint32_t MISR259:1;
            vuint32_t MISR258:1;
            vuint32_t MISR257:1;
            vuint32_t MISR256:1;
        } B;
    } UM8;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t MISR288:1;
        } B;
    } UM9;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:2;
            vuint32_t LOWOPP:14;
            vuint32_t MIDOPP:16;
        } B;
    } OPP0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t HIGHOPP:16;
        } B;
    } OPP1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:1;
            vuint32_t A128KOPP:31;
        } B;
    } OPP2;

    vuint8_t ADR_reserved5[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t PWD:32;
        } B;
    } TMD;

};

/**************************************************************************/
/*                 Module: FLEXCAN            */
/**************************************************************************/
struct FLEXCAN_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t MDIS:1;
            vuint32_t FRZ:1;
            vuint32_t FEN:1;
            vuint32_t HALT:1;
            vuint32_t NOT_RDY:1;
            vuint32_t unused_5:1;
            vuint32_t SOFT_RST:1;
            vuint32_t FRZ_ACK:1;
            vuint32_t SUPV:1;
            vuint32_t unused_4:1;
            vuint32_t WRN_EN:1;
            vuint32_t LPM_ACK:1;
            vuint32_t unused_3:2;
            vuint32_t SRX_DIS:1;
            vuint32_t BCC:1;
            vuint32_t unused_2:2;
            vuint32_t LPRIO_EN:1;
            vuint32_t AEN:1;
            vuint32_t unused_1:2;
            vuint32_t IDAM:2;
            vuint32_t unused_0:2;
            vuint32_t MAXMB:6;
        } B;
    } MCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t PRESDIV:8;
            vuint32_t RJW:2;
            vuint32_t PSEG1:3;
            vuint32_t PSEG2:3;
            vuint32_t BOFF_MSK:1;
            vuint32_t ERR_MSK:1;
            vuint32_t CLK_SRC:1;
            vuint32_t LPB:1;
            vuint32_t TWRN_MSK:1;
            vuint32_t RWRN_MSK:1;
            vuint32_t unused_0:2;
            vuint32_t SMP:1;
            vuint32_t BOFF_REC:1;
            vuint32_t TSYN:1;
            vuint32_t LBUF:1;
            vuint32_t LOM:1;
            vuint32_t PROPSEG:3;
        } B;
    } CTRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t TIMER:16;
        } B;
    } TIMER;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t MI31:1;
            vuint32_t MI30:1;
            vuint32_t MI29:1;
            vuint32_t MI28:1;
            vuint32_t MI27:1;
            vuint32_t MI26:1;
            vuint32_t MI25:1;
            vuint32_t MI24:1;
            vuint32_t MI23:1;
            vuint32_t MI22:1;
            vuint32_t MI21:1;
            vuint32_t MI20:1;
            vuint32_t MI19:1;
            vuint32_t MI18:1;
            vuint32_t MI17:1;
            vuint32_t MI16:1;
            vuint32_t MI15:1;
            vuint32_t MI14:1;
            vuint32_t MI13:1;
            vuint32_t MI12:1;
            vuint32_t MI11:1;
            vuint32_t MI10:1;
            vuint32_t MI9:1;
            vuint32_t MI8:1;
            vuint32_t MI7:1;
            vuint32_t MI6:1;
            vuint32_t MI5:1;
            vuint32_t MI4:1;
            vuint32_t MI3:1;
            vuint32_t MI2:1;
            vuint32_t MI1:1;
            vuint32_t MI0:1;
        } B;
    } RXGMASK;

    union {
        vuint32_t R;
        struct {
            vuint32_t MI31:1;
            vuint32_t MI30:1;
            vuint32_t MI29:1;
            vuint32_t MI28:1;
            vuint32_t MI27:1;
            vuint32_t MI26:1;
            vuint32_t MI25:1;
            vuint32_t MI24:1;
            vuint32_t MI23:1;
            vuint32_t MI22:1;
            vuint32_t MI21:1;
            vuint32_t MI20:1;
            vuint32_t MI19:1;
            vuint32_t MI18:1;
            vuint32_t MI17:1;
            vuint32_t MI16:1;
            vuint32_t MI15:1;
            vuint32_t MI14:1;
            vuint32_t MI13:1;
            vuint32_t MI12:1;
            vuint32_t MI11:1;
            vuint32_t MI10:1;
            vuint32_t MI9:1;
            vuint32_t MI8:1;
            vuint32_t MI7:1;
            vuint32_t MI6:1;
            vuint32_t MI5:1;
            vuint32_t MI4:1;
            vuint32_t MI3:1;
            vuint32_t MI2:1;
            vuint32_t MI1:1;
            vuint32_t MI0:1;
        } B;
    } RX14MASK;

    union {
        vuint32_t R;
        struct {
            vuint32_t MI31:1;
            vuint32_t MI30:1;
            vuint32_t MI29:1;
            vuint32_t MI28:1;
            vuint32_t MI27:1;
            vuint32_t MI26:1;
            vuint32_t MI25:1;
            vuint32_t MI24:1;
            vuint32_t MI23:1;
            vuint32_t MI22:1;
            vuint32_t MI21:1;
            vuint32_t MI20:1;
            vuint32_t MI19:1;
            vuint32_t MI18:1;
            vuint32_t MI17:1;
            vuint32_t MI16:1;
            vuint32_t MI15:1;
            vuint32_t MI14:1;
            vuint32_t MI13:1;
            vuint32_t MI12:1;
            vuint32_t MI11:1;
            vuint32_t MI10:1;
            vuint32_t MI9:1;
            vuint32_t MI8:1;
            vuint32_t MI7:1;
            vuint32_t MI6:1;
            vuint32_t MI5:1;
            vuint32_t MI4:1;
            vuint32_t MI3:1;
            vuint32_t MI2:1;
            vuint32_t MI1:1;
            vuint32_t MI0:1;
        } B;
    } RX15MASK;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t RX_ERR_COUNTER:8;
            vuint32_t TX_ERR_COUNTER:8;
        } B;
    } ECR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:14;
            vuint32_t TWRN_INT:1;
            vuint32_t RWRN_INT:1;
            vuint32_t BIT1_ERR:1;
            vuint32_t BIT0_ERR:1;
            vuint32_t ACK_ERR:1;
            vuint32_t CRC_ERR:1;
            vuint32_t FRM_ERR:1;
            vuint32_t STF_ERR:1;
            vuint32_t TX_WRN:1;
            vuint32_t RX_WRN:1;
            vuint32_t IDLE:1;
            vuint32_t TXRX:1;
            vuint32_t FLT_CONF:2;
            vuint32_t unused_1:1;
            vuint32_t BOFF_INT:1;
            vuint32_t ERR_INT:1;
            vuint32_t unused_0:1;
        } B;
    } ESR;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t BUF31M:1;
            vuint32_t BUF30M:1;
            vuint32_t BUF29M:1;
            vuint32_t BUF28M:1;
            vuint32_t BUF27M:1;
            vuint32_t BUF26M:1;
            vuint32_t BUF25M:1;
            vuint32_t BUF24M:1;
            vuint32_t BUF23M:1;
            vuint32_t BUF22M:1;
            vuint32_t BUF21M:1;
            vuint32_t BUF20M:1;
            vuint32_t BUF19M:1;
            vuint32_t BUF18M:1;
            vuint32_t BUF17M:1;
            vuint32_t BUF16M:1;
            vuint32_t BUF15M:1;
            vuint32_t BUF14M:1;
            vuint32_t BUF13M:1;
            vuint32_t BUF12M:1;
            vuint32_t BUF11M:1;
            vuint32_t BUF10M:1;
            vuint32_t BUF9M:1;
            vuint32_t BUF8M:1;
            vuint32_t BUF7M:1;
            vuint32_t BUF6M:1;
            vuint32_t BUF5M:1;
            vuint32_t BUF4M:1;
            vuint32_t BUF3M:1;
            vuint32_t BUF2M:1;
            vuint32_t BUF1M:1;
            vuint32_t BUF0M:1;
        } B;
    } IMASK1;

    vuint8_t ADR_reserved2[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t BUF31I:1;
            vuint32_t BUF30I:1;
            vuint32_t BUF29I:1;
            vuint32_t BUF28I:1;
            vuint32_t BUF27I:1;
            vuint32_t BUF26I:1;
            vuint32_t BUF25I:1;
            vuint32_t BUF24I:1;
            vuint32_t BUF23I:1;
            vuint32_t BUF22I:1;
            vuint32_t BUF21I:1;
            vuint32_t BUF20I:1;
            vuint32_t BUF19I:1;
            vuint32_t BUF18I:1;
            vuint32_t BUF17I:1;
            vuint32_t BUF16I:1;
            vuint32_t BUF15I:1;
            vuint32_t BUF14I:1;
            vuint32_t BUF13I:1;
            vuint32_t BUF12I:1;
            vuint32_t BUF11I:1;
            vuint32_t BUF10I:1;
            vuint32_t BUF9I:1;
            vuint32_t BUF8I:1;
            vuint32_t BUF7I:1;
            vuint32_t BUF6I:1;
            vuint32_t BUF5I:1;
            vuint32_t BUF4I:1;
            vuint32_t BUF3I:1;
            vuint32_t BUF2I:1;
            vuint32_t BUF1I:1;
            vuint32_t BUF0I:1;
        } B;
    } IFLAG1;

    vuint8_t ADR_reserved3[76];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t unused_1:4;
                vuint32_t CODE:4;
                vuint32_t unused_0:1;
                vuint32_t SRR:1;
                vuint32_t IDE:1;
                vuint32_t RTR:1;
                vuint32_t LENGTH:4;
                vuint32_t TIME_STAMP:16;
            } B;
        } MB_CS;

        union {
            vuint32_t R;
            struct {
                vuint32_t PRIO:3;
                vuint32_t ID:29;
            } B;
        } MB_ID;

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA_BYTE_0:8;
                vuint32_t DATA_BYTE_1:8;
                vuint32_t DATA_BYTE_2:8;
                vuint32_t DATA_BYTE_3:8;
            } B;
        } MB_DATAL;

        union {
            vuint32_t R;
            struct {
                vuint32_t DATA_BYTE_4:8;
                vuint32_t DATA_BYTE_5:8;
                vuint32_t DATA_BYTE_6:8;
                vuint32_t DATA_BYTE_7:8;
            } B;
        } MB_DATAH;

    } MB[32];

    vuint8_t ADR_reserved4[1536];

    union {
        vuint32_t R;
        struct {
            vuint32_t MI31:1;
            vuint32_t MI30:1;
            vuint32_t MI29:1;
            vuint32_t MI28:1;
            vuint32_t MI27:1;
            vuint32_t MI26:1;
            vuint32_t MI25:1;
            vuint32_t MI24:1;
            vuint32_t MI23:1;
            vuint32_t MI22:1;
            vuint32_t MI21:1;
            vuint32_t MI20:1;
            vuint32_t MI19:1;
            vuint32_t MI18:1;
            vuint32_t MI17:1;
            vuint32_t MI16:1;
            vuint32_t MI15:1;
            vuint32_t MI14:1;
            vuint32_t MI13:1;
            vuint32_t MI12:1;
            vuint32_t MI11:1;
            vuint32_t MI10:1;
            vuint32_t MI9:1;
            vuint32_t MI8:1;
            vuint32_t MI7:1;
            vuint32_t MI6:1;
            vuint32_t MI5:1;
            vuint32_t MI4:1;
            vuint32_t MI3:1;
            vuint32_t MI2:1;
            vuint32_t MI1:1;
            vuint32_t MI0:1;
        } B;
    } RXIMR[32];

};

/**************************************************************************/
/*                 Module: INTC            */
/**************************************************************************/
struct INTC_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t HVEN0:1;
        } B;
    } BCR;

    vuint8_t ADR_reserved0[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t PRI:5;
        } B;
    } CPR[1];

    vuint8_t ADR_reserved1[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t VTBA:20;
            vuint32_t INTVEC:10;
            vuint32_t unused_0:2;
        } B;
    } IACKR[1];

    vuint8_t ADR_reserved2[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t EOI:32;
        } B;
    } EOIR[1];

    vuint8_t ADR_reserved3[12];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:6;
            vuint8_t SET:1;
            vuint8_t CLR:1;
        } B;
    } SSCIR[32];

    union {
        struct {
            union {
                vuint16_t R;
                union {
				    struct {
                        vuint16_t PRC_SEL:4;
                        vuint16_t unused_0:6;
                        vuint16_t PRI:6;
                    } B;
				    struct {
                        vuint16_t PRC_SEL0:1;
                        vuint16_t unused_0:9;
                        vuint16_t PRI:6;
                    } B_PRC_SEL_BITS;
                };
            } PSR_NOSWT[32];
            union {
                vuint16_t R;
                union {
				    struct {
                        vuint16_t PRC_SEL:4;
                        vuint16_t unused_1:3;
                        vuint16_t SWT:1;
                        vuint16_t unused_0:2;
                        vuint16_t PRI:6;
                    } B;
				    struct {
                        vuint16_t PRC_SEL0:1;
                        vuint16_t unused_1:6;
                        vuint16_t SWT:1;
                        vuint16_t unused_0:2;
                        vuint16_t PRI:6;
                    } B_PRC_SEL_BITS;
                };				
            } PSR_SWT[992];
        };
        struct {
            vuint16_t R;
            
        } PSR[1024];
    };            

};

/**************************************************************************/
/*                 Module: JDC            */
/**************************************************************************/
struct JDC_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t JIN_IEN:1;
            vuint32_t unused_0:15;
            vuint32_t JOUT_IEN:1;
        } B;
    } MCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:13;
            vuint32_t JIN_RDY:1;
            vuint32_t unused_2:1;
            vuint32_t JIN_INT:1;
            vuint32_t unused_1:13;
            vuint32_t JOUT_RDY:1;
            vuint32_t unused_0:1;
            vuint32_t JOUT_INT:1;
        } B;
    } MSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA:32;
        } B;
    } JOUT_IPS;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA:32;
        } B;
    } JIN_IPS;

};

/**************************************************************************/
/*                 Module: JTAGM            */
/**************************************************************************/
struct JTAGM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t SWRESET:1;
            vuint32_t EVTO0_SENSE:2;
            vuint32_t EVTO1_SENSE:2;
            vuint32_t EVTO_IE:1;
            vuint32_t EVTI0_ASSERT:1;
            vuint32_t EVTI1_ASSERT:1;
            vuint32_t unused_1:10;
            vuint32_t INTER_JTAG_FRAME_TIMER:6;
            vuint32_t unused_0:1;
            vuint32_t SIE:1;
            vuint32_t IIE:1;
            vuint32_t TCKSEL:3;
            vuint32_t JTAGM_JCOMP:1;
            vuint32_t DTM:1;
        } B;
    } MCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:8;
            vuint32_t DCI_STATUS:8;
            vuint32_t EVTO0_EDGE:1;
            vuint32_t EVTO1_EDGE:1;
            vuint32_t SPU_INT_CLR:1;
            vuint32_t SPU_INT:1;
            vuint32_t unused_1:1;
            vuint32_t NEXUS_ERR:1;
            vuint32_t IDLE:1;
            vuint32_t NR:1;
            vuint32_t EVTO0_CLR:1;
            vuint32_t EVTO1_CLR:1;
            vuint32_t unused_0:6;
        } B;
    } SR;

    union {
        vuint32_t R;
        struct {
            vuint32_t TMS_HIGH:32;
        } B;
    } DOR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t TMS_LOW:28;
            vuint32_t unused_0:4;
        } B;
    } DOR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t TDI_HIGH:32;
        } B;
    } DOR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t TDI_LOW:28;
            vuint32_t unused_0:3;
            vuint32_t SEND:1;
        } B;
    } DOR3;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t TDO_LOW:32;
        } B;
    } DIR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t TDO_HIGH:28;
            vuint32_t unused_0:4;
        } B;
    } DIR1;

};

/**************************************************************************/
/*                 Module: LINFLEXD            */
/**************************************************************************/
struct LINFLEXD_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t CCD:1;
            vuint32_t CFD:1;
            vuint32_t LASE:1;
            vuint32_t AUTOWU:1;
            vuint32_t MBL:4;
            vuint32_t BF:1;
            vuint32_t unused_0:1;
            vuint32_t LBKM:1;
            vuint32_t MME:1;
            vuint32_t SSBL:1;
            vuint32_t RBLM:1;
            vuint32_t SLEEP:1;
            vuint32_t INIT:1;
        } B;
    } LINCR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t SZIE:1;
            vuint32_t OCIE:1;
            vuint32_t BEIE:1;
            vuint32_t CEIE:1;
            vuint32_t HEIE:1;
            vuint32_t unused_0:2;
            vuint32_t FEIE:1;
            vuint32_t BOIE:1;
            vuint32_t LSIE:1;
            vuint32_t WUIE:1;
            vuint32_t DBFIE:1;
            vuint32_t DBEIE_TOIE:1;
            vuint32_t DRIE:1;
            vuint32_t DTIE:1;
            vuint32_t HRIE:1;
        } B;
    } LINIER;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:12;
            vuint32_t AUTOSYNC_COMP:1;
            vuint32_t RDC:3;
            vuint32_t LINS:4;
            vuint32_t unused_0:2;
            vuint32_t RMB:1;
            vuint32_t DRBNE:1;
            vuint32_t RXBUSY:1;
            vuint32_t RDI:1;
            vuint32_t WUF:1;
            vuint32_t DBFF:1;
            vuint32_t DBEF:1;
            vuint32_t DRF:1;
            vuint32_t DTF:1;
            vuint32_t HRF:1;
        } B;
    } LINSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t SZF:1;
            vuint32_t OCF:1;
            vuint32_t BEF:1;
            vuint32_t CEF:1;
            vuint32_t SFEF:1;
            vuint32_t SDEF:1;
            vuint32_t IDPEF:1;
            vuint32_t FEF:1;
            vuint32_t BOF:1;
            vuint32_t unused_0:6;
            vuint32_t NF:1;
        } B;
    } LINESR;

    union {
        vuint32_t R;
        struct {
            vuint32_t MIS:1;
            vuint32_t CSP:3;
            vuint32_t OSR:4;
            vuint32_t ROSE:1;
            vuint32_t NEF:3;
            vuint32_t DTU_PCETX:1;
            vuint32_t SBUR:2;
            vuint32_t WLS:1;
            vuint32_t TDFL_TFC:3;
            vuint32_t RDFL_RFC:3;
            vuint32_t RFBM:1;
            vuint32_t TFBM:1;
            vuint32_t WL1:1;
            vuint32_t PC1:1;
            vuint32_t RXEN:1;
            vuint32_t TXEN:1;
            vuint32_t PC0:1;
            vuint32_t PCE:1;
            vuint32_t WL0:1;
            vuint32_t UART:1;
        } B;
    } UARTCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t SZF:1;
            vuint32_t OCF:1;
            vuint32_t PE:4;
            vuint32_t RMB:1;
            vuint32_t FEF:1;
            vuint32_t BOF:1;
            vuint32_t RDI:1;
            vuint32_t WUF:1;
            vuint32_t RFNE:1;
            vuint32_t TO:1;
            vuint32_t DRF_RFE:1;
            vuint32_t DTF_TFF:1;
            vuint32_t NF:1;
        } B;
    } UARTSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:21;
            vuint32_t MODE:1;
            vuint32_t IOT:1;
            vuint32_t TOCE:1;
            vuint32_t CNT:8;
        } B;
    } LINTCSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t OC2:8;
            vuint32_t OC1:8;
        } B;
    } LINOCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:20;
            vuint32_t RTO:4;
            vuint32_t unused_0:1;
            vuint32_t HTO:7;
        } B;
    } LINTOCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t FBR:4;
        } B;
    } LINFBRR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t IBR:20;
        } B;
    } LINIBRR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t CF:8;
        } B;
    } LINCFR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t TBDE:1;
            vuint32_t IOBE:1;
            vuint32_t IOPE:1;
            vuint32_t WURQ:1;
            vuint32_t DDRQ:1;
            vuint32_t DTRQ:1;
            vuint32_t ABRQ:1;
            vuint32_t HTRQ:1;
            vuint32_t unused_0:8;
        } B;
    } LINCR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t DFL:6;
            vuint32_t DIR:1;
            vuint32_t CCS:1;
            vuint32_t unused_0:2;
            vuint32_t ID:6;
        } B;
    } BIDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA3:8;
            vuint32_t DATA2:8;
            vuint32_t DATA1:8;
            vuint32_t DATA0:8;
        } B;
    } BDRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA7:8;
            vuint32_t DATA6:8;
            vuint32_t DATA5:8;
            vuint32_t DATA4:8;
        } B;
    } BDRM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t FACT:16;
        } B;
    } IFER;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t IFMI:5;
        } B;
    } IFMI;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t IFM:8;
        } B;
    } IFMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t DFL:6;
            vuint32_t DIR:1;
            vuint32_t CCS:1;
            vuint32_t unused_0:2;
            vuint32_t ID:6;
        } B;
    } IFCR[16];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t TDFBM:1;
            vuint32_t RDFBM:1;
            vuint32_t TDLIS:1;
            vuint32_t RDLIS:1;
            vuint32_t STOP:1;
            vuint32_t SR:1;
        } B;
    } GCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t PTO:12;
        } B;
    } UARTPTO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t CTO:12;
        } B;
    } UARTCTO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t DTE:16;
        } B;
    } DMATXE;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t DRE:16;
        } B;
    } DMARXE;

};

/**************************************************************************/
/*                 Module: LINFLEXD_MASTERONLY            */
/**************************************************************************/
struct LINFLEXD_MASTERONLY_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t CCD:1;
            vuint32_t CFD:1;
            vuint32_t LASE:1;
            vuint32_t AUTOWU:1;
            vuint32_t MBL:4;
            vuint32_t BF:1;
            vuint32_t unused_0:1;
            vuint32_t LBKM:1;
            vuint32_t MME:1;
            vuint32_t SSBL:1;
            vuint32_t RBLM:1;
            vuint32_t SLEEP:1;
            vuint32_t INIT:1;
        } B;
    } LINCR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t SZIE:1;
            vuint32_t OCIE:1;
            vuint32_t BEIE:1;
            vuint32_t CEIE:1;
            vuint32_t HEIE:1;
            vuint32_t unused_0:2;
            vuint32_t FEIE:1;
            vuint32_t BOIE:1;
            vuint32_t LSIE:1;
            vuint32_t WUIE:1;
            vuint32_t DBFIE:1;
            vuint32_t DBEIE_TOIE:1;
            vuint32_t DRIE:1;
            vuint32_t DTIE:1;
            vuint32_t HRIE:1;
        } B;
    } LINIER;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:12;
            vuint32_t AUTOSYNC_COMP:1;
            vuint32_t RDC:3;
            vuint32_t LINS:4;
            vuint32_t unused_0:2;
            vuint32_t RMB:1;
            vuint32_t DRBNE:1;
            vuint32_t RXBUSY:1;
            vuint32_t RDI:1;
            vuint32_t WUF:1;
            vuint32_t DBFF:1;
            vuint32_t DBEF:1;
            vuint32_t DRF:1;
            vuint32_t DTF:1;
            vuint32_t HRF:1;
        } B;
    } LINSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t SZF:1;
            vuint32_t OCF:1;
            vuint32_t BEF:1;
            vuint32_t CEF:1;
            vuint32_t SFEF:1;
            vuint32_t SDEF:1;
            vuint32_t IDPEF:1;
            vuint32_t FEF:1;
            vuint32_t BOF:1;
            vuint32_t unused_0:6;
            vuint32_t NF:1;
        } B;
    } LINESR;

    union {
        vuint32_t R;
        struct {
            vuint32_t MIS:1;
            vuint32_t CSP:3;
            vuint32_t OSR:4;
            vuint32_t ROSE:1;
            vuint32_t NEF:3;
            vuint32_t DTU_PCETX:1;
            vuint32_t SBUR:2;
            vuint32_t WLS:1;
            vuint32_t TDFL_TFC:3;
            vuint32_t RDFL_RFC:3;
            vuint32_t RFBM:1;
            vuint32_t TFBM:1;
            vuint32_t WL1:1;
            vuint32_t PC1:1;
            vuint32_t RXEN:1;
            vuint32_t TXEN:1;
            vuint32_t PC0:1;
            vuint32_t PCE:1;
            vuint32_t WL0:1;
            vuint32_t UART:1;
        } B;
    } UARTCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t SZF:1;
            vuint32_t OCF:1;
            vuint32_t PE:4;
            vuint32_t RMB:1;
            vuint32_t FEF:1;
            vuint32_t BOF:1;
            vuint32_t RDI:1;
            vuint32_t WUF:1;
            vuint32_t RFNE:1;
            vuint32_t TO:1;
            vuint32_t DRF_RFE:1;
            vuint32_t DTF_TFF:1;
            vuint32_t NF:1;
        } B;
    } UARTSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:21;
            vuint32_t MODE:1;
            vuint32_t IOT:1;
            vuint32_t TOCE:1;
            vuint32_t CNT:8;
        } B;
    } LINTCSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t OC2:8;
            vuint32_t OC1:8;
        } B;
    } LINOCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:20;
            vuint32_t RTO:4;
            vuint32_t unused_0:1;
            vuint32_t HTO:7;
        } B;
    } LINTOCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t FBR:4;
        } B;
    } LINFBRR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t IBR:20;
        } B;
    } LINIBRR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t CF:8;
        } B;
    } LINCFR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t TBDE:1;
            vuint32_t IOBE:1;
            vuint32_t IOPE:1;
            vuint32_t WURQ:1;
            vuint32_t DDRQ:1;
            vuint32_t DTRQ:1;
            vuint32_t ABRQ:1;
            vuint32_t HTRQ:1;
            vuint32_t unused_0:8;
        } B;
    } LINCR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t DFL:6;
            vuint32_t DIR:1;
            vuint32_t CCS:1;
            vuint32_t unused_0:2;
            vuint32_t ID:6;
        } B;
    } BIDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA3:8;
            vuint32_t DATA2:8;
            vuint32_t DATA1:8;
            vuint32_t DATA0:8;
        } B;
    } BDRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t DATA7:8;
            vuint32_t DATA6:8;
            vuint32_t DATA5:8;
            vuint32_t DATA4:8;
        } B;
    } BDRM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t FACT:16;
        } B;
    } IFER;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t IFMI:5;
        } B;
    } IFMI;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t IFM:8;
        } B;
    } IFMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t TDFBM:1;
            vuint32_t RDFBM:1;
            vuint32_t TDLIS:1;
            vuint32_t RDLIS:1;
            vuint32_t STOP:1;
            vuint32_t SR:1;
        } B;
    } GCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t PTO:12;
        } B;
    } UARTPTO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:20;
            vuint32_t CTO:12;
        } B;
    } UARTCTO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t DTE:16;
        } B;
    } DMATXE;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t DRE:16;
        } B;
    } DMARXE;

};

/**************************************************************************/
/*                 Module: MC_CGM            */
/**************************************************************************/
struct MC_CGM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t SDUR:8;
            vuint32_t unused_0:24;
        } B;
    } PCS_SDUR;

    union {
        vuint32_t R;
        struct {
            vuint32_t INIT:16;
            vuint32_t unused_0:8;
            vuint32_t RATE:8;
        } B;
    } PCS_DIVC1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVS:20;
        } B;
    } PCS_DIVS1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVE:20;
        } B;
    } PCS_DIVE1;

    union {
        vuint32_t R;
        struct {
            vuint32_t INIT:16;
            vuint32_t unused_0:8;
            vuint32_t RATE:8;
        } B;
    } PCS_DIVC2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVS:20;
        } B;
    } PCS_DIVS2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVE:20;
        } B;
    } PCS_DIVE2;

    vuint8_t ADR_reserved0[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t INIT:16;
            vuint32_t unused_0:8;
            vuint32_t RATE:8;
        } B;
    } PCS_DIVC4;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVS:20;
        } B;
    } PCS_DIVS4;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:12;
            vuint32_t DIVE:20;
        } B;
    } PCS_DIVE4;

    vuint8_t ADR_reserved1[156];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t SYS_DIV_RATIO_CHNG:1;
        } B;
    } SC_DIV_RC;

    union {
        vuint32_t R;
        struct {
            vuint32_t SYS_UPD_TYPE:1;
            vuint32_t unused_0:29;
            vuint32_t AUX1_UPD_TYPE:1;
            vuint32_t AUX0_UPD_TYPE:1;
        } B;
    } DIV_UPD_TYPE;

    union {
        vuint32_t R;
        struct {
            vuint32_t DIV_UPD_TRIGGER:32;
        } B;
    } DIV_UPD_TRIG;

    union {
        vuint32_t R;
        struct {
            vuint32_t SYS_UPD_STAT:1;
            vuint32_t unused_0:29;
            vuint32_t AUX1_UPD_STAT:1;
            vuint32_t AUX0_UPD_STAT:1;
        } B;
    } DIV_UPD_STAT;

    vuint8_t ADR_reserved2[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:4;
            vuint32_t SELSTAT:4;
            vuint32_t unused_1:4;
            vuint32_t SWTRG:3;
            vuint32_t SWIP:1;
            vuint32_t unused_0:16;
        } B;
    } SC_SS;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:12;
            vuint32_t DIV:3;
            vuint32_t unused_0:16;
        } B;
    } SC_DC0;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:11;
            vuint32_t DIV:4;
            vuint32_t unused_0:16;
        } B;
    } SC_DC1;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:7;
            vuint32_t DIV:8;
            vuint32_t unused_0:16;
        } B;
    } SC_DC2;

    vuint8_t ADR_reserved3[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELCTL:4;
            vuint32_t unused_0:24;
        } B;
    } AC0_SC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELSTAT:4;
            vuint32_t unused_0:24;
        } B;
    } AC0_SS;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:11;
            vuint32_t DIV:4;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC0;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:8;
            vuint32_t DIV:7;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC1;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:8;
            vuint32_t DIV:7;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC2;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:8;
            vuint32_t DIV:7;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC3;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:11;
            vuint32_t DIV:4;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC4;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:11;
            vuint32_t DIV:4;
            vuint32_t unused_0:16;
        } B;
    } AC0_DC5;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELCTL:4;
            vuint32_t unused_0:24;
        } B;
    } AC1_SC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELSTAT:4;
            vuint32_t unused_0:24;
        } B;
    } AC1_SS;

    union {
        vuint32_t R;
        struct {
            vuint32_t DE:1;
            vuint32_t unused_1:9;
            vuint32_t DIV:6;
            vuint32_t unused_0:16;
        } B;
    } AC1_DC0;

    vuint8_t ADR_reserved4[20];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELCTL:4;
            vuint32_t unused_0:24;
        } B;
    } AC2_SC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELSTAT:4;
            vuint32_t unused_0:24;
        } B;
    } AC2_SS;

    vuint8_t ADR_reserved5[24];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELCTL:4;
            vuint32_t unused_0:24;
        } B;
    } AC3_SC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t SELSTAT:4;
            vuint32_t unused_0:24;
        } B;
    } AC3_SS;

};

/**************************************************************************/
/*                 Module: MC_ME            */
/**************************************************************************/
struct MC_ME_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t S_CURRENT_MODE:4;
            vuint32_t S_MTRANS:1;
            vuint32_t unused_3:3;
            vuint32_t S_PDO:1;
            vuint32_t unused_2:2;
            vuint32_t S_MVR:1;
            vuint32_t unused_1:2;
            vuint32_t S_FLA:2;
            vuint32_t unused_0:8;
            vuint32_t S_PLL1:1;
            vuint32_t S_PLL0:1;
            vuint32_t S_XOSC:1;
            vuint32_t S_IRCOSC:1;
            vuint32_t S_SYSCLK:4;
        } B;
    } GS;

    union {
        vuint32_t R;
        struct {
            vuint32_t TARGET_MODE:4;
            vuint32_t unused_0:12;
            vuint32_t KEY:16;
        } B;
    } MCTL;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:16;
            vuint32_t RESET_DEST:1;
            vuint32_t unused_1:4;
            vuint32_t STOP0:1;
            vuint32_t unused_0:1;
            vuint32_t HALT0:1;
            vuint32_t RUN3:1;
            vuint32_t RUN2:1;
            vuint32_t RUN1:1;
            vuint32_t RUN0:1;
            vuint32_t DRUN:1;
            vuint32_t SAFE:1;
            vuint32_t TEST:1;
            vuint32_t RESET_FUNC:1;
        } B;
    } ME;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t I_ICONF_CC:1;
            vuint32_t I_ICONF_CU:1;
            vuint32_t I_ICONF:1;
            vuint32_t I_IMODE:1;
            vuint32_t I_SAFE:1;
            vuint32_t I_MTC:1;
        } B;
    } IS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t M_ICONF_CC:1;
            vuint32_t M_ICONF_CU:1;
            vuint32_t M_ICONF:1;
            vuint32_t M_IMODE:1;
            vuint32_t M_SAFE:1;
            vuint32_t M_MTC:1;
        } B;
    } IM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t S_MRIG:1;
            vuint32_t S_MTI:1;
            vuint32_t S_MRI:1;
            vuint32_t S_DMA:1;
            vuint32_t S_NMA:1;
            vuint32_t S_SEA:1;
        } B;
    } IMTS;

    union {
        vuint32_t R;
        struct {
            vuint32_t PREVIOUS_MODE:4;
            vuint32_t unused_3:4;
            vuint32_t MPH_BUSY:1;
            vuint32_t unused_2:2;
            vuint32_t PMC_PROG:1;
            vuint32_t DBG_MODE:1;
            vuint32_t CCKL_PROG:1;
            vuint32_t PCS_PROG:1;
            vuint32_t SMR:1;
            vuint32_t unused_1:1;
            vuint32_t VREG_CSRC_SC:1;
            vuint32_t CSRC_CSRC_SC:1;
            vuint32_t IRCOSC_SC:1;
            vuint32_t SCSRC_SC:1;
            vuint32_t SYSCLK_SW:1;
            vuint32_t unused_0:1;
            vuint32_t FLASH_SC:1;
            vuint32_t CDP_PRPH_224_255:1;
            vuint32_t CDP_PRPH_192_223:1;
            vuint32_t CDP_PRPH_160_191:1;
            vuint32_t CDP_PRPH_128_159:1;
            vuint32_t CDP_PRPH_96_127:1;
            vuint32_t CDP_PRPH_64_95:1;
            vuint32_t CDP_PRPH_32_63:1;
            vuint32_t CDP_PRPH_0_31:1;
        } B;
    } DMTS;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } RESET_MC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } TEST_MC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } SAFE_MC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } DRUN_MC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } RUN_MC[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } HALT0_MC;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:1;
            vuint32_t PWRLVL:3;
            vuint32_t unused_3:4;
            vuint32_t PDO:1;
            vuint32_t unused_2:2;
            vuint32_t MVRON:1;
            vuint32_t unused_1:2;
            vuint32_t FLAON:2;
            vuint32_t unused_0:8;
            vuint32_t PLL1ON:1;
            vuint32_t PLL0ON:1;
            vuint32_t XOSCON:1;
            vuint32_t IRCOSCON:1;
            vuint32_t SYSCLK:4;
        } B;
    } STOP0_MC;

    vuint8_t ADR_reserved2[20];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:1;
            vuint32_t S_PIT_0:1;
            vuint32_t unused_0:30;
        } B;
    } PS0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:25;
            vuint32_t S_CRC_0:1;
            vuint32_t unused_1:1;
            vuint32_t S_DMAMUX_0:1;
            vuint32_t unused_0:4;
        } B;
    } PS1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t S_LINFLEXD_0:1;
            vuint32_t unused_1:12;
            vuint32_t S_FLEXCAN_0:1;
            vuint32_t unused_0:15;
        } B;
    } PS2;

    union {
        vuint32_t R;
        struct {
            vuint32_t S_ADCSAR_0:1;
            vuint32_t S_ADCSEQ_0:1;
            vuint32_t unused_2:12;
            vuint32_t S_ADCSEQ_B:1;
            vuint32_t S_ADCSAR_B:1;
            vuint32_t unused_1:12;
            vuint32_t S_DSPI_0:1;
            vuint32_t S_DSPI_1:1;
            vuint32_t unused_0:2;
        } B;
    } PS3;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t S_ETIMER_2:1;
            vuint32_t S_ETIMER_3:1;
            vuint32_t S_ETIMER_0:1;
            vuint32_t S_ETIMER_1:1;
        } B;
    } PS4;

    vuint8_t ADR_reserved3[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t S_LINFLEXD_1:1;
            vuint32_t unused_1:12;
            vuint32_t S_FLEXCAN_1:1;
            vuint32_t unused_0:15;
        } B;
    } PS6;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t S_CTU:1;
            vuint32_t unused_1:16;
            vuint32_t S_DSPI_2:1;
            vuint32_t unused_0:3;
        } B;
    } PS7;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t RUN3:1;
            vuint32_t RUN2:1;
            vuint32_t RUN1:1;
            vuint32_t RUN0:1;
            vuint32_t DRUN:1;
            vuint32_t SAFE:1;
            vuint32_t TEST:1;
            vuint32_t RESET:1;
        } B;
    } RUN_PC[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:21;
            vuint32_t STOP0:1;
            vuint32_t unused_1:1;
            vuint32_t HALT0:1;
            vuint32_t unused_0:8;
        } B;
    } LP_PC[8];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:2;
            vuint8_t LP_CFG:3;
            vuint8_t RUN_CFG:3;
        } B;
    } PCTL[256];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:30;
            vuint32_t S_CORE1:1;
            vuint32_t S_CORE0:1;
        } B;
    } CS;

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_1:5;
            vuint16_t STOP0:1;
            vuint16_t unused_0:1;
            vuint16_t HALT0:1;
            vuint16_t RUN3:1;
            vuint16_t RUN2:1;
            vuint16_t RUN1:1;
            vuint16_t RUN0:1;
            vuint16_t DRUN:1;
            vuint16_t SAFE:1;
            vuint16_t TEST:1;
            vuint16_t RESET:1;
        } B;
    } CCTL0;

    vuint8_t ADR_reserved17[26];

    union {
        vuint32_t R;
        struct {
            vuint32_t ADDR:30;
            vuint32_t unused_0:1;
            vuint32_t RMC:1;
        } B;
    } CADDR0;

};

/**************************************************************************/
/*                 Module: MC_PCU            */
/**************************************************************************/
struct MC_PCU_tag {
    vuint8_t ADR_reserved0[64];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t PD0:1;
        } B;
    } PSTAT;

};

/**************************************************************************/
/*                 Module: MC_RGM            */
/**************************************************************************/
struct MC_RGM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t F_VOR_DEST:1;
            vuint32_t F_TSR_DEST:1;
            vuint32_t unused_3:8;
            vuint32_t F_SSCM:1;
            vuint32_t unused_2:3;
            vuint32_t F_JTAG_DEST:1;
            vuint32_t F_FIF:1;
            vuint32_t F_EDR:1;
            vuint32_t unused_1:2;
            vuint32_t F_SUF:1;
            vuint32_t F_FFRR:1;
            vuint32_t F_SOFT_DEST:1;
            vuint32_t unused_0:1;
            vuint32_t F_PORST:1;
            vuint32_t F_POR:1;
        } B;
    } DES;

    vuint8_t ADR_reserved0[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t D_VOR_DEST:1;
            vuint32_t D_TSR_DEST:1;
            vuint32_t unused_3:8;
            vuint32_t D_SSCM:1;
            vuint32_t unused_2:3;
            vuint32_t D_JTAG_DEST:1;
            vuint32_t D_FIF:1;
            vuint32_t D_EDR:1;
            vuint32_t unused_1:2;
            vuint32_t D_SUF:1;
            vuint32_t D_FFRR:1;
            vuint32_t D_SOFT_DEST:1;
            vuint32_t unused_0:1;
            vuint32_t D_PORST:1;
            vuint32_t D_POR:1;
        } B;
    } DERD;

    vuint8_t ADR_reserved1[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:8;
            vuint32_t AR_TSR_DEST:1;
            vuint32_t unused_1:21;
            vuint32_t AR_PORST:1;
            vuint32_t unused_0:1;
        } B;
    } DEAR;

    vuint8_t ADR_reserved2[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t BE_VOR_DEST:1;
            vuint32_t BE_TSR_DEST:1;
            vuint32_t unused_3:8;
            vuint32_t BE_SSCM:1;
            vuint32_t unused_2:3;
            vuint32_t BE_JTAG_DEST:1;
            vuint32_t BE_FIF:1;
            vuint32_t BE_EDR:1;
            vuint32_t unused_1:2;
            vuint32_t BE_SUF:1;
            vuint32_t BE_FFRR:1;
            vuint32_t BE_SOFT_DEST:1;
            vuint32_t unused_0:1;
            vuint32_t BE_PORST:1;
            vuint32_t BE_POR:1;
        } B;
    } DBRE;

    vuint8_t ADR_reserved3[716];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t F_VOR_FUNC:1;
            vuint32_t F_TSR_FUNC:1;
            vuint32_t unused_3:12;
            vuint32_t F_JTAG_FUNC:1;
            vuint32_t unused_2:3;
            vuint32_t F_FCCU_SOFT:1;
            vuint32_t F_FCCU_HARD:1;
            vuint32_t unused_1:1;
            vuint32_t F_SOFT_FUNC:1;
            vuint32_t F_ST_DONE:1;
            vuint32_t F_WAKEUP:1;
            vuint32_t unused_0:1;
        } B;
    } FES;

    vuint8_t ADR_reserved4[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t D_VOR_FUNC:1;
            vuint32_t D_TSR_FUNC:1;
            vuint32_t unused_3:12;
            vuint32_t D_JTAG_FUNC:1;
            vuint32_t unused_2:3;
            vuint32_t D_FCCU_SOFT:1;
            vuint32_t D_FCCU_HARD:1;
            vuint32_t unused_1:1;
            vuint32_t D_SOFT_FUNC:1;
            vuint32_t D_ST_DONE:1;
            vuint32_t D_WAKEUP:1;
            vuint32_t unused_0:1;
        } B;
    } FERD;

    vuint8_t ADR_reserved5[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:7;
            vuint32_t AR_VOR_FUNC:1;
            vuint32_t AR_TSR_FUNC:1;
            vuint32_t unused_2:16;
            vuint32_t AR_FCCU_SOFT:1;
            vuint32_t unused_1:4;
            vuint32_t AR_WAKEUP:1;
            vuint32_t unused_0:1;
        } B;
    } FEAR;

    vuint8_t ADR_reserved6[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t BE_VOR_FUNC:1;
            vuint32_t BE_TSR_FUNC:1;
            vuint32_t unused_3:12;
            vuint32_t BE_JTAG_FUNC:1;
            vuint32_t unused_2:3;
            vuint32_t BE_FCCU_SOFT:1;
            vuint32_t BE_FCCU_HARD:1;
            vuint32_t unused_1:1;
            vuint32_t BE_SOFT_FUNC:1;
            vuint32_t BE_ST_DONE:1;
            vuint32_t BE_WAKEUP:1;
            vuint32_t unused_0:1;
        } B;
    } FBRE;

    vuint8_t ADR_reserved7[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:7;
            vuint32_t SS_VOR_FUNC:1;
            vuint32_t SS_TSR_FUNC:1;
            vuint32_t unused_3:12;
            vuint32_t SS_JTAG_FUNC:1;
            vuint32_t unused_2:3;
            vuint32_t SS_FCCU_SOFT:1;
            vuint32_t SS_FCCU_HARD:1;
            vuint32_t unused_1:1;
            vuint32_t SS_SOFT_FUNC:1;
            vuint32_t SS_ST_DONE:1;
            vuint32_t SS_WAKEUP:1;
            vuint32_t unused_0:1;
        } B;
    } FESS;

    vuint8_t ADR_reserved8[704];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:4;
            vuint8_t FRET:4;
        } B;
    } FRET;

    vuint8_t ADR_reserved9[3];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:4;
            vuint8_t DRET:4;
        } B;
    } DRET;

    vuint8_t ADR_reserved10[7];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:1;
            vuint32_t PIT_RTC_0_RST:1;
            vuint32_t unused_1:14;
            vuint32_t SIUL_RST:1;
            vuint32_t unused_0:15;
        } B;
    } PRST0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:25;
            vuint32_t CRC_0_RST:1;
            vuint32_t unused_1:1;
            vuint32_t DMAMUX_0_RST:1;
            vuint32_t unused_0:4;
        } B;
    } PRST1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t LINFLEXD_0_RST:1;
            vuint32_t unused_1:12;
            vuint32_t FLEXCAN_0_RST:1;
            vuint32_t unused_0:15;
        } B;
    } PRST2;

    union {
        vuint32_t R;
        struct {
            vuint32_t ADCSAR_DIG_0_RST:1;
            vuint32_t ADCSAR_SEQ_0_RST:1;
            vuint32_t unused_2:12;
            vuint32_t ADCSAR_SEQ_B_RST:1;
            vuint32_t ADCSAR_DIG_B_RST:1;
            vuint32_t unused_1:12;
            vuint32_t DSPI_0_RST:1;
            vuint32_t DSPI_1_RST:1;
            vuint32_t unused_0:2;
        } B;
    } PRST3;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t ETIMER_2_RST:1;
            vuint32_t ETIMER_3_RST:1;
            vuint32_t ETIMER_0_RST:1;
            vuint32_t ETIMER_1_RST:1;
        } B;
    } PRST4;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:22;
            vuint32_t FCCU_RST:1;
            vuint32_t unused_0:9;
        } B;
    } PRST5;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t LINFLEXD_1_RST:1;
            vuint32_t unused_1:12;
            vuint32_t FLEXCAN_1_RST:1;
            vuint32_t unused_0:15;
        } B;
    } PRST6;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t CTU_RST:1;
            vuint32_t unused_1:16;
            vuint32_t DSPI_2_RST:1;
            vuint32_t unused_0:3;
        } B;
    } PRST7;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:1;
            vuint32_t PIT_RTC_0_STAT:1;
            vuint32_t unused_1:14;
            vuint32_t SIUL_STAT:1;
            vuint32_t unused_0:15;
        } B;
    } PSTAT0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:25;
            vuint32_t CRC_0_STAT:1;
            vuint32_t unused_1:1;
            vuint32_t DMAMUX_0_STAT:1;
            vuint32_t unused_0:4;
        } B;
    } PSTAT1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t LINFLEXD_0_STAT:1;
            vuint32_t unused_1:12;
            vuint32_t FLEXCAN_0_STAT:1;
            vuint32_t unused_0:15;
        } B;
    } PSTAT2;

    union {
        vuint32_t R;
        struct {
            vuint32_t ADCSAR_DIG_0_STAT:1;
            vuint32_t ADCSAR_SEQ_0_STAT:1;
            vuint32_t unused_2:12;
            vuint32_t ADCSAR_SEQ_B_STAT:1;
            vuint32_t ADCSAR_DIG_B_STAT:1;
            vuint32_t unused_1:12;
            vuint32_t DSPI_0_STAT:1;
            vuint32_t DSPI_1_STAT:1;
            vuint32_t unused_0:2;
        } B;
    } PSTAT3;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t ETIMER_2_STAT:1;
            vuint32_t ETIMER_3_STAT:1;
            vuint32_t ETIMER_0_STAT:1;
            vuint32_t ETIMER_1_STAT:1;
        } B;
    } PSTAT4;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:22;
            vuint32_t FCCU_STAT:1;
            vuint32_t unused_0:9;
        } B;
    } PSTAT5;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:3;
            vuint32_t LINFLEXD_1_STAT:1;
            vuint32_t unused_1:12;
            vuint32_t FLEXCAN_1_STAT:1;
            vuint32_t unused_0:15;
        } B;
    } PSTAT6;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t CTU_STAT:1;
            vuint32_t unused_1:16;
            vuint32_t DSPI_2_STAT:1;
            vuint32_t unused_0:3;
        } B;
    } PSTAT7;

};

/**************************************************************************/
/*                 Module: MEMU            */
/**************************************************************************/
struct MEMU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t SWR:1;
            vuint32_t unused_0:15;
        } B;
    } CTRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t PR_CE:1;
            vuint32_t PR_UCE:1;
            vuint32_t PR_CEO:1;
            vuint32_t PR_UCO:1;
            vuint32_t PR_EBO:1;
            vuint32_t unused_1:3;
            vuint32_t F_CE:1;
            vuint32_t F_UCE:1;
            vuint32_t F_CEO:1;
            vuint32_t F_UCO:1;
            vuint32_t F_EBO:1;
            vuint32_t unused_0:3;
            vuint32_t SR_CE:1;
            vuint32_t SR_UCE:1;
            vuint32_t SR_CEO:1;
            vuint32_t SR_UCO:1;
            vuint32_t SR_EBO:1;
        } B;
    } ERR_FLAG;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:11;
            vuint32_t FR_PR_CE:1;
            vuint32_t FR_PR_UCE:1;
            vuint32_t FR_PR_CEO:1;
            vuint32_t FR_PR_UCO:1;
            vuint32_t FR_PR_EBO:1;
            vuint32_t unused_1:3;
            vuint32_t FR_F_CE:1;
            vuint32_t FR_F_UCE:1;
            vuint32_t FR_F_CEO:1;
            vuint32_t FR_F_UCO:1;
            vuint32_t FR_F_EBO:1;
            vuint32_t unused_0:3;
            vuint32_t FR_SR_CE:1;
            vuint32_t FR_SR_UCE:1;
            vuint32_t FR_SR_CEO:1;
            vuint32_t FR_SR_UCO:1;
            vuint32_t FR_SR_EBO:1;
        } B;
    } DEBUG;

    vuint8_t ADR_reserved1[16];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t VLD:1;
                vuint32_t unused_0:23;
                vuint32_t BAD_BIT:8;
            } B;
        } CERR_STS;

        union {
            vuint32_t R;
            struct {
                vuint32_t ERR_ADD:32;
            } B;
        } CERR_ADDR;

    } SYS_RAM[10];

    union {
        vuint32_t R;
        struct {
            vuint32_t VLD:1;
            vuint32_t unused_0:31;
        } B;
    } SYS_RAM_UNCERR_STS;

    union {
        vuint32_t R;
        struct {
            vuint32_t ERR_ADD:32;
        } B;
    } SYS_RAM_UNCERR_ADDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t OFLW:32;
        } B;
    } SYS_RAM_OFLW[1];

    vuint8_t ADR_reserved2[1444];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t VLD:1;
                vuint32_t unused_0:23;
                vuint32_t BAD_BIT:8;
            } B;
        } CERR_STS;

        union {
            vuint32_t R;
            struct {
                vuint32_t ERR_ADD:32;
            } B;
        } CERR_ADDR;

    } PERIPH_RAM[2];

    union {
        vuint32_t R;
        struct {
            vuint32_t VLD:1;
            vuint32_t unused_0:31;
        } B;
    } PERIPH_RAM_UNCERR_STS;

    union {
        vuint32_t R;
        struct {
            vuint32_t ERR_ADD:32;
        } B;
    } PERIPH_RAM_UNCERR_ADDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t OFLW:32;
        } B;
    } PERIPH_RAM_OFLW[1];

    vuint8_t ADR_reserved3[1508];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t VLD:1;
                vuint32_t unused_0:23;
                vuint32_t BAD_BIT:8;
            } B;
        } CERR_STS;

        union {
            vuint32_t R;
            struct {
                vuint32_t ERR_ADD:32;
            } B;
        } CERR_ADDR;

    } FLASH[20];

    union {
        vuint32_t R;
        struct {
            vuint32_t VLD:1;
            vuint32_t unused_0:31;
        } B;
    } FLASH_UNCERR_STS;

    union {
        vuint32_t R;
        struct {
            vuint32_t ERR_ADD:32;
        } B;
    } FLASH_UNCERR_ADDR;

    union {
        vuint32_t R;
        struct {
            vuint32_t OFLW:32;
        } B;
    } FLASH_OFLW[1];

};

/**************************************************************************/
/*                 Module: OSC40M_DIG            */
/**************************************************************************/
struct OSC40M_DIG_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t OSCBYP:1;
            vuint32_t unused_2:7;
            vuint32_t EOCV:8;
            vuint32_t M_OSC:1;
            vuint32_t unused_1:7;
            vuint32_t I_OSC:1;
            vuint32_t unused_0:5;
            vuint32_t S_OSC:1;
            vuint32_t OSCON:1;
        } B;
    } CTL;

};

/**************************************************************************/
/*                 Module: PASS            */
/**************************************************************************/
struct PASS_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t CNS:1;
            vuint32_t JUN:1;
            vuint32_t unused_0:27;
            vuint32_t LIFE:3;
        } B;
    } LCSTAT;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:30;
            vuint32_t GRP:2;
        } B;
    } CHSEL;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t CMST:4;
        } B;
    } CSTAT;

    vuint8_t ADR_reserved2[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t PW32:32;
        } B;
    } CIN[8];

    vuint8_t ADR_reserved3[192];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t TSLOCK:1;
                vuint32_t unused_0:1;
                vuint32_t LOWLOCK:14;
                vuint32_t MIDLOCK:16;
            } B;
        } LOCK0_PG;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:16;
                vuint32_t HIGHLOCK:16;
            } B;
        } LOCK1_PG;

        union {
            vuint32_t R;
            struct {
                vuint32_t L_128LCK:32;
            } B;
        } LOCK2_PG;

        union {
            vuint32_t R;
            struct {
                vuint32_t PGL:1;
                vuint32_t DBL:1;
                vuint32_t MO:1;
                vuint32_t unused_1:1;
                vuint32_t MSTR:4;
                vuint32_t unused_0:3;
                vuint32_t RL4:1;
                vuint32_t RL3:1;
                vuint32_t RL2:1;
                vuint32_t RL1:1;
                vuint32_t RL0:1;
                vuint32_t U_256LCK:16;
            } B;
        } LOCK3_PG;

    } PG[4];

};

/**************************************************************************/
/*                 Module: PBRIDGE            */
/**************************************************************************/
struct PBRIDGE_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t MPROT0:4;
            vuint32_t MPROT1:4;
            vuint32_t MPROT2:4;
            vuint32_t MPROT3:4;
            vuint32_t MPROT4:4;
            vuint32_t MPROT5:4;
            vuint32_t MPROT6:4;
            vuint32_t MPROT7:4;
        } B;
    } MPRA;

    vuint8_t ADR_reserved0[252];

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR0:4;
            vuint32_t PACR1:4;
            vuint32_t PACR2:4;
            vuint32_t PACR3:4;
            vuint32_t PACR4:4;
            vuint32_t PACR5:4;
            vuint32_t PACR6:4;
            vuint32_t PACR7:4;
        } B;
    } PACRA;

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR8:4;
            vuint32_t PACR9:4;
            vuint32_t PACR10:4;
            vuint32_t PACR11:4;
            vuint32_t PACR12:4;
            vuint32_t PACR13:4;
            vuint32_t PACR14:4;
            vuint32_t PACR15:4;
        } B;
    } PACRB;

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR16:4;
            vuint32_t PACR17:4;
            vuint32_t PACR18:4;
            vuint32_t PACR19:4;
            vuint32_t PACR20:4;
            vuint32_t PACR21:4;
            vuint32_t PACR22:4;
            vuint32_t PACR23:4;
        } B;
    } PACRC;

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR24:4;
            vuint32_t PACR25:4;
            vuint32_t PACR26:4;
            vuint32_t PACR27:4;
            vuint32_t PACR28:4;
            vuint32_t PACR29:4;
            vuint32_t PACR30:4;
            vuint32_t PACR31:4;
        } B;
    } PACRD;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR40:4;
            vuint32_t PACR41:4;
            vuint32_t PACR42:4;
            vuint32_t PACR43:4;
            vuint32_t PACR44:4;
            vuint32_t PACR45:4;
            vuint32_t PACR46:4;
            vuint32_t PACR47:4;
        } B;
    } PACRF;

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR48:4;
            vuint32_t PACR49:4;
            vuint32_t PACR50:4;
            vuint32_t PACR51:4;
            vuint32_t PACR52:4;
            vuint32_t PACR53:4;
            vuint32_t PACR54:4;
            vuint32_t PACR55:4;
        } B;
    } PACRG;

    union {
        vuint32_t R;
        struct {
            vuint32_t PACR56:4;
            vuint32_t PACR57:4;
            vuint32_t PACR58:4;
            vuint32_t PACR59:4;
            vuint32_t PACR60:4;
            vuint32_t PACR61:4;
            vuint32_t PACR62:4;
            vuint32_t PACR63:4;
        } B;
    } PACRH;

    vuint8_t ADR_reserved2[32];

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR0:4;
            vuint32_t OPACR1:4;
            vuint32_t OPACR2:4;
            vuint32_t OPACR3:4;
            vuint32_t OPACR4:4;
            vuint32_t OPACR5:4;
            vuint32_t OPACR6:4;
            vuint32_t OPACR7:4;
        } B;
    } OPACRA;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR8:4;
            vuint32_t OPACR9:4;
            vuint32_t OPACR10:4;
            vuint32_t OPACR11:4;
            vuint32_t OPACR12:4;
            vuint32_t OPACR13:4;
            vuint32_t OPACR14:4;
            vuint32_t OPACR15:4;
        } B;
    } OPACRB;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR16:4;
            vuint32_t OPACR17:4;
            vuint32_t OPACR18:4;
            vuint32_t OPACR19:4;
            vuint32_t OPACR20:4;
            vuint32_t OPACR21:4;
            vuint32_t OPACR22:4;
            vuint32_t OPACR23:4;
        } B;
    } OPACRC;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR24:4;
            vuint32_t OPACR25:4;
            vuint32_t OPACR26:4;
            vuint32_t OPACR27:4;
            vuint32_t OPACR28:4;
            vuint32_t OPACR29:4;
            vuint32_t OPACR30:4;
            vuint32_t OPACR31:4;
        } B;
    } OPACRD;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR32:4;
            vuint32_t OPACR33:4;
            vuint32_t OPACR34:4;
            vuint32_t OPACR35:4;
            vuint32_t OPACR36:4;
            vuint32_t OPACR37:4;
            vuint32_t OPACR38:4;
            vuint32_t OPACR39:4;
        } B;
    } OPACRE;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR40:4;
            vuint32_t OPACR41:4;
            vuint32_t OPACR42:4;
            vuint32_t OPACR43:4;
            vuint32_t OPACR44:4;
            vuint32_t OPACR45:4;
            vuint32_t OPACR46:4;
            vuint32_t OPACR47:4;
        } B;
    } OPACRF;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR48:4;
            vuint32_t OPACR49:4;
            vuint32_t OPACR50:4;
            vuint32_t OPACR51:4;
            vuint32_t OPACR52:4;
            vuint32_t OPACR53:4;
            vuint32_t OPACR54:4;
            vuint32_t OPACR55:4;
        } B;
    } OPACRG;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR56:4;
            vuint32_t OPACR57:4;
            vuint32_t OPACR58:4;
            vuint32_t OPACR59:4;
            vuint32_t OPACR60:4;
            vuint32_t OPACR61:4;
            vuint32_t OPACR62:4;
            vuint32_t OPACR63:4;
        } B;
    } OPACRH;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR64:4;
            vuint32_t OPACR65:4;
            vuint32_t OPACR66:4;
            vuint32_t OPACR67:4;
            vuint32_t OPACR68:4;
            vuint32_t OPACR69:4;
            vuint32_t OPACR70:4;
            vuint32_t OPACR71:4;
        } B;
    } OPACRI;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR72:4;
            vuint32_t OPACR73:4;
            vuint32_t OPACR74:4;
            vuint32_t OPACR75:4;
            vuint32_t OPACR76:4;
            vuint32_t OPACR77:4;
            vuint32_t OPACR78:4;
            vuint32_t OPACR79:4;
        } B;
    } OPACRJ;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR80:4;
            vuint32_t OPACR81:4;
            vuint32_t OPACR82:4;
            vuint32_t OPACR83:4;
            vuint32_t OPACR84:4;
            vuint32_t OPACR85:4;
            vuint32_t OPACR86:4;
            vuint32_t OPACR87:4;
        } B;
    } OPACRK;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR88:4;
            vuint32_t OPACR89:4;
            vuint32_t OPACR90:4;
            vuint32_t OPACR91:4;
            vuint32_t OPACR92:4;
            vuint32_t OPACR93:4;
            vuint32_t OPACR94:4;
            vuint32_t OPACR95:4;
        } B;
    } OPACRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR96:4;
            vuint32_t OPACR97:4;
            vuint32_t OPACR98:4;
            vuint32_t OPACR99:4;
            vuint32_t OPACR100:4;
            vuint32_t OPACR101:4;
            vuint32_t OPACR102:4;
            vuint32_t OPACR103:4;
        } B;
    } OPACRM;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR104:4;
            vuint32_t OPACR105:4;
            vuint32_t OPACR106:4;
            vuint32_t OPACR107:4;
            vuint32_t OPACR108:4;
            vuint32_t OPACR109:4;
            vuint32_t OPACR110:4;
            vuint32_t OPACR111:4;
        } B;
    } OPACRN;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR112:4;
            vuint32_t OPACR113:4;
            vuint32_t OPACR114:4;
            vuint32_t OPACR115:4;
            vuint32_t OPACR116:4;
            vuint32_t OPACR117:4;
            vuint32_t OPACR118:4;
            vuint32_t OPACR119:4;
        } B;
    } OPACRO;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR120:4;
            vuint32_t OPACR121:4;
            vuint32_t OPACR122:4;
            vuint32_t OPACR123:4;
            vuint32_t OPACR124:4;
            vuint32_t OPACR125:4;
            vuint32_t OPACR126:4;
            vuint32_t OPACR127:4;
        } B;
    } OPACRP;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR128:4;
            vuint32_t OPACR129:4;
            vuint32_t OPACR130:4;
            vuint32_t OPACR131:4;
            vuint32_t OPACR132:4;
            vuint32_t OPACR133:4;
            vuint32_t OPACR134:4;
            vuint32_t OPACR135:4;
        } B;
    } OPACRQ;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR136:4;
            vuint32_t OPACR137:4;
            vuint32_t OPACR138:4;
            vuint32_t OPACR139:4;
            vuint32_t OPACR140:4;
            vuint32_t OPACR141:4;
            vuint32_t OPACR142:4;
            vuint32_t OPACR143:4;
        } B;
    } OPACRR;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR144:4;
            vuint32_t OPACR145:4;
            vuint32_t OPACR146:4;
            vuint32_t OPACR147:4;
            vuint32_t OPACR148:4;
            vuint32_t OPACR149:4;
            vuint32_t OPACR150:4;
            vuint32_t OPACR151:4;
        } B;
    } OPACRS;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR152:4;
            vuint32_t OPACR153:4;
            vuint32_t OPACR154:4;
            vuint32_t OPACR155:4;
            vuint32_t OPACR156:4;
            vuint32_t OPACR157:4;
            vuint32_t OPACR158:4;
            vuint32_t OPACR159:4;
        } B;
    } OPACRT;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR160:4;
            vuint32_t OPACR161:4;
            vuint32_t OPACR162:4;
            vuint32_t OPACR163:4;
            vuint32_t OPACR164:4;
            vuint32_t OPACR165:4;
            vuint32_t OPACR166:4;
            vuint32_t OPACR167:4;
        } B;
    } OPACRU;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR168:4;
            vuint32_t OPACR169:4;
            vuint32_t OPACR170:4;
            vuint32_t OPACR171:4;
            vuint32_t OPACR172:4;
            vuint32_t OPACR173:4;
            vuint32_t OPACR174:4;
            vuint32_t OPACR175:4;
        } B;
    } OPACRV;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR176:4;
            vuint32_t OPACR177:4;
            vuint32_t OPACR178:4;
            vuint32_t OPACR179:4;
            vuint32_t OPACR180:4;
            vuint32_t OPACR181:4;
            vuint32_t OPACR182:4;
            vuint32_t OPACR183:4;
        } B;
    } OPACRW;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR184:4;
            vuint32_t OPACR185:4;
            vuint32_t OPACR186:4;
            vuint32_t OPACR187:4;
            vuint32_t OPACR188:4;
            vuint32_t OPACR189:4;
            vuint32_t OPACR190:4;
            vuint32_t OPACR191:4;
        } B;
    } OPACRX;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR192:4;
            vuint32_t OPACR193:4;
            vuint32_t OPACR194:4;
            vuint32_t OPACR195:4;
            vuint32_t OPACR196:4;
            vuint32_t OPACR197:4;
            vuint32_t OPACR198:4;
            vuint32_t OPACR199:4;
        } B;
    } OPACRY;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR200:4;
            vuint32_t OPACR201:4;
            vuint32_t OPACR202:4;
            vuint32_t OPACR203:4;
            vuint32_t OPACR204:4;
            vuint32_t OPACR205:4;
            vuint32_t OPACR206:4;
            vuint32_t OPACR207:4;
        } B;
    } OPACRZ;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR208:4;
            vuint32_t OPACR209:4;
            vuint32_t OPACR210:4;
            vuint32_t OPACR211:4;
            vuint32_t OPACR212:4;
            vuint32_t OPACR213:4;
            vuint32_t OPACR214:4;
            vuint32_t OPACR215:4;
        } B;
    } OPACRAA;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR216:4;
            vuint32_t OPACR217:4;
            vuint32_t OPACR218:4;
            vuint32_t OPACR219:4;
            vuint32_t OPACR220:4;
            vuint32_t OPACR221:4;
            vuint32_t OPACR222:4;
            vuint32_t OPACR223:4;
        } B;
    } OPACRAB;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR224:4;
            vuint32_t OPACR225:4;
            vuint32_t OPACR226:4;
            vuint32_t OPACR227:4;
            vuint32_t OPACR228:4;
            vuint32_t OPACR229:4;
            vuint32_t OPACR230:4;
            vuint32_t OPACR231:4;
        } B;
    } OPACRAC;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR232:4;
            vuint32_t OPACR233:4;
            vuint32_t OPACR234:4;
            vuint32_t OPACR235:4;
            vuint32_t OPACR236:4;
            vuint32_t OPACR237:4;
            vuint32_t OPACR238:4;
            vuint32_t OPACR239:4;
        } B;
    } OPACRAD;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR240:4;
            vuint32_t OPACR241:4;
            vuint32_t OPACR242:4;
            vuint32_t OPACR243:4;
            vuint32_t OPACR244:4;
            vuint32_t OPACR245:4;
            vuint32_t OPACR246:4;
            vuint32_t OPACR247:4;
        } B;
    } OPACRAE;

    union {
        vuint32_t R;
        struct {
            vuint32_t OPACR248:4;
            vuint32_t OPACR249:4;
            vuint32_t OPACR250:4;
            vuint32_t OPACR251:4;
            vuint32_t OPACR252:4;
            vuint32_t OPACR253:4;
            vuint32_t OPACR254:4;
            vuint32_t OPACR255:4;
        } B;
    } OPACRAF;

};

/**************************************************************************/
/*                 Module: PFLASH            */
/**************************************************************************/
struct PFLASH_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t P0_M15PFE:1;
            vuint32_t P0_M14PFE:1;
            vuint32_t P0_M13PFE:1;
            vuint32_t P0_M12PFE:1;
            vuint32_t P0_M11PFE:1;
            vuint32_t P0_M10PFE:1;
            vuint32_t P0_M9PFE:1;
            vuint32_t P0_M8PFE:1;
            vuint32_t P0_M7PFE:1;
            vuint32_t P0_M6PFE:1;
            vuint32_t P0_M5PFE:1;
            vuint32_t P0_M4PFE:1;
            vuint32_t P0_M3PFE:1;
            vuint32_t P0_M2PFE:1;
            vuint32_t P0_M1PFE:1;
            vuint32_t P0_M0PFE:1;
            vuint32_t unused_3:3;
            vuint32_t RWSC:5;
            vuint32_t unused_2:1;
            vuint32_t P0_DPFEN:1;
            vuint32_t unused_1:1;
            vuint32_t P0_IPFEN:1;
            vuint32_t unused_0:1;
            vuint32_t P0_PFLIM:2;
            vuint32_t P0_BFEN:1;
        } B;
    } PFCR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t P1_M15PFE:1;
            vuint32_t P1_M14PFE:1;
            vuint32_t P1_M13PFE:1;
            vuint32_t P1_M12PFE:1;
            vuint32_t P1_M11PFE:1;
            vuint32_t P1_M10PFE:1;
            vuint32_t P1_M9PFE:1;
            vuint32_t P1_M8PFE:1;
            vuint32_t P1_M7PFE:1;
            vuint32_t P1_M6PFE:1;
            vuint32_t P1_M5PFE:1;
            vuint32_t P1_M4PFE:1;
            vuint32_t P1_M3PFE:1;
            vuint32_t P1_M2PFE:1;
            vuint32_t P1_M1PFE:1;
            vuint32_t P1_M0PFE:1;
            vuint32_t unused_2:9;
            vuint32_t P1_DPFEN:1;
            vuint32_t unused_1:1;
            vuint32_t P1_IPFEN:1;
            vuint32_t unused_0:1;
            vuint32_t P1_PFLIM:2;
            vuint32_t P1_BFEN:1;
        } B;
    } PFCR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t P0_WCFG:2;
            vuint32_t P1_WCFG:2;
            vuint32_t unused_1:11;
            vuint32_t BAF_DIS:1;
            vuint32_t ARBM:2;
            vuint32_t unused_0:14;
        } B;
    } PFCR3;

    union {
        vuint32_t R;
        struct {
            vuint32_t M0AP:2;
            vuint32_t M1AP:2;
            vuint32_t M2AP:2;
            vuint32_t M3AP:2;
            vuint32_t M4AP:2;
            vuint32_t M5AP:2;
            vuint32_t M6AP:2;
            vuint32_t M7AP:2;
            vuint32_t M8AP:2;
            vuint32_t M9AP:2;
            vuint32_t M10AP:2;
            vuint32_t M11AP:2;
            vuint32_t M12AP:2;
            vuint32_t M13AP:2;
            vuint32_t M14AP:2;
            vuint32_t M15AP:2;
        } B;
    } PFAPR;

};

/**************************************************************************/
/*                 Module: PIT            */
/**************************************************************************/
struct PIT_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:30;
            vuint32_t MDIS:1;
            vuint32_t FRZ:1;
        } B;
    } MCR;

    vuint8_t ADR_reserved0[252];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t TSV:32;
            } B;
        } LDVAL;

        union {
            vuint32_t R;
            struct {
                vuint32_t TVL:32;
            } B;
        } CVAL;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:30;
                vuint32_t TIE:1;
                vuint32_t TEN:1;
            } B;
        } TCTRL;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:31;
                vuint32_t TIF:1;
            } B;
        } TFLG;

    } CH[4];

};

/**************************************************************************/
/*                 Module: PLLDIG            */
/**************************************************************************/
struct PLLDIG_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:22;
            vuint32_t CLKCFG:2;
            vuint32_t EXPDIE:1;
            vuint32_t unused_1:3;
            vuint32_t LOLIE:1;
            vuint32_t unused_0:3;
        } B;
    } PLL0CR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:24;
            vuint32_t EXTPDF:1;
            vuint32_t unused_1:3;
            vuint32_t LOLF:1;
            vuint32_t LOCK:1;
            vuint32_t unused_0:2;
        } B;
    } PLL0SR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_3:1;
            vuint32_t RFDPHI1:4;
            vuint32_t unused_2:5;
            vuint32_t RFDPHI:6;
            vuint32_t unused_1:1;
            vuint32_t PREDIV:3;
            vuint32_t unused_0:5;
            vuint32_t MFD:7;
        } B;
    } PLL0DV;

    vuint8_t ADR_reserved0[20];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:22;
            vuint32_t CLKCFG:2;
            vuint32_t EXPDIE:1;
            vuint32_t unused_1:3;
            vuint32_t LOLIE:1;
            vuint32_t unused_0:3;
        } B;
    } PLL1CR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:24;
            vuint32_t EXTPDF:1;
            vuint32_t unused_1:3;
            vuint32_t LOLF:1;
            vuint32_t LOCK:1;
            vuint32_t unused_0:2;
        } B;
    } PLL1SR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:10;
            vuint32_t RFDPHI:6;
            vuint32_t unused_0:9;
            vuint32_t MFD:7;
        } B;
    } PLL1DV;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:1;
            vuint32_t MODEN:1;
            vuint32_t MODSEL:1;
            vuint32_t MODPRD:13;
            vuint32_t unused_0:1;
            vuint32_t INCSTP:15;
        } B;
    } PLL1FM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:1;
            vuint32_t FDEN:1;
            vuint32_t unused_1:12;
            vuint32_t DTHDIS:2;
            vuint32_t unused_0:4;
            vuint32_t FRCDIV:12;
        } B;
    } PLL1FD;

};

/**************************************************************************/
/*                 Module: PMCDIG            */
/**************************************************************************/
struct PMCDIG_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:7;
            vuint32_t LVD3_C:1;
            vuint32_t unused_0:24;
        } B;
    } EPR_LV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:7;
            vuint32_t REE3_C:1;
            vuint32_t unused_0:24;
        } B;
    } REE_LV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:7;
            vuint32_t RES3_C:1;
            vuint32_t unused_0:24;
        } B;
    } RES_LV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:7;
            vuint32_t VD3IE_C:1;
            vuint32_t unused_0:24;
        } B;
    } IE_LV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:7;
            vuint32_t FEE3_C:1;
            vuint32_t unused_0:24;
        } B;
    } FEE_LV0;

    vuint8_t ADR_reserved0[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t HVD6_C:1;
            vuint32_t unused_0:16;
        } B;
    } EPR_LV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t REE6_C:1;
            vuint32_t unused_0:16;
        } B;
    } REE_LV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t RES6_C:1;
            vuint32_t unused_0:16;
        } B;
    } RES_LV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t HVD6IE_C:1;
            vuint32_t unused_0:16;
        } B;
    } IE_LV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:15;
            vuint32_t FEE6_C:1;
            vuint32_t unused_0:16;
        } B;
    } FEE_LV1;

    vuint8_t ADR_reserved1[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t LVD11_AD:1;
            vuint32_t LVD11_FL:1;
            vuint32_t unused_1:3;
            vuint32_t LVD11_C:1;
            vuint32_t unused_0:24;
        } B;
    } EPR_HV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t REE11_AD:1;
            vuint32_t REE11_FL:1;
            vuint32_t unused_1:3;
            vuint32_t REE11_C:1;
            vuint32_t unused_0:24;
        } B;
    } REE_HV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t RES11_AD:1;
            vuint32_t RES11_FL:1;
            vuint32_t unused_1:3;
            vuint32_t RES11_C:1;
            vuint32_t unused_0:24;
        } B;
    } RES_HV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t LVD11IE_AD:1;
            vuint32_t LVD11IE_FL:1;
            vuint32_t unused_1:3;
            vuint32_t LVD11IE_C:1;
            vuint32_t unused_0:24;
        } B;
    } IE_HV0;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t FEE11_AD:1;
            vuint32_t FEE11_FL:1;
            vuint32_t unused_1:3;
            vuint32_t FEE11_C:1;
            vuint32_t unused_0:24;
        } B;
    } FEE_HV0;

    vuint8_t ADR_reserved2[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:10;
            vuint32_t LVD14_AD:1;
            vuint32_t unused_1:12;
            vuint32_t HVD13_C:1;
            vuint32_t unused_0:8;
        } B;
    } EPR_HV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:10;
            vuint32_t REE14_AD:1;
            vuint32_t unused_1:12;
            vuint32_t REE13_C:1;
            vuint32_t unused_0:8;
        } B;
    } REE_HV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:10;
            vuint32_t RES14_AD:1;
            vuint32_t unused_1:12;
            vuint32_t RES13_C:1;
            vuint32_t unused_0:8;
        } B;
    } RES_HV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:10;
            vuint32_t LVDIE14_AD:1;
            vuint32_t unused_1:12;
            vuint32_t HVDIE13_C:1;
            vuint32_t unused_0:8;
        } B;
    } IE_HV1;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:10;
            vuint32_t FEE14_AD:1;
            vuint32_t unused_1:12;
            vuint32_t FEE13_C:1;
            vuint32_t unused_0:8;
        } B;
    } FEE_HV1;

    vuint8_t ADR_reserved3[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_8:1;
            vuint32_t VD15_C:1;
            vuint32_t VD14_AD:1;
            vuint32_t unused_7:2;
            vuint32_t VD13_C:1;
            vuint32_t unused_6:1;
            vuint32_t VD11_AD:1;
            vuint32_t VD11_FL:1;
            vuint32_t VD11_C:1;
            vuint32_t VD10_FL:1;
            vuint32_t VD10_C:1;
            vuint32_t unused_5:1;
            vuint32_t VD9_C:1;
            vuint32_t unused_4:1;
            vuint32_t VD8_C:1;
            vuint32_t VD7_FL:1;
            vuint32_t VD7_C:1;
            vuint32_t unused_3:1;
            vuint32_t VD6_C:1;
            vuint32_t unused_2:5;
            vuint32_t VD3_C:1;
            vuint32_t VD2_FL:1;
            vuint32_t VD2_C:1;
            vuint32_t unused_1:1;
            vuint32_t VD1_C:1;
            vuint32_t unused_0:1;
            vuint32_t VD0_C:1;
        } B;
    } GR_S;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_7:1;
            vuint32_t VD15_C:1;
            vuint32_t VD14_AD:1;
            vuint32_t unused_6:2;
            vuint32_t VD13_C:1;
            vuint32_t unused_5:1;
            vuint32_t VD11_AD:1;
            vuint32_t VD11_FL:1;
            vuint32_t VD11_C:1;
            vuint32_t VD10_FL:1;
            vuint32_t VD10_C:1;
            vuint32_t unused_4:1;
            vuint32_t VD9_C:1;
            vuint32_t unused_3:1;
            vuint32_t VD8_C:1;
            vuint32_t VD7_FL:1;
            vuint32_t VD7_C:1;
            vuint32_t unused_2:1;
            vuint32_t VD6_C:1;
            vuint32_t unused_1:5;
            vuint32_t VD3_C:1;
            vuint32_t VD2_FL:1;
            vuint32_t VD2_C:1;
            vuint32_t unused_0:1;
            vuint32_t VD1_C:1;
            vuint32_t IRQ_ST:1;
            vuint32_t VD0_C:1;
        } B;
    } GR_P;

    union {
        vuint32_t R;
        struct {
            vuint32_t IE_EN:1;
            vuint32_t unused_6:1;
            vuint32_t VDIE14_AD:1;
            vuint32_t unused_5:2;
            vuint32_t VDIE13_C:1;
            vuint32_t unused_4:1;
            vuint32_t VDIE11_AD:1;
            vuint32_t VDIE11_FL:1;
            vuint32_t VDIE11_C:1;
            vuint32_t unused_3:9;
            vuint32_t VDIE6_C:1;
            vuint32_t unused_2:5;
            vuint32_t VDIE3_C:1;
            vuint32_t unused_1:4;
            vuint32_t IRQ_EN:1;
            vuint32_t unused_0:1;
        } B;
    } IE_G;

    vuint8_t ADR_reserved4[436];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t MREG_ENB:1;
        } B;
    } MREG_CTRL;

    vuint8_t ADR_reserved5[188];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t TEMP_2:1;
            vuint32_t TEMP_1:1;
            vuint32_t TEMP_0:1;
        } B;
    } EPR_TD;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t TEMP_2:1;
            vuint32_t TEMP_1:1;
            vuint32_t TEMP_0:1;
        } B;
    } REE_TD;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t TEMP_2:1;
            vuint32_t TEMP_1:1;
            vuint32_t TEMP_0:1;
        } B;
    } RES_TD;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t TS2IE:1;
            vuint32_t TS1IE:1;
            vuint32_t TS0IE:1;
            vuint32_t unused_0:11;
            vuint32_t MUX_CTRL:1;
            vuint32_t AOUT_EN:1;
        } B;
    } CTL_TD;

    vuint8_t ADR_reserved6[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t FEE_TS2:1;
            vuint32_t FEE_TS1:1;
            vuint32_t FEE_TS0:1;
        } B;
    } FEE_TD;

    vuint8_t ADR_reserved7[140];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t ESR0_CFG:1;
        } B;
    } ESR0_CFG;

    vuint8_t ADR_reserved8[36];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:2;
            vuint32_t FLAGS_P2:14;
            vuint32_t unused_0:2;
            vuint32_t FLAGS_P1:14;
        } B;
    } BIST_FLAGS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_5:11;
            vuint32_t IRQST:1;
            vuint32_t unused_4:3;
            vuint32_t IRQEN:1;
            vuint32_t unused_3:3;
            vuint32_t NCFST:1;
            vuint32_t unused_2:3;
            vuint32_t NCFEN:1;
            vuint32_t unused_1:1;
            vuint32_t STATUS:3;
            vuint32_t unused_0:3;
            vuint32_t START:1;
        } B;
    } BIST_CTRL;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:3;
            vuint32_t TIME_1:13;
            vuint32_t unused_0:3;
            vuint32_t TIME_0:13;
        } B;
    } BIST_TIME10;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:3;
            vuint32_t TIME_3:13;
            vuint32_t unused_0:3;
            vuint32_t TIME_2:13;
        } B;
    } BIST_TIME32;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:3;
            vuint32_t TIME_6:13;
            vuint32_t unused_0:3;
            vuint32_t TIME_5:13;
        } B;
    } BIST_TIME65;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t VD_MON:6;
        } B;
    } BIST_DEBUG;

};

/**************************************************************************/
/*                 Module: PRAM            */
/**************************************************************************/
struct PRAM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:22;
            vuint32_t PRI1:1;
            vuint32_t PRI0:1;
            vuint32_t P1_BO_DIS:1;
            vuint32_t P0_BO_DIS:1;
            vuint32_t unused_0:5;
            vuint32_t FT_DIS:1;
        } B;
    } PRCR1;

};

/**************************************************************************/
/*                 Module: RC16M_DIG            */
/**************************************************************************/
struct RC16M_DIG_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:11;
            vuint32_t USER_TRIM:5;
            vuint32_t unused_0:16;
        } B;
    } CTL;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t RCTRIM:8;
        } B;
    } NT;

};

/**************************************************************************/
/*                 Module: SARADC            */
/**************************************************************************/
struct SARADC_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t OWREN:1;
            vuint32_t WLSIDE:1;
            vuint32_t MODE:1;
            vuint32_t XSTRTEN:1;
            vuint32_t NSTART:1;
            vuint32_t NTRGEN:1;
            vuint32_t NEDGESEL:2;
            vuint32_t JSTART:1;
            vuint32_t JTRGEN:1;
            vuint32_t JEDGESEL:2;
            vuint32_t JTRGSEQ:1;
            vuint32_t unused_3:1;
            vuint32_t CTUEN:1;
            vuint32_t CTU_MODE:1;
            vuint32_t unused_2:4;
            vuint32_t JTRGSEL:4;
            vuint32_t ABORTCHAIN:1;
            vuint32_t ABORT:1;
            vuint32_t unused_1:1;
            vuint32_t FRZ:1;
            vuint32_t unused_0:3;
            vuint32_t PWDN:1;
        } B;
    } MCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_4:4;
            vuint32_t NSTART:1;
            vuint32_t unused_3:3;
            vuint32_t JSTART:1;
            vuint32_t unused_2:4;
            vuint32_t JABORTCHAIN:1;
            vuint32_t unused_1:1;
            vuint32_t CTUSTART:1;
            vuint32_t CHADDR:8;
            vuint32_t unused_0:5;
            vuint32_t ADCSTATUS:3;
        } B;
    } MSR;

    vuint8_t ADR_reserved0[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t CTUTRGERR:1;
            vuint32_t EOCTU:1;
            vuint32_t JEOC:1;
            vuint32_t JECH:1;
            vuint32_t NEOC:1;
            vuint32_t NECH:1;
        } B;
    } ISR;

    union {
        vuint32_t R;
        struct {
            vuint32_t EOC_CH31:1;
            vuint32_t EOC_CH30:1;
            vuint32_t EOC_CH29:1;
            vuint32_t EOC_CH28:1;
            vuint32_t EOC_CH27:1;
            vuint32_t EOC_CH26:1;
            vuint32_t EOC_CH25:1;
            vuint32_t EOC_CH24:1;
            vuint32_t EOC_CH23:1;
            vuint32_t EOC_CH22:1;
            vuint32_t EOC_CH21:1;
            vuint32_t EOC_CH20:1;
            vuint32_t EOC_CH19:1;
            vuint32_t EOC_CH18:1;
            vuint32_t EOC_CH17:1;
            vuint32_t EOC_CH16:1;
            vuint32_t EOC_CH15:1;
            vuint32_t EOC_CH14:1;
            vuint32_t EOC_CH13:1;
            vuint32_t EOC_CH12:1;
            vuint32_t EOC_CH11:1;
            vuint32_t EOC_CH10:1;
            vuint32_t EOC_CH9:1;
            vuint32_t EOC_CH8:1;
            vuint32_t EOC_CH7:1;
            vuint32_t EOC_CH6:1;
            vuint32_t EOC_CH5:1;
            vuint32_t EOC_CH4:1;
            vuint32_t EOC_CH3:1;
            vuint32_t EOC_CH2:1;
            vuint32_t EOC_CH1:1;
            vuint32_t EOC_CH0:1;
        } B;
    } ICIPR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t EOC_CH63:1;
            vuint32_t EOC_CH62:1;
            vuint32_t EOC_CH61:1;
            vuint32_t EOC_CH60:1;
            vuint32_t EOC_CH59:1;
            vuint32_t EOC_CH58:1;
            vuint32_t EOC_CH57:1;
            vuint32_t EOC_CH56:1;
            vuint32_t EOC_CH55:1;
            vuint32_t EOC_CH54:1;
            vuint32_t EOC_CH53:1;
            vuint32_t EOC_CH52:1;
            vuint32_t EOC_CH51:1;
            vuint32_t EOC_CH50:1;
            vuint32_t EOC_CH49:1;
            vuint32_t EOC_CH48:1;
            vuint32_t EOC_CH47:1;
            vuint32_t EOC_CH46:1;
            vuint32_t EOC_CH45:1;
            vuint32_t EOC_CH44:1;
            vuint32_t EOC_CH43:1;
            vuint32_t EOC_CH42:1;
            vuint32_t EOC_CH41:1;
            vuint32_t EOC_CH40:1;
            vuint32_t EOC_CH39:1;
            vuint32_t EOC_CH38:1;
            vuint32_t EOC_CH37:1;
            vuint32_t EOC_CH36:1;
            vuint32_t EOC_CH35:1;
            vuint32_t EOC_CH34:1;
            vuint32_t EOC_CH33:1;
            vuint32_t EOC_CH32:1;
        } B;
    } ICIPR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t EOC_CH95:1;
            vuint32_t EOC_CH94:1;
            vuint32_t EOC_CH93:1;
            vuint32_t EOC_CH92:1;
            vuint32_t EOC_CH91:1;
            vuint32_t EOC_CH90:1;
            vuint32_t EOC_CH89:1;
            vuint32_t EOC_CH88:1;
            vuint32_t EOC_CH87:1;
            vuint32_t EOC_CH86:1;
            vuint32_t EOC_CH85:1;
            vuint32_t EOC_CH84:1;
            vuint32_t EOC_CH83:1;
            vuint32_t EOC_CH82:1;
            vuint32_t EOC_CH81:1;
            vuint32_t EOC_CH80:1;
            vuint32_t EOC_CH79:1;
            vuint32_t EOC_CH78:1;
            vuint32_t EOC_CH77:1;
            vuint32_t EOC_CH76:1;
            vuint32_t EOC_CH75:1;
            vuint32_t EOC_CH74:1;
            vuint32_t EOC_CH73:1;
            vuint32_t EOC_CH72:1;
            vuint32_t EOC_CH71:1;
            vuint32_t EOC_CH70:1;
            vuint32_t EOC_CH69:1;
            vuint32_t EOC_CH68:1;
            vuint32_t EOC_CH67:1;
            vuint32_t EOC_CH66:1;
            vuint32_t EOC_CH65:1;
            vuint32_t EOC_CH64:1;
        } B;
    } ICIPR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t MSKEOCTU:1;
            vuint32_t MSKJEOC:1;
            vuint32_t MSKJECH:1;
            vuint32_t MSKNEOC:1;
            vuint32_t MSKNECH:1;
        } B;
    } IMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t IM_CH:32;
        } B;
    } ICIMR[3];


    union {
        vuint32_t R;
        struct {
            vuint32_t WDG15H:1;
            vuint32_t WDG15L:1;
            vuint32_t WDG14H:1;
            vuint32_t WDG14L:1;
            vuint32_t WDG13H:1;
            vuint32_t WDG13L:1;
            vuint32_t WDG12H:1;
            vuint32_t WDG12L:1;
            vuint32_t WDG11H:1;
            vuint32_t WDG11L:1;
            vuint32_t WDG10H:1;
            vuint32_t WDG10L:1;
            vuint32_t WDG9H:1;
            vuint32_t WDG9L:1;
            vuint32_t WDG8H:1;
            vuint32_t WDG8L:1;
            vuint32_t WDG7H:1;
            vuint32_t WDG7L:1;
            vuint32_t WDG6H:1;
            vuint32_t WDG6L:1;
            vuint32_t WDG5H:1;
            vuint32_t WDG5L:1;
            vuint32_t WDG4H:1;
            vuint32_t WDG4L:1;
            vuint32_t WDG3H:1;
            vuint32_t WDG3L:1;
            vuint32_t WDG2H:1;
            vuint32_t WDG2L:1;
            vuint32_t WDG1H:1;
            vuint32_t WDG1L:1;
            vuint32_t WDG0H:1;
            vuint32_t WDG0L:1;
        } B;
    } WTISR;

    union {
        vuint32_t R;
        struct {
            vuint32_t MSKWDG15H:1;
            vuint32_t MSKWDG15L:1;
            vuint32_t MSKWDG14H:1;
            vuint32_t MSKWDG14L:1;
            vuint32_t MSKWDG13H:1;
            vuint32_t MSKWDG13L:1;
            vuint32_t MSKWDG12H:1;
            vuint32_t MSKWDG12L:1;
            vuint32_t MSKWDG11H:1;
            vuint32_t MSKWDG11L:1;
            vuint32_t MSKWDG10H:1;
            vuint32_t MSKWDG10L:1;
            vuint32_t MSKWDG9H:1;
            vuint32_t MSKWDG9L:1;
            vuint32_t MSKWDG8H:1;
            vuint32_t MSKWDG8L:1;
            vuint32_t MSKWDG7H:1;
            vuint32_t MSKWDG7L:1;
            vuint32_t MSKWDG6H:1;
            vuint32_t MSKWDG6L:1;
            vuint32_t MSKWDG5H:1;
            vuint32_t MSKWDG5L:1;
            vuint32_t MSKWDG4H:1;
            vuint32_t MSKWDG4L:1;
            vuint32_t MSKWDG3H:1;
            vuint32_t MSKWDG3L:1;
            vuint32_t MSKWDG2H:1;
            vuint32_t MSKWDG2L:1;
            vuint32_t MSKWDG1H:1;
            vuint32_t MSKWDG1L:1;
            vuint32_t MSKWDG0H:1;
            vuint32_t MSKWDG0L:1;
        } B;
    } WTIMR;

    vuint8_t ADR_reserved1[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:30;
            vuint32_t DCLR:1;
            vuint32_t DMAEN:1;
        } B;
    } DMAE;

    union {
        vuint32_t R;
        struct {
            vuint32_t DS_CH31:1;
            vuint32_t DS_CH30:1;
            vuint32_t DS_CH29:1;
            vuint32_t DS_CH28:1;
            vuint32_t DS_CH27:1;
            vuint32_t DS_CH26:1;
            vuint32_t DS_CH25:1;
            vuint32_t DS_CH24:1;
            vuint32_t DS_CH23:1;
            vuint32_t DS_CH22:1;
            vuint32_t DS_CH21:1;
            vuint32_t DS_CH20:1;
            vuint32_t DS_CH19:1;
            vuint32_t DS_CH18:1;
            vuint32_t DS_CH17:1;
            vuint32_t DS_CH16:1;
            vuint32_t DS_CH15:1;
            vuint32_t DS_CH14:1;
            vuint32_t DS_CH13:1;
            vuint32_t DS_CH12:1;
            vuint32_t DS_CH11:1;
            vuint32_t DS_CH10:1;
            vuint32_t DS_CH9:1;
            vuint32_t DS_CH8:1;
            vuint32_t DS_CH7:1;
            vuint32_t DS_CH6:1;
            vuint32_t DS_CH5:1;
            vuint32_t DS_CH4:1;
            vuint32_t DS_CH3:1;
            vuint32_t DS_CH2:1;
            vuint32_t DS_CH1:1;
            vuint32_t DS_CH0:1;
        } B;
    } ICDSR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t DS_CH63:1;
            vuint32_t DS_CH62:1;
            vuint32_t DS_CH61:1;
            vuint32_t DS_CH60:1;
            vuint32_t DS_CH59:1;
            vuint32_t DS_CH58:1;
            vuint32_t DS_CH57:1;
            vuint32_t DS_CH56:1;
            vuint32_t DS_CH55:1;
            vuint32_t DS_CH54:1;
            vuint32_t DS_CH53:1;
            vuint32_t DS_CH52:1;
            vuint32_t DS_CH51:1;
            vuint32_t DS_CH50:1;
            vuint32_t DS_CH49:1;
            vuint32_t DS_CH48:1;
            vuint32_t DS_CH47:1;
            vuint32_t DS_CH46:1;
            vuint32_t DS_CH45:1;
            vuint32_t DS_CH44:1;
            vuint32_t DS_CH43:1;
            vuint32_t DS_CH42:1;
            vuint32_t DS_CH41:1;
            vuint32_t DS_CH40:1;
            vuint32_t DS_CH39:1;
            vuint32_t DS_CH38:1;
            vuint32_t DS_CH37:1;
            vuint32_t DS_CH36:1;
            vuint32_t DS_CH35:1;
            vuint32_t DS_CH34:1;
            vuint32_t DS_CH33:1;
            vuint32_t DS_CH32:1;
        } B;
    } ICDSR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t DS_CH95:1;
            vuint32_t DS_CH94:1;
            vuint32_t DS_CH93:1;
            vuint32_t DS_CH92:1;
            vuint32_t DS_CH91:1;
            vuint32_t DS_CH90:1;
            vuint32_t DS_CH89:1;
            vuint32_t DS_CH88:1;
            vuint32_t DS_CH87:1;
            vuint32_t DS_CH86:1;
            vuint32_t DS_CH85:1;
            vuint32_t DS_CH84:1;
            vuint32_t DS_CH83:1;
            vuint32_t DS_CH82:1;
            vuint32_t DS_CH81:1;
            vuint32_t DS_CH80:1;
            vuint32_t DS_CH79:1;
            vuint32_t DS_CH78:1;
            vuint32_t DS_CH77:1;
            vuint32_t DS_CH76:1;
            vuint32_t DS_CH75:1;
            vuint32_t DS_CH74:1;
            vuint32_t DS_CH73:1;
            vuint32_t DS_CH72:1;
            vuint32_t DS_CH71:1;
            vuint32_t DS_CH70:1;
            vuint32_t DS_CH69:1;
            vuint32_t DS_CH68:1;
            vuint32_t DS_CH67:1;
            vuint32_t DS_CH66:1;
            vuint32_t DS_CH65:1;
            vuint32_t DS_CH64:1;
        } B;
    } ICDSR2;

    vuint8_t ADR_reserved2[16];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:4;
            vuint32_t THRH:12;
            vuint32_t unused_0:4;
            vuint32_t THRL:12;
        } B;
    } WTHRHLR[4];

    vuint8_t ADR_reserved3[36];

    union {
        vuint32_t R;
        struct {
            vuint32_t CRES:1;
            vuint32_t unused_0:19;
            vuint32_t PRECHG:4;
            vuint32_t INPSAMP:8;
        } B;
    } CTR[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t NCE_CH:32;
        } B;
    } ICNCMR[3];

    vuint8_t ADR_reserved4[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t JCE_CH:32;
        } B;
    } ICJCMR[3];

    vuint8_t ADR_reserved5[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:24;
            vuint32_t PDED:8;
        } B;
    } PDEDR;

    vuint8_t ADR_reserved6[52];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:4;
            vuint32_t PCE:1;
            vuint32_t unused_1:1;
            vuint32_t CTSEL:2;
            vuint32_t unused_0:3;
            vuint32_t FCERR:1;
            vuint32_t VALID:1;
            vuint32_t OVERW:1;
            vuint32_t RESULT:2;
            vuint32_t CDATA:16;
        } B;
    } ICDR[96];

    vuint8_t ADR_reserved7[48];

    union {
        vuint32_t R;
        struct {
            vuint32_t WSEL_CH7:4;
            vuint32_t WSEL_CH6:4;
            vuint32_t WSEL_CH5:4;
            vuint32_t WSEL_CH4:4;
            vuint32_t WSEL_CH3:4;
            vuint32_t WSEL_CH2:4;
            vuint32_t WSEL_CH1:4;
            vuint32_t WSEL_CH0:4;
        } B;
    } ICWSELR[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t WEN_CH31:1;
            vuint32_t WEN_CH30:1;
            vuint32_t WEN_CH29:1;
            vuint32_t WEN_CH28:1;
            vuint32_t WEN_CH27:1;
            vuint32_t WEN_CH26:1;
            vuint32_t WEN_CH25:1;
            vuint32_t WEN_CH24:1;
            vuint32_t WEN_CH23:1;
            vuint32_t WEN_CH22:1;
            vuint32_t WEN_CH21:1;
            vuint32_t WEN_CH20:1;
            vuint32_t WEN_CH19:1;
            vuint32_t WEN_CH18:1;
            vuint32_t WEN_CH17:1;
            vuint32_t WEN_CH16:1;
            vuint32_t WEN_CH15:1;
            vuint32_t WEN_CH14:1;
            vuint32_t WEN_CH13:1;
            vuint32_t WEN_CH12:1;
            vuint32_t WEN_CH11:1;
            vuint32_t WEN_CH10:1;
            vuint32_t WEN_CH9:1;
            vuint32_t WEN_CH8:1;
            vuint32_t WEN_CH7:1;
            vuint32_t WEN_CH6:1;
            vuint32_t WEN_CH5:1;
            vuint32_t WEN_CH4:1;
            vuint32_t WEN_CH3:1;
            vuint32_t WEN_CH2:1;
            vuint32_t WEN_CH1:1;
            vuint32_t WEN_CH0:1;
        } B;
    } ICWENR[3];

    vuint8_t ADR_reserved8[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t AWOR_CH31:1;
            vuint32_t AWOR_CH30:1;
            vuint32_t AWOR_CH29:1;
            vuint32_t AWOR_CH28:1;
            vuint32_t AWOR_CH27:1;
            vuint32_t AWOR_CH26:1;
            vuint32_t AWOR_CH25:1;
            vuint32_t AWOR_CH24:1;
            vuint32_t AWOR_CH23:1;
            vuint32_t AWOR_CH22:1;
            vuint32_t AWOR_CH21:1;
            vuint32_t AWOR_CH20:1;
            vuint32_t AWOR_CH19:1;
            vuint32_t AWOR_CH18:1;
            vuint32_t AWOR_CH17:1;
            vuint32_t AWOR_CH16:1;
            vuint32_t AWOR_CH15:1;
            vuint32_t AWOR_CH14:1;
            vuint32_t AWOR_CH13:1;
            vuint32_t AWOR_CH12:1;
            vuint32_t AWOR_CH11:1;
            vuint32_t AWOR_CH10:1;
            vuint32_t AWOR_CH9:1;
            vuint32_t AWOR_CH8:1;
            vuint32_t AWOR_CH7:1;
            vuint32_t AWOR_CH6:1;
            vuint32_t AWOR_CH5:1;
            vuint32_t AWOR_CH4:1;
            vuint32_t AWOR_CH3:1;
            vuint32_t AWOR_CH2:1;
            vuint32_t AWOR_CH1:1;
            vuint32_t AWOR_CH0:1;
        } B;
    } ICAWORR[3];

    vuint8_t ADR_reserved9[260];

    union {
        vuint32_t R;
        struct {
            vuint32_t EOC_CH127:1;
            vuint32_t EOC_CH126:1;
            vuint32_t EOC_CH125:1;
            vuint32_t EOC_CH124:1;
            vuint32_t EOC_CH123:1;
            vuint32_t EOC_CH122:1;
            vuint32_t EOC_CH121:1;
            vuint32_t EOC_CH120:1;
            vuint32_t EOC_CH119:1;
            vuint32_t EOC_CH118:1;
            vuint32_t EOC_CH117:1;
            vuint32_t EOC_CH116:1;
            vuint32_t EOC_CH115:1;
            vuint32_t EOC_CH114:1;
            vuint32_t EOC_CH113:1;
            vuint32_t EOC_CH112:1;
            vuint32_t EOC_CH111:1;
            vuint32_t EOC_CH110:1;
            vuint32_t EOC_CH109:1;
            vuint32_t EOC_CH108:1;
            vuint32_t EOC_CH107:1;
            vuint32_t EOC_CH106:1;
            vuint32_t EOC_CH105:1;
            vuint32_t EOC_CH104:1;
            vuint32_t EOC_CH103:1;
            vuint32_t EOC_CH102:1;
            vuint32_t EOC_CH101:1;
            vuint32_t EOC_CH100:1;
            vuint32_t EOC_CH99:1;
            vuint32_t EOC_CH98:1;
            vuint32_t EOC_CH97:1;
            vuint32_t EOC_CH96:1;
        } B;
    } TCIPR;

    union {
        vuint32_t R;
        struct {
            vuint32_t IM_CH127:1;
            vuint32_t IM_CH126:1;
            vuint32_t IM_CH125:1;
            vuint32_t IM_CH124:1;
            vuint32_t IM_CH123:1;
            vuint32_t IM_CH122:1;
            vuint32_t IM_CH121:1;
            vuint32_t IM_CH120:1;
            vuint32_t IM_CH119:1;
            vuint32_t IM_CH118:1;
            vuint32_t IM_CH117:1;
            vuint32_t IM_CH116:1;
            vuint32_t IM_CH115:1;
            vuint32_t IM_CH114:1;
            vuint32_t IM_CH113:1;
            vuint32_t IM_CH112:1;
            vuint32_t IM_CH111:1;
            vuint32_t IM_CH110:1;
            vuint32_t IM_CH109:1;
            vuint32_t IM_CH108:1;
            vuint32_t IM_CH107:1;
            vuint32_t IM_CH106:1;
            vuint32_t IM_CH105:1;
            vuint32_t IM_CH104:1;
            vuint32_t IM_CH103:1;
            vuint32_t IM_CH102:1;
            vuint32_t IM_CH101:1;
            vuint32_t IM_CH100:1;
            vuint32_t IM_CH99:1;
            vuint32_t IM_CH98:1;
            vuint32_t IM_CH97:1;
            vuint32_t IM_CH96:1;
        } B;
    } TCIMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t DS_CH127:1;
            vuint32_t DS_CH126:1;
            vuint32_t DS_CH125:1;
            vuint32_t DS_CH124:1;
            vuint32_t DS_CH123:1;
            vuint32_t DS_CH122:1;
            vuint32_t DS_CH121:1;
            vuint32_t DS_CH120:1;
            vuint32_t DS_CH119:1;
            vuint32_t DS_CH118:1;
            vuint32_t DS_CH117:1;
            vuint32_t DS_CH116:1;
            vuint32_t DS_CH115:1;
            vuint32_t DS_CH114:1;
            vuint32_t DS_CH113:1;
            vuint32_t DS_CH112:1;
            vuint32_t DS_CH111:1;
            vuint32_t DS_CH110:1;
            vuint32_t DS_CH109:1;
            vuint32_t DS_CH108:1;
            vuint32_t DS_CH107:1;
            vuint32_t DS_CH106:1;
            vuint32_t DS_CH105:1;
            vuint32_t DS_CH104:1;
            vuint32_t DS_CH103:1;
            vuint32_t DS_CH102:1;
            vuint32_t DS_CH101:1;
            vuint32_t DS_CH100:1;
            vuint32_t DS_CH99:1;
            vuint32_t DS_CH98:1;
            vuint32_t DS_CH97:1;
            vuint32_t DS_CH96:1;
        } B;
    } TCDSR;

    union {
        vuint32_t R;
        struct {
            vuint32_t NCE_CH127:1;
            vuint32_t NCE_CH126:1;
            vuint32_t NCE_CH125:1;
            vuint32_t NCE_CH124:1;
            vuint32_t NCE_CH123:1;
            vuint32_t NCE_CH122:1;
            vuint32_t NCE_CH121:1;
            vuint32_t NCE_CH120:1;
            vuint32_t NCE_CH119:1;
            vuint32_t NCE_CH118:1;
            vuint32_t NCE_CH117:1;
            vuint32_t NCE_CH116:1;
            vuint32_t NCE_CH115:1;
            vuint32_t NCE_CH114:1;
            vuint32_t NCE_CH113:1;
            vuint32_t NCE_CH112:1;
            vuint32_t NCE_CH111:1;
            vuint32_t NCE_CH110:1;
            vuint32_t NCE_CH109:1;
            vuint32_t NCE_CH108:1;
            vuint32_t NCE_CH107:1;
            vuint32_t NCE_CH106:1;
            vuint32_t NCE_CH105:1;
            vuint32_t NCE_CH104:1;
            vuint32_t NCE_CH103:1;
            vuint32_t NCE_CH102:1;
            vuint32_t NCE_CH101:1;
            vuint32_t NCE_CH100:1;
            vuint32_t NCE_CH99:1;
            vuint32_t NCE_CH98:1;
            vuint32_t NCE_CH97:1;
            vuint32_t NCE_CH96:1;
        } B;
    } TCNCMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t JCE_CH127:1;
            vuint32_t JCE_CH126:1;
            vuint32_t JCE_CH125:1;
            vuint32_t JCE_CH124:1;
            vuint32_t JCE_CH123:1;
            vuint32_t JCE_CH122:1;
            vuint32_t JCE_CH121:1;
            vuint32_t JCE_CH120:1;
            vuint32_t JCE_CH119:1;
            vuint32_t JCE_CH118:1;
            vuint32_t JCE_CH117:1;
            vuint32_t JCE_CH116:1;
            vuint32_t JCE_CH115:1;
            vuint32_t JCE_CH114:1;
            vuint32_t JCE_CH113:1;
            vuint32_t JCE_CH112:1;
            vuint32_t JCE_CH111:1;
            vuint32_t JCE_CH110:1;
            vuint32_t JCE_CH109:1;
            vuint32_t JCE_CH108:1;
            vuint32_t JCE_CH107:1;
            vuint32_t JCE_CH106:1;
            vuint32_t JCE_CH105:1;
            vuint32_t JCE_CH104:1;
            vuint32_t JCE_CH103:1;
            vuint32_t JCE_CH102:1;
            vuint32_t JCE_CH101:1;
            vuint32_t JCE_CH100:1;
            vuint32_t JCE_CH99:1;
            vuint32_t JCE_CH98:1;
            vuint32_t JCE_CH97:1;
            vuint32_t JCE_CH96:1;
        } B;
    } TCJCMR;

    union {
        vuint32_t R;
        struct {
            vuint32_t WSEL_CH103:4;
            vuint32_t WSEL_CH102:4;
            vuint32_t WSEL_CH101:4;
            vuint32_t WSEL_CH100:4;
            vuint32_t WSEL_CH99:4;
            vuint32_t WSEL_CH98:4;
            vuint32_t WSEL_CH97:4;
            vuint32_t WSEL_CH96:4;
        } B;
    } TCWSELR[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t WEN_CH127:1;
            vuint32_t WEN_CH126:1;
            vuint32_t WEN_CH125:1;
            vuint32_t WEN_CH124:1;
            vuint32_t WEN_CH123:1;
            vuint32_t WEN_CH122:1;
            vuint32_t WEN_CH121:1;
            vuint32_t WEN_CH120:1;
            vuint32_t WEN_CH119:1;
            vuint32_t WEN_CH118:1;
            vuint32_t WEN_CH117:1;
            vuint32_t WEN_CH116:1;
            vuint32_t WEN_CH115:1;
            vuint32_t WEN_CH114:1;
            vuint32_t WEN_CH113:1;
            vuint32_t WEN_CH112:1;
            vuint32_t WEN_CH111:1;
            vuint32_t WEN_CH110:1;
            vuint32_t WEN_CH109:1;
            vuint32_t WEN_CH108:1;
            vuint32_t WEN_CH107:1;
            vuint32_t WEN_CH106:1;
            vuint32_t WEN_CH105:1;
            vuint32_t WEN_CH104:1;
            vuint32_t WEN_CH103:1;
            vuint32_t WEN_CH102:1;
            vuint32_t WEN_CH101:1;
            vuint32_t WEN_CH100:1;
            vuint32_t WEN_CH99:1;
            vuint32_t WEN_CH98:1;
            vuint32_t WEN_CH97:1;
            vuint32_t WEN_CH96:1;
        } B;
    } TCWENR;

    union {
        vuint32_t R;
        struct {
            vuint32_t AWOR_CH127:1;
            vuint32_t AWOR_CH126:1;
            vuint32_t AWOR_CH125:1;
            vuint32_t AWOR_CH124:1;
            vuint32_t AWOR_CH123:1;
            vuint32_t AWOR_CH122:1;
            vuint32_t AWOR_CH121:1;
            vuint32_t AWOR_CH120:1;
            vuint32_t AWOR_CH119:1;
            vuint32_t AWOR_CH118:1;
            vuint32_t AWOR_CH117:1;
            vuint32_t AWOR_CH116:1;
            vuint32_t AWOR_CH115:1;
            vuint32_t AWOR_CH114:1;
            vuint32_t AWOR_CH113:1;
            vuint32_t AWOR_CH112:1;
            vuint32_t AWOR_CH111:1;
            vuint32_t AWOR_CH110:1;
            vuint32_t AWOR_CH109:1;
            vuint32_t AWOR_CH108:1;
            vuint32_t AWOR_CH107:1;
            vuint32_t AWOR_CH106:1;
            vuint32_t AWOR_CH105:1;
            vuint32_t AWOR_CH104:1;
            vuint32_t AWOR_CH103:1;
            vuint32_t AWOR_CH102:1;
            vuint32_t AWOR_CH101:1;
            vuint32_t AWOR_CH100:1;
            vuint32_t AWOR_CH99:1;
            vuint32_t AWOR_CH98:1;
            vuint32_t AWOR_CH97:1;
            vuint32_t AWOR_CH96:1;
        } B;
    } TCAWORR;

    vuint8_t ADR_reserved10[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH3:1;
            vuint32_t ICSEL_TCH3:7;
            vuint32_t ESIC_TCH2:1;
            vuint32_t ICSEL_TCH2:7;
            vuint32_t ESIC_TCH1:1;
            vuint32_t ICSEL_TCH1:7;
            vuint32_t ESIC_TCH0:1;
            vuint32_t ICSEL_TCH0:7;
        } B;
    } TCCAPR0;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH7:1;
            vuint32_t ICSEL_TCH7:7;
            vuint32_t ESIC_TCH6:1;
            vuint32_t ICSEL_TCH6:7;
            vuint32_t ESIC_TCH5:1;
            vuint32_t ICSEL_TCH5:7;
            vuint32_t ESIC_TCH4:1;
            vuint32_t ICSEL_TCH4:7;
        } B;
    } TCCAPR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH11:1;
            vuint32_t ICSEL_TCH11:7;
            vuint32_t ESIC_TCH10:1;
            vuint32_t ICSEL_TCH10:7;
            vuint32_t ESIC_TCH9:1;
            vuint32_t ICSEL_TCH9:7;
            vuint32_t ESIC_TCH8:1;
            vuint32_t ICSEL_TCH8:7;
        } B;
    } TCCAPR2;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH15:1;
            vuint32_t ICSEL_TCH15:7;
            vuint32_t ESIC_TCH14:1;
            vuint32_t ICSEL_TCH14:7;
            vuint32_t ESIC_TCH13:1;
            vuint32_t ICSEL_TCH13:7;
            vuint32_t ESIC_TCH12:1;
            vuint32_t ICSEL_TCH12:7;
        } B;
    } TCCAPR3;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH19:1;
            vuint32_t ICSEL_TCH19:7;
            vuint32_t ESIC_TCH18:1;
            vuint32_t ICSEL_TCH18:7;
            vuint32_t ESIC_TCH17:1;
            vuint32_t ICSEL_TCH17:7;
            vuint32_t ESIC_TCH16:1;
            vuint32_t ICSEL_TCH16:7;
        } B;
    } TCCAPR4;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH23:1;
            vuint32_t ICSEL_TCH23:7;
            vuint32_t ESIC_TCH22:1;
            vuint32_t ICSEL_TCH22:7;
            vuint32_t ESIC_TCH21:1;
            vuint32_t ICSEL_TCH21:7;
            vuint32_t ESIC_TCH20:1;
            vuint32_t ICSEL_TCH20:7;
        } B;
    } TCCAPR5;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH27:1;
            vuint32_t ICSEL_TCH27:7;
            vuint32_t ESIC_TCH26:1;
            vuint32_t ICSEL_TCH26:7;
            vuint32_t ESIC_TCH25:1;
            vuint32_t ICSEL_TCH25:7;
            vuint32_t ESIC_TCH24:1;
            vuint32_t ICSEL_TCH24:7;
        } B;
    } TCCAPR6;

    union {
        vuint32_t R;
        struct {
            vuint32_t ESIC_TCH31:1;
            vuint32_t ICSEL_TCH31:7;
            vuint32_t ESIC_TCH30:1;
            vuint32_t ICSEL_TCH30:7;
            vuint32_t ESIC_TCH29:1;
            vuint32_t ICSEL_TCH29:7;
            vuint32_t ESIC_TCH28:1;
            vuint32_t ICSEL_TCH28:7;
        } B;
    } TCCAPR7;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:4;
            vuint32_t PCE:1;
            vuint32_t unused_1:1;
            vuint32_t CTSEL:2;
            vuint32_t unused_0:3;
            vuint32_t FCERR:1;
            vuint32_t VALID:1;
            vuint32_t OVERW:1;
            vuint32_t RESULT:2;
            vuint32_t CDATA:16;
        } B;
    } TCDR[32];

};

/**************************************************************************/
/*                 Module: SIUL2            */
/**************************************************************************/
struct SIUL2_tag {
    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t PARTNUM:16;
            vuint32_t ED:1;
            vuint32_t PKG:5;
            vuint32_t unused_0:2;
            vuint32_t MAJOR_MASK:4;
            vuint32_t MINOR_MASK:4;
        } B;
    } MIDR1;

    union {
        vuint32_t R;
        struct {
            vuint32_t SUPPLIER:1;
            vuint32_t FLASH_SIZE_1:4;
            vuint32_t FLASH_SIZE_2:4;
            vuint32_t unused_1:7;
            vuint32_t FAMILYNUM:8;
            vuint32_t unused_0:8;
        } B;
    } MIDR2;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t EIF5:1;
            vuint32_t EIF4:1;
            vuint32_t EIF3:1;
            vuint32_t EIF2:1;
            vuint32_t EIF1:1;
            vuint32_t EIF0:1;
        } B;
    } DISR0;

    vuint8_t ADR_reserved2[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t EIRE5:1;
            vuint32_t EIRE4:1;
            vuint32_t EIRE3:1;
            vuint32_t EIRE2:1;
            vuint32_t EIRE1:1;
            vuint32_t EIRE0:1;
        } B;
    } DIRER0;

    vuint8_t ADR_reserved3[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t DIRS5:1;
            vuint32_t DIRS4:1;
            vuint32_t DIRS3:1;
            vuint32_t DIRS2:1;
            vuint32_t DIRS1:1;
            vuint32_t DIRS0:1;
        } B;
    } DIRSR0;

    vuint8_t ADR_reserved4[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t IREE5:1;
            vuint32_t IREE4:1;
            vuint32_t IREE3:1;
            vuint32_t IREE2:1;
            vuint32_t IREE1:1;
            vuint32_t IREE0:1;
        } B;
    } IREER0;

    vuint8_t ADR_reserved5[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t IFEE5:1;
            vuint32_t IFEE4:1;
            vuint32_t IFEE3:1;
            vuint32_t IFEE2:1;
            vuint32_t IFEE1:1;
            vuint32_t IFEE0:1;
        } B;
    } IFEER0;

    vuint8_t ADR_reserved6[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:26;
            vuint32_t IFE5:1;
            vuint32_t IFE4:1;
            vuint32_t IFE3:1;
            vuint32_t IFE2:1;
            vuint32_t IFE1:1;
            vuint32_t IFE0:1;
        } B;
    } IFER0;

    vuint8_t ADR_reserved7[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t MAXCNT:4;
        } B;
    } IFMCR[32];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:28;
            vuint32_t IFCP:4;
        } B;
    } IFCPR;

    vuint8_t ADR_reserved8[380];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:1;
            vuint32_t OERC:3;
            vuint32_t unused_1:2;
            vuint32_t ODC:2;
            vuint32_t SMC:1;
            vuint32_t APC:1;
            vuint32_t ILS:2;
            vuint32_t IBE:1;
            vuint32_t HYS:1;
            vuint32_t WPDE:1;
            vuint32_t WPUE:1;
            vuint32_t unused_0:8;
            vuint32_t SSS:8;
        } B;
    } MSCR_IO[512];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t INV:1;
            vuint32_t unused_0:7;
            vuint32_t SSS:8;
        } B;
    } MSCR_MUX[512];
   
    vuint8_t ADR_reserved9[192];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:7;
            vuint8_t PDO:1;
        } B;
    } GPDO[80];

    vuint8_t ADR_reserved10[432];

    union {
        vuint8_t R;
        struct {
            vuint8_t unused_0:7;
            vuint8_t PDI:1;
        } B;
    } GPDI[80];

    vuint8_t ADR_reserved11[432];

    union {
        vuint16_t R;
        struct {
            vuint16_t PPDO:16;
        } B;
    } PGPDO[5];

    vuint8_t ADR_reserved12[54];

    union {
        vuint16_t R;
        struct {
            vuint16_t PPDI:16;
        } B;
    } PGPDI[5];

    vuint8_t ADR_reserved13[54];

    union {
        vuint32_t R;
        struct {
            vuint32_t MASK:16;
            vuint32_t MPPDO:16;
        } B;
    } MPGPDO[5];

};

/**************************************************************************/
/*                 Module: SMPU            */
/**************************************************************************/
struct SMPU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t SPERR:5;
            vuint32_t unused_1:7;
            vuint32_t HRL:4;
            vuint32_t NSP:4;
            vuint32_t NRGD:4;
            vuint32_t unused_0:7;
            vuint32_t VLD:1;
        } B;
    } CESR;

    vuint8_t ADR_reserved0[12];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t EADDR:32;
            } B;
        } EAR;

        union {
            vuint32_t R;
            struct {
                vuint32_t EACD:16;
                vuint32_t EPID:8;
                vuint32_t EMN:4;
                vuint32_t EATTR:3;
                vuint32_t ERW:1;
            } B;
        } EDR;

    } ERROR[5];

    vuint8_t ADR_reserved1[968];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t SRTADDR:32;
            } B;
        } WORD0;

        union {
            vuint32_t R;
            struct {
                vuint32_t ENDADDR:32;
            } B;
        } WORD1;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:21;
                vuint32_t M1SM:2;
                vuint32_t M1UM:3;
                vuint32_t M0PE:1;
                vuint32_t M0SM:2;
                vuint32_t M0UM:3;
            } B;
        } WORD2_FMT0;

        union {
            vuint32_t R;
            struct {
                vuint32_t PID:8;
                vuint32_t PIDMASK:8;
                vuint32_t unused_0:15;
                vuint32_t VLD:1;
            } B;
        } WORD3;

    } RGD[8];

    vuint8_t ADR_reserved2[896];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:21;
            vuint32_t M1SM:2;
            vuint32_t M1UM:3;
            vuint32_t M0PE:1;
            vuint32_t M0SM:2;
            vuint32_t M0UM:3;
        } B;
    } RGDAAC[8];

};

/**************************************************************************/
/*                 Module: SSCM            */
/**************************************************************************/
struct SSCM_tag {
    union {
        vuint16_t R;
        struct {
            vuint16_t unused_3:1;
            vuint16_t CER:1;
            vuint16_t unused_2:2;
            vuint16_t NXEN:1;
            vuint16_t unused_1:3;
            vuint16_t BMODE:3;
            vuint16_t VLE:1;
            vuint16_t unused_0:4;
        } B;
    } STATUS;

    union {
        vuint16_t R;
        struct {
            vuint16_t JPIN:10;
            vuint16_t unused_1:1;
            vuint16_t MREV:4;
            vuint16_t unused_0:1;
        } B;
    } MEMCONFIG;

    vuint8_t ADR_reserved0[2];

    union {
        vuint16_t R;
        struct {
            vuint16_t unused_0:14;
            vuint16_t PAE:1;
            vuint16_t RAE:1;
        } B;
    } ERROR;

    vuint8_t ADR_reserved1[32];

    union {
        vuint32_t R;
        struct {
            vuint32_t SADR:32;
        } B;
    } PSA;

    vuint8_t ADR_reserved2[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t LC:3;
        } B;
    } LCSTAT;

};

/**************************************************************************/
/*                 Module: STCU2            */
/**************************************************************************/
struct STCU2_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:21;
            vuint32_t BYP:1;
            vuint32_t MBPLLEN:1;
            vuint32_t LBPLLEN:1;
            vuint32_t unused_0:7;
            vuint32_t RUN:1;
        } B;
    } RUN;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t SKC:32;
        } B;
    } SKC;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:1;
            vuint32_t PTR:7;
            vuint32_t LB_DELAY:8;
            vuint32_t unused_1:7;
            vuint32_t WRP:1;
            vuint32_t unused_0:2;
            vuint32_t CRCEN:1;
            vuint32_t PMOSEN:1;
            vuint32_t MBU:1;
            vuint32_t CLK_CFG:3;
        } B;
    } CFG;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_2:2;
            vuint32_t PLLODF:6;
            vuint32_t unused_1:5;
            vuint32_t PLLIDF:3;
            vuint32_t unused_0:9;
            vuint32_t PLLLDF:7;
        } B;
    } PLL_CFG;

    union {
        vuint32_t R;
        struct {
            vuint32_t WDGEOC:32;
        } B;
    } WDG;

    vuint8_t ADR_reserved1[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t CRCE:32;
        } B;
    } CRCE;

    union {
        vuint32_t R;
        struct {
            vuint32_t CRCR:32;
        } B;
    } CRCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:22;
            vuint32_t UFSF:1;
            vuint32_t RFSF:1;
            vuint32_t unused_0:3;
            vuint32_t LOCKE:1;
            vuint32_t WDTO:1;
            vuint32_t CRCS:1;
            vuint32_t ENGE:1;
            vuint32_t INVP:1;
        } B;
    } ERR_STAT;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:27;
            vuint32_t LOCKEUFM:1;
            vuint32_t WDTOUFM:1;
            vuint32_t CRCSUFM:1;
            vuint32_t ENGEUFM:1;
            vuint32_t INVPUFM:1;
        } B;
    } ERR_FM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t LBS2:1;
            vuint32_t LBS1:1;
            vuint32_t LBS0:1;
        } B;
    } LBS;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t LBE2:1;
            vuint32_t LBE1:1;
            vuint32_t LBE0:1;
        } B;
    } LBE;

    vuint8_t ADR_reserved2[12];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t LBUFM2:1;
            vuint32_t LBUFM1:1;
            vuint32_t LBUFM0:1;
        } B;
    } LBUFM;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:23;
            vuint32_t MBS8:1;
            vuint32_t MBS7:1;
            vuint32_t MBS6:1;
            vuint32_t MBS5:1;
            vuint32_t MBS4:1;
            vuint32_t MBS3:1;
            vuint32_t MBS2:1;
            vuint32_t MBS1:1;
            vuint32_t MBS0:1;
        } B;
    } MBSL;

    vuint8_t ADR_reserved3[8];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:23;
            vuint32_t MBE8:1;
            vuint32_t MBE7:1;
            vuint32_t MBE6:1;
            vuint32_t MBE5:1;
            vuint32_t MBE4:1;
            vuint32_t MBE3:1;
            vuint32_t MBE2:1;
            vuint32_t MBE1:1;
            vuint32_t MBE0:1;
        } B;
    } MBEL;

    vuint8_t ADR_reserved4[32];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:23;
            vuint32_t MBUFM8:1;
            vuint32_t MBUFM7:1;
            vuint32_t MBUFM6:1;
            vuint32_t MBUFM5:1;
            vuint32_t MBUFM4:1;
            vuint32_t MBUFM3:1;
            vuint32_t MBUFM2:1;
            vuint32_t MBUFM1:1;
            vuint32_t MBUFM0:1;
        } B;
    } MBUFML;

    vuint8_t ADR_reserved5[136];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t CSM:1;
                vuint32_t PTR:7;
                vuint32_t unused_1:4;
                vuint32_t PRPGEN:1;
                vuint32_t SHS:3;
                vuint32_t SCEN_OFF:4;
                vuint32_t SCEN_ON:4;
                vuint32_t unused_0:4;
                vuint32_t PFT:1;
                vuint32_t CWS:3;
            } B;
        } CTRL;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:6;
                vuint32_t PCS:26;
            } B;
        } PCS;

        union {
            vuint32_t R;
            struct {
                vuint32_t PRPG31:1;
                vuint32_t PRPG30:1;
                vuint32_t PRPG29:1;
                vuint32_t PRPG28:1;
                vuint32_t PRPG27:1;
                vuint32_t PRPG26:1;
                vuint32_t PRPG25:1;
                vuint32_t PRPG24:1;
                vuint32_t PRPG23:1;
                vuint32_t PRPG22:1;
                vuint32_t PRPG21:1;
                vuint32_t PRPG20:1;
                vuint32_t PRPG19:1;
                vuint32_t PRPG18:1;
                vuint32_t PRPG17:1;
                vuint32_t PRPG16:1;
                vuint32_t PRPG15:1;
                vuint32_t PRPG14:1;
                vuint32_t PRPG13:1;
                vuint32_t PRPG12:1;
                vuint32_t PRPG11:1;
                vuint32_t PRPG10:1;
                vuint32_t PRPG9:1;
                vuint32_t PRPG8:1;
                vuint32_t PRPG7:1;
                vuint32_t PRPG6:1;
                vuint32_t PRPG5:1;
                vuint32_t PRPG4:1;
                vuint32_t PRPG3:1;
                vuint32_t PRPG2:1;
                vuint32_t PRPG1:1;
                vuint32_t PRPG0:1;
            } B;
        } PRPGL;

        union {
            vuint32_t R;
            struct {
                vuint32_t PRPG63:1;
                vuint32_t PRPG62:1;
                vuint32_t PRPG61:1;
                vuint32_t PRPG60:1;
                vuint32_t PRPG59:1;
                vuint32_t PRPG58:1;
                vuint32_t PRPG57:1;
                vuint32_t PRPG56:1;
                vuint32_t PRPG55:1;
                vuint32_t PRPG54:1;
                vuint32_t PRPG53:1;
                vuint32_t PRPG52:1;
                vuint32_t PRPG51:1;
                vuint32_t PRPG50:1;
                vuint32_t PRPG49:1;
                vuint32_t PRPG48:1;
                vuint32_t PRPG47:1;
                vuint32_t PRPG46:1;
                vuint32_t PRPG45:1;
                vuint32_t PRPG44:1;
                vuint32_t PRPG43:1;
                vuint32_t PRPG42:1;
                vuint32_t PRPG41:1;
                vuint32_t PRPG40:1;
                vuint32_t PRPG39:1;
                vuint32_t PRPG38:1;
                vuint32_t PRPG37:1;
                vuint32_t PRPG36:1;
                vuint32_t PRPG35:1;
                vuint32_t PRPG34:1;
                vuint32_t PRPG33:1;
                vuint32_t PRPG32:1;
            } B;
        } PRPGH;

        union {
            vuint32_t R;
            struct {
                vuint32_t MISRE31:1;
                vuint32_t MISRE30:1;
                vuint32_t MISRE29:1;
                vuint32_t MISRE28:1;
                vuint32_t MISRE27:1;
                vuint32_t MISRE26:1;
                vuint32_t MISRE25:1;
                vuint32_t MISRE24:1;
                vuint32_t MISRE23:1;
                vuint32_t MISRE22:1;
                vuint32_t MISRE21:1;
                vuint32_t MISRE20:1;
                vuint32_t MISRE19:1;
                vuint32_t MISRE18:1;
                vuint32_t MISRE17:1;
                vuint32_t MISRE16:1;
                vuint32_t MISRE15:1;
                vuint32_t MISRE14:1;
                vuint32_t MISRE13:1;
                vuint32_t MISRE12:1;
                vuint32_t MISRE11:1;
                vuint32_t MISRE10:1;
                vuint32_t MISRE9:1;
                vuint32_t MISRE8:1;
                vuint32_t MISRE7:1;
                vuint32_t MISRE6:1;
                vuint32_t MISRE5:1;
                vuint32_t MISRE4:1;
                vuint32_t MISRE3:1;
                vuint32_t MISRE2:1;
                vuint32_t MISRE1:1;
                vuint32_t MISRE0:1;
            } B;
        } MISREL;

        union {
            vuint32_t R;
            struct {
                vuint32_t MISRE63:1;
                vuint32_t MISRE62:1;
                vuint32_t MISRE61:1;
                vuint32_t MISRE60:1;
                vuint32_t MISRE59:1;
                vuint32_t MISRE58:1;
                vuint32_t MISRE57:1;
                vuint32_t MISRE56:1;
                vuint32_t MISRE55:1;
                vuint32_t MISRE54:1;
                vuint32_t MISRE53:1;
                vuint32_t MISRE52:1;
                vuint32_t MISRE51:1;
                vuint32_t MISRE50:1;
                vuint32_t MISRE49:1;
                vuint32_t MISRE48:1;
                vuint32_t MISRE47:1;
                vuint32_t MISRE46:1;
                vuint32_t MISRE45:1;
                vuint32_t MISRE44:1;
                vuint32_t MISRE43:1;
                vuint32_t MISRE42:1;
                vuint32_t MISRE41:1;
                vuint32_t MISRE40:1;
                vuint32_t MISRE39:1;
                vuint32_t MISRE38:1;
                vuint32_t MISRE37:1;
                vuint32_t MISRE36:1;
                vuint32_t MISRE35:1;
                vuint32_t MISRE34:1;
                vuint32_t MISRE33:1;
                vuint32_t MISRE32:1;
            } B;
        } MISREH;

        union {
            vuint32_t R;
            struct {
                vuint32_t MISRR31:1;
                vuint32_t MISRR30:1;
                vuint32_t MISRR29:1;
                vuint32_t MISRR28:1;
                vuint32_t MISRR27:1;
                vuint32_t MISRR26:1;
                vuint32_t MISRR25:1;
                vuint32_t MISRR24:1;
                vuint32_t MISRR23:1;
                vuint32_t MISRR22:1;
                vuint32_t MISRR21:1;
                vuint32_t MISRR20:1;
                vuint32_t MISRR19:1;
                vuint32_t MISRR18:1;
                vuint32_t MISRR17:1;
                vuint32_t MISRR16:1;
                vuint32_t MISRR15:1;
                vuint32_t MISRR14:1;
                vuint32_t MISRR13:1;
                vuint32_t MISRR12:1;
                vuint32_t MISRR11:1;
                vuint32_t MISRR10:1;
                vuint32_t MISRR9:1;
                vuint32_t MISRR8:1;
                vuint32_t MISRR7:1;
                vuint32_t MISRR6:1;
                vuint32_t MISRR5:1;
                vuint32_t MISRR4:1;
                vuint32_t MISRR3:1;
                vuint32_t MISRR2:1;
                vuint32_t MISRR1:1;
                vuint32_t MISRR0:1;
            } B;
        } MISRRL;

        union {
            vuint32_t R;
            struct {
                vuint32_t MISRR63:1;
                vuint32_t MISRR62:1;
                vuint32_t MISRR61:1;
                vuint32_t MISRR60:1;
                vuint32_t MISRR59:1;
                vuint32_t MISRR58:1;
                vuint32_t MISRR57:1;
                vuint32_t MISRR56:1;
                vuint32_t MISRR55:1;
                vuint32_t MISRR54:1;
                vuint32_t MISRR53:1;
                vuint32_t MISRR52:1;
                vuint32_t MISRR51:1;
                vuint32_t MISRR50:1;
                vuint32_t MISRR49:1;
                vuint32_t MISRR48:1;
                vuint32_t MISRR47:1;
                vuint32_t MISRR46:1;
                vuint32_t MISRR45:1;
                vuint32_t MISRR44:1;
                vuint32_t MISRR43:1;
                vuint32_t MISRR42:1;
                vuint32_t MISRR41:1;
                vuint32_t MISRR40:1;
                vuint32_t MISRR39:1;
                vuint32_t MISRR38:1;
                vuint32_t MISRR37:1;
                vuint32_t MISRR36:1;
                vuint32_t MISRR35:1;
                vuint32_t MISRR34:1;
                vuint32_t MISRR33:1;
                vuint32_t MISRR32:1;
            } B;
        } MISRRH;

        vuint8_t STCU2_reserved6[32];
    } LB[3];

    vuint8_t ADR_reserved7[1088];

    union {
        vuint32_t R;
        struct {
            vuint32_t CSM:1;
            vuint32_t PTR:7;
            vuint32_t unused_0:24;
        } B;
    } MB_CTRL[9];

};

/**************************************************************************/
/*                 Module: STM            */
/**************************************************************************/
struct STM_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t unused_1:16;
            vuint32_t CPS:8;
            vuint32_t unused_0:6;
            vuint32_t FRZ:1;
            vuint32_t TEN:1;
        } B;
    } CR;

    union {
        vuint32_t R;
        struct {
            vuint32_t CNT:32;
        } B;
    } CNT;

    vuint8_t ADR_reserved0[8];

    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:31;
                vuint32_t CEN:1;
            } B;
        } CCR;

        union {
            vuint32_t R;
            struct {
                vuint32_t unused_0:31;
                vuint32_t CIF:1;
            } B;
        } CIR;

        union {
            vuint32_t R;
            struct {
                vuint32_t CMP:32;
            } B;
        } CMP;

        vuint8_t STM_reserved1[4];
    } CH[4];

};

/**************************************************************************/
/*                 Module: SWT            */
/**************************************************************************/
struct SWT_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t MAP0:1;
            vuint32_t MAP1:1;
            vuint32_t MAP2:1;
            vuint32_t MAP3:1;
            vuint32_t MAP4:1;
            vuint32_t MAP5:1;
            vuint32_t MAP6:1;
            vuint32_t MAP7:1;
            vuint32_t unused_1:13;
            vuint32_t SMD:2;
            vuint32_t RIA:1;
            vuint32_t WND:1;
            vuint32_t ITR:1;
            vuint32_t HLK:1;
            vuint32_t SLK:1;
            vuint32_t unused_0:1;
            vuint32_t STP:1;
            vuint32_t FRZ:1;
            vuint32_t WEN:1;
        } B;
    } CR;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:31;
            vuint32_t TIF:1;
        } B;
    } IR;

    union {
        vuint32_t R;
        struct {
            vuint32_t WTO:32;
        } B;
    } TO;

    union {
        vuint32_t R;
        struct {
            vuint32_t WST:32;
        } B;
    } WN;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t WSC:16;
        } B;
    } SR;

    union {
        vuint32_t R;
        struct {
            vuint32_t CNT:32;
        } B;
    } CO;

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:16;
            vuint32_t SK:16;
        } B;
    } SK;

};

/**************************************************************************/
/*                 Module: WKPU            */
/**************************************************************************/
struct WKPU_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t NIF0:1;
            vuint32_t NOVF0:1;
            vuint32_t unused_3:6;
            vuint32_t NIF1:1;
            vuint32_t NOVF1:1;
            vuint32_t unused_2:6;
            vuint32_t NIF2:1;
            vuint32_t NOVF2:1;
            vuint32_t unused_1:6;
            vuint32_t RIF:1;
            vuint32_t ROVF:1;
            vuint32_t unused_0:6;
        } B;
    } NSR;

    vuint8_t ADR_reserved0[4];

    union {
        vuint32_t R;
        struct {
            vuint32_t NLOCK0:1;
            vuint32_t NDSS0:2;
            vuint32_t NWRE0:1;
            vuint32_t unused_3:1;
            vuint32_t NREE0:1;
            vuint32_t NFEE0:1;
            vuint32_t NFE0:1;
            vuint32_t NLOCK1:1;
            vuint32_t NDSS1:2;
            vuint32_t NWRE1:1;
            vuint32_t unused_2:1;
            vuint32_t NREE1:1;
            vuint32_t NFEE1:1;
            vuint32_t NFE1:1;
            vuint32_t NLOCK2:1;
            vuint32_t NDSS2:2;
            vuint32_t NWRE2:1;
            vuint32_t unused_1:1;
            vuint32_t NREE2:1;
            vuint32_t NFEE2:1;
            vuint32_t NFE2:1;
            vuint32_t RLOCK:1;
            vuint32_t RDSS:2;
            vuint32_t RWRE:1;
            vuint32_t unused_0:1;
            vuint32_t RREE:1;
            vuint32_t RFEE:1;
            vuint32_t RFE:1;
        } B;
    } NCR;

};

/**************************************************************************/
/*                 Module: XBAR            */
/**************************************************************************/
struct XBAR_tag {
    struct {
        union {
            vuint32_t R;
            struct {
                vuint32_t unused_7:1;
                vuint32_t M7:3;
                vuint32_t unused_6:1;
                vuint32_t M6:3;
                vuint32_t unused_5:1;
                vuint32_t M5:3;
                vuint32_t unused_4:1;
                vuint32_t M4:3;
                vuint32_t unused_3:1;
                vuint32_t M3:3;
                vuint32_t unused_2:1;
                vuint32_t M2:3;
                vuint32_t unused_1:1;
                vuint32_t M1:3;
                vuint32_t unused_0:1;
                vuint32_t M0:3;
            } B;
        } PRS;

        vuint8_t XBAR_reserved0[12];

        union {
            vuint32_t R;
            struct {
                vuint32_t RO:1;
                vuint32_t HRP:1;
                vuint32_t unused_2:20;
                vuint32_t ARB:2;
                vuint32_t unused_1:2;
                vuint32_t PCTL:2;
                vuint32_t unused_0:2;
                vuint32_t PARK:2;
            } B;
        } CRS;

        vuint8_t XBAR_reserved1[236];
    } SLAVE[5];

    vuint8_t ADR_reserved2[768];

    union {
        vuint32_t R;
        struct {
            vuint32_t unused_0:29;
            vuint32_t AULB:3;
        } B;
        vuint8_t unused[252];
    } MGPCR[3];

};

/**************************************************************************/
/*                 Module: XBIC            */
/**************************************************************************/
struct XBIC_tag {
    union {
        vuint32_t R;
        struct {
            vuint32_t SE0:1;
            vuint32_t SE1:1;
            vuint32_t SE2:1;
            vuint32_t SE3:1;
            vuint32_t SE4:1;
            vuint32_t SE5:1;
            vuint32_t SE6:1;
            vuint32_t SE7:1;
            vuint32_t ME0:1;
            vuint32_t ME1:1;
            vuint32_t ME2:1;
            vuint32_t ME3:1;
            vuint32_t ME4:1;
            vuint32_t ME5:1;
            vuint32_t ME6:1;
            vuint32_t ME7:1;
            vuint32_t unused_0:16;
        } B;
    } MCR;

    union {
        vuint32_t R;
        struct {
            vuint32_t EIE:1;
            vuint32_t unused_0:16;
            vuint32_t SLV:3;
            vuint32_t MST:4;
            vuint32_t SYN:8;
        } B;
    } EIR;

    union {
        vuint32_t R;
        struct {
            vuint32_t VLD:1;
            vuint32_t DPSE0:1;
            vuint32_t DPSE1:1;
            vuint32_t DPSE2:1;
            vuint32_t DPSE3:1;
            vuint32_t DPSE4:1;
            vuint32_t unused_1:3;
            vuint32_t DPME0:1;
            vuint32_t DPME1:1;
            vuint32_t DPME2:1;
            vuint32_t unused_0:5;
            vuint32_t SLV:3;
            vuint32_t MST:4;
            vuint32_t SYN:8;
        } B;
    } ESR;

    union {
        vuint32_t R;
        struct {
            vuint32_t ADDR:32;
        } B;
    } EAR;

};


#define CMU_0                            (*(volatile struct CMU_tag *) 0xfffb0200UL)
#define CMU_1                            (*(volatile struct CMU_tag *) 0xfbfb0200UL)
#define CMU_2                            (*(volatile struct CMU_tag *) 0xfbfb0240UL)
#define CMU_3                            (*(volatile struct CMU_tag *) 0xfbfb0280UL)
#define CRC_0                            (*(volatile struct CRC_tag *) 0xfff64000UL)
#define CTU_0                            (*(volatile struct CTU_tag *) 0xffc2c000UL)
#define DMAMUX_0                      (*(volatile struct DMAMUX_tag *) 0xfff6c000UL)
#define DSPI_0                          (*(volatile struct DSPI_tag *) 0xffe70000UL)
#define DSPI_1                          (*(volatile struct DSPI_tag *) 0xffe74000UL)
#define DSPI_2                          (*(volatile struct DSPI_tag *) 0xfbe70000UL)
#define EDMA_0                          (*(volatile struct EDMA_tag *) 0xfc0a0000UL)
#define EIM                              (*(volatile struct EIM_tag *) 0xfc008000UL)
#define ETIMER_0                      (*(volatile struct ETIMER_tag *) 0xffc20000UL)
#define ETIMER_1                      (*(volatile struct ETIMER_tag *) 0xffc24000UL)
#define ETIMER_2                      (*(volatile struct ETIMER_tag *) 0xfbc20000UL)
#define ETIMER_3                      (*(volatile struct ETIMER_tag *) 0xfbc24000UL)
#define FCCU                            (*(volatile struct FCCU_tag *) 0xfbf58000UL)
#define FLASH_0                        (*(volatile struct FLASH_tag *) 0xfffe0000UL)
#define FLEXCAN_0                    (*(volatile struct FLEXCAN_tag *) 0xffec0000UL)
#define FLEXCAN_1                    (*(volatile struct FLEXCAN_tag *) 0xfbec0000UL)
#define INTC_0                          (*(volatile struct INTC_tag *) 0xfc040000UL)
#define JDC                              (*(volatile struct JDC_tag *) 0xfff3c000UL)
#define JTAGM                          (*(volatile struct JTAGM_tag *) 0xfff48000UL)
#define LINFLEXD_0                  (*(volatile struct LINFLEXD_tag *) 0xffe8c000UL)
/* LINFlexD for Master has a different memory map */
#define LINFLEXD_1       (*(volatile struct LINFLEXD_MASTERONLY_tag *) 0xfbe8c000UL)
#define MC_CGM                        (*(volatile struct MC_CGM_tag *) 0xfffb0700UL)
#define MC_ME                          (*(volatile struct MC_ME_tag *) 0xfffb8000UL)
#define MC_PCU                        (*(volatile struct MC_PCU_tag *) 0xfffa0000UL)
#define MC_RGM                        (*(volatile struct MC_RGM_tag *) 0xfffa8000UL)
#define MEMU                            (*(volatile struct MEMU_tag *) 0xfff50000UL)
#define OSC40M_DIG                (*(volatile struct OSC40M_DIG_tag *) 0xfffb0080UL)
#define PASS                            (*(volatile struct PASS_tag *) 0xfffe4000UL)
#define PBRIDGE_0                    (*(volatile struct PBRIDGE_tag *) 0xfc000000UL)
#define PBRIDGE_1                    (*(volatile struct PBRIDGE_tag *) 0xf8000000UL)
#define PFLASH_0                      (*(volatile struct PFLASH_tag *) 0xfc030000UL)
#define PIT_0                            (*(volatile struct PIT_tag *) 0xfff84000UL)
#define PLLDIG                        (*(volatile struct PLLDIG_tag *) 0xfffb0100UL)
#define PMCDIG                        (*(volatile struct PMCDIG_tag *) 0xfffa0400UL)
#define PRAM_0                          (*(volatile struct PRAM_tag *) 0xfc020000UL)
#define RC16M_DIG                  (*(volatile struct RC16M_DIG_tag *) 0xfffb0000UL)
#define SAR_ADC_12BIT_0               (*(volatile struct SARADC_tag *) 0xffe00000UL)
#define SAR_ADC_12BIT_B0              (*(volatile struct SARADC_tag *) 0xffe3c000UL)
#define SIUL2                          (*(volatile struct SIUL2_tag *) 0xfffc0000UL)
#define SMPU_0                          (*(volatile struct SMPU_tag *) 0xfc010000UL)
#define SSCM                            (*(volatile struct SSCM_tag *) 0xffff8000UL)
#define STCU2                          (*(volatile struct STCU2_tag *) 0xfff44000UL)
#define STM_0                            (*(volatile struct STM_tag *) 0xfc068000UL)
#define SWT_0                            (*(volatile struct SWT_tag *) 0xfc058000UL)
#define WKPU                            (*(volatile struct WKPU_tag *) 0xfff98000UL)
#define XBAR_0                          (*(volatile struct XBAR_tag *) 0xfc004000UL)
#define XBIC_0                          (*(volatile struct XBIC_tag *) 0xfc018000UL)



#endif /* _SPC570S_H_ */