#include "racer.h"
#include <iostream>

Racer::Racer() {
    // Py_Initialize();
    pModule = PyImport_ImportModule("piracer.vehicles");
    pClass = PyObject_GetAttrString(pModule, "PiRacerStandard");
    pInstance = PyObject_CallObject(pClass, NULL);
}

Racer::~Racer() {
    std::cout << "piracer remove start" << std::endl;
    Py_XDECREF(pInstance);
    Py_XDECREF(pClass);
    Py_XDECREF(pModule);
    std::cout << "piracer remove finish" << std::endl;
    // Py_FinalizeEx();
}

void Racer::set_steering_percent(float steering) {
    PyObject_CallMethod(pInstance, "set_steering_percent", "(f)", steering);
}

void Racer::set_throttle_percent(float throttle) {
    PyObject_CallMethod(pInstance, "set_throttle_percent", "(f)", throttle);
}

double Racer::getBatttery() {
    pVoltage = PyObject_CallMethod(pInstance, "get_battery_voltage", NULL);
    voltage = PyFloat_AsDouble(pVoltage);
    voltage_level = (uint32_t)((voltage/3-3.1)*100/1.1);
    return voltage_level;
}
