// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder.h for the primary calling header

#include "Vadder__pch.h"
#include "Vadder__Syms.h"
#include "Vadder___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__ico(Vadder___024root* vlSelf);
#endif  // VL_DEBUG

void Vadder___024root___eval_triggers__ico(Vadder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_triggers__ico\n"); );
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.setBit(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadder___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vadder___024root___ico_sequent__TOP__0(Vadder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___ico_sequent__TOP__0\n"); );
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adder__DOT__result = (0x1ffU & ((IData)(vlSelfRef.a) 
                                              + (IData)(vlSelfRef.b)));
    vlSelfRef.sum = (0xffU & (IData)(vlSelfRef.adder__DOT__result));
    vlSelfRef.carry = (1U & ((IData)(vlSelfRef.adder__DOT__result) 
                             >> 8U));
    if (vlSymsp->_vm_contextp__->assertOnGet(2, 1)) {
        if (VL_UNLIKELY((((IData)(vlSelfRef.sum) != 
                          (0xffU & (IData)(vlSelfRef.adder__DOT__result)))))) {
            VL_WRITEF_NX("[%0t] %%Error: adder.sv:19: Assertion failed in %Nadder: \342\235\214 Sum mismatch: a=%0x b=%0x sum=%0x expected=%0x\n",0,
                         64,VL_TIME_UNITED_Q(1),-12,
                         vlSymsp->name(),8,(IData)(vlSelfRef.a),
                         8,vlSelfRef.b,8,(IData)(vlSelfRef.sum),
                         8,(0xffU & (IData)(vlSelfRef.adder__DOT__result)));
            VL_STOP_MT("rtl\\adder.sv", 19, "");
        }
    }
    if (vlSymsp->_vm_contextp__->assertOnGet(2, 1)) {
        if (VL_UNLIKELY((((IData)(vlSelfRef.carry) 
                          != (1U & ((IData)(vlSelfRef.adder__DOT__result) 
                                    >> 8U)))))) {
            VL_WRITEF_NX("[%0t] %%Error: adder.sv:22: Assertion failed in %Nadder: \342\235\214 Carry mismatch: a=%0x b=%0x carry=%0b expected=%0b\n",0,
                         64,VL_TIME_UNITED_Q(1),-12,
                         vlSymsp->name(),8,(IData)(vlSelfRef.a),
                         8,vlSelfRef.b,1,(IData)(vlSelfRef.carry),
                         1,(1U & ((IData)(vlSelfRef.adder__DOT__result) 
                                  >> 8U)));
            VL_STOP_MT("rtl\\adder.sv", 22, "");
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vadder___024root___dump_triggers__act(Vadder___024root* vlSelf);
#endif  // VL_DEBUG

void Vadder___024root___eval_triggers__act(Vadder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder___024root___eval_triggers__act\n"); );
    Vadder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadder___024root___dump_triggers__act(vlSelf);
    }
#endif
}
