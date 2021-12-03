/*
 * File: main.c
 * Creator: George Ferguson
 * Created: Mon Nov 28 14:11:17 2016
 * Time-stamp: <Tue Jul 17 16:02:29 EDT 2018 ferguson>
 */
#include <stdio.h>
#include <stdlib.h>
#include "Circuit.h"

/**
 * Two AND gates connected to make a 3-input AND circuit.
 */
static Circuit* and3_Circuit() {
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_AndGate();
	Gate* A2 = new_AndGate();
	Gate** gates = new_Gate_array(2);
	gates[0] = A1;
	gates[1] = A2;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 2, gates);
	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, z, Gate_getInput(A2, 1));
	Circuit_connect(circuit, Gate_getOutput(A2), out);
	
	return circuit;
}

static Circuit* A_Circuit()
{
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* A1 = new_AndGate();
	Gate* O1 = new_OrGate();
	Gate* NO1 = new_NORGate();
	Gate** gates = new_Gate_array(3);
	gates[0] = A1;
	gates[1] = O1;
	gates[2] = NO1;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 3, gates);
	Circuit_connect(circuit, x, Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, y, Gate_getInput(NO1, 0));
	Circuit_connect(circuit, z, Gate_getInput(NO1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O1, 0));
	Circuit_connect(circuit, Gate_getOutput(NO1), Gate_getInput(O1, 1));
	Circuit_connect(circuit, Gate_getOutput(O1), out);
	return circuit;
}

static Circuit* B_Circuit()
{
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* I1 = new_Inverter();
	Gate* A1 = new_AndGate();
	Gate* A2 = new_AndGate();
	Gate* O1 = new_OrGate();
	Gate** gates = new_Gate_array(4);
	gates[0] = I1;
	gates[1] = O1;
	gates[2] = A1;
	gates[3] = A2;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 4, gates);
	Circuit_connect(circuit, x, Gate_getInput(I1, 0));
	Circuit_connect(circuit, y, Gate_getInput(O1, 0));
	Circuit_connect(circuit, z, Gate_getInput(O1, 1));
	Circuit_connect(circuit, Gate_getOutput(I1), Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, Gate_getOutput(O1), Gate_getInput(A2, 1));
	Circuit_connect(circuit, Gate_getOutput(A2), out);
	return circuit;
}

static Circuit* C_Circuit()
{
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(1);
	outputs[0] = out;

	Gate* I1 = new_Inverter();
	Gate* I2 = new_Inverter();
	Gate* A1 = new_AndGate();
	Gate* NA1 = new_NANDGate();
	Gate* O1 = new_OrGate();
	Gate** gates = new_Gate_array(5);
	gates[0] = I1;
	gates[1] = I2;
	gates[2] = A1;
	gates[3] = NA1;
	gates[4] = O1;

	Circuit *circuit = new_Circuit(3, inputs, 1, outputs, 5, gates);
	Circuit_connect(circuit, x, Gate_getInput(I1, 0));
	Circuit_connect(circuit, z, Gate_getInput(I2, 0));
	Circuit_connect(circuit, Gate_getOutput(I1), Gate_getInput(A1, 0));
	Circuit_connect(circuit, y, Gate_getInput(A1, 1));
	Circuit_connect(circuit, y, Gate_getInput(NA1, 0));
	Circuit_connect(circuit, Gate_getOutput(I2), Gate_getInput(NA1, 1));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O1, 0));
	Circuit_connect(circuit, Gate_getOutput(NA1), Gate_getInput(O1, 1));
	Circuit_connect(circuit, Gate_getOutput(O1), out);
	return circuit;
}

static Circuit* Adder_Circuit()
{
	Boolean* x = new_Boolean(false);
	Boolean* y = new_Boolean(false);
	Boolean* z = new_Boolean(false);
	Boolean** inputs = new_Boolean_array(3);
	inputs[0] = x;
	inputs[1] = y;
	inputs[2] = z;

	Boolean* out1 = new_Boolean(false);
	Boolean* out2 = new_Boolean(false);
	Boolean** outputs = new_Boolean_array(2);
	outputs[0] = out1;
	outputs[1] = out2;

	Gate* I1 = new_Inverter();
	Gate* I2 = new_Inverter();
	Gate* I3 = new_Inverter();
	Gate* A1 = new_And3Gate();
	Gate* A2 = new_And3Gate();
	Gate* A3 = new_And3Gate();
	Gate* A4 = new_And3Gate();
	Gate* A5 = new_And3Gate();
	Gate* A6 = new_And3Gate();
	Gate* A7 = new_And3Gate();
	Gate* O1 = new_Or4Gate();
	Gate* O2 = new_Or4Gate();
	Gate** gates = new_Gate_array(12);
	gates[0] = I1;
	gates[1] = I2;
	gates[2] = I3;
	gates[3] = A1;
	gates[4] = A2;
	gates[5] = A3;
	gates[6] = A4;
	gates[7] = A5;
	gates[8] = A6;
	gates[9] = A7;
	gates[10] = O1;
	gates[11] = O2;

	Circuit *circuit = new_Circuit(3, inputs, 2, outputs, 12, gates);
	Circuit_connect(circuit, x, Gate_getInput(I1, 0));
	Circuit_connect(circuit, y, Gate_getInput(I2, 0));
	Circuit_connect(circuit, z, Gate_getInput(I3, 0));
	Circuit_connect(circuit, x, Gate_getInput(A4, 0));
	Circuit_connect(circuit, x, Gate_getInput(A5, 0));
	Circuit_connect(circuit, x, Gate_getInput(A6, 2));
	Circuit_connect(circuit, x, Gate_getInput(A7, 0));
	Circuit_connect(circuit, y, Gate_getInput(A2, 1));
	Circuit_connect(circuit, y, Gate_getInput(A3, 1));
	Circuit_connect(circuit, y, Gate_getInput(A6, 1));
	Circuit_connect(circuit, y, Gate_getInput(A7, 1));
	Circuit_connect(circuit, z, Gate_getInput(A7, 2));
	Circuit_connect(circuit, z, Gate_getInput(A5, 2));
	Circuit_connect(circuit, z, Gate_getInput(A3, 2));
	Circuit_connect(circuit, z, Gate_getInput(A1, 2));
	Circuit_connect(circuit, Gate_getOutput(I1), Gate_getInput(A1, 0));
	Circuit_connect(circuit, Gate_getOutput(I1), Gate_getInput(A2, 0));
	Circuit_connect(circuit, Gate_getOutput(I1), Gate_getInput(A3, 0));
	Circuit_connect(circuit, Gate_getOutput(I2), Gate_getInput(A1, 1));
	Circuit_connect(circuit, Gate_getOutput(I2), Gate_getInput(A4, 1));
	Circuit_connect(circuit, Gate_getOutput(I2), Gate_getInput(A5, 1));
	Circuit_connect(circuit, Gate_getOutput(I3), Gate_getInput(A6, 0));
	Circuit_connect(circuit, Gate_getOutput(I3), Gate_getInput(A4, 2));
	Circuit_connect(circuit, Gate_getOutput(I3), Gate_getInput(A2, 2));
	Circuit_connect(circuit, Gate_getOutput(A1), Gate_getInput(O1, 0));
	Circuit_connect(circuit, Gate_getOutput(A2), Gate_getInput(O1, 1));
	Circuit_connect(circuit, Gate_getOutput(A4), Gate_getInput(O1, 2));
	Circuit_connect(circuit, Gate_getOutput(A7), Gate_getInput(O1, 3));
	Circuit_connect(circuit, Gate_getOutput(A3), Gate_getInput(O2, 0));
	Circuit_connect(circuit, Gate_getOutput(A5), Gate_getInput(O2, 1));
	Circuit_connect(circuit, Gate_getOutput(A6), Gate_getInput(O2, 2));
	Circuit_connect(circuit, Gate_getOutput(A7), Gate_getInput(O2, 3));
	Circuit_connect(circuit, Gate_getOutput(O1), out2);
	Circuit_connect(circuit, Gate_getOutput(O2), out1);
	return circuit;
}

static char* b2s(bool b) {
	return b ? "T" : "F";
}

static void test3In1Out(Circuit* circuit, bool in0, bool in1, bool in2) {
	Circuit_setInput(circuit, 0, in0);
	Circuit_setInput(circuit, 1, in1);
	Circuit_setInput(circuit, 2, in2);
	Circuit_update(circuit);
	bool out0 = Circuit_getOutput(circuit, 0);
	printf("%s %s %s -> %s\n", b2s(in0), b2s(in1), b2s(in2), b2s(out0));
}

static void tester(Circuit* circuit, int* array)
{
	bool convert = false;
	int numInputs = circuit->numInputs;
	int numOutputs = circuit->numOutputs;

	for(int i = 0; i < numInputs; i++)
	{
		if(array[i] == 0)
		{
			convert = false;
		}
		else
		{
			convert = true;
		}
		Circuit_setInput(circuit, i, convert);
		printf("%s ", b2s(convert));
	}
	Circuit_update(circuit);
	printf("-> ");

	for(int i = 0; i < numOutputs; i++)
	{
		bool out0 = Circuit_getOutput(circuit, i);
		printf("%s ", b2s(out0));
	}
	printf("\n");
}

int power(int base, int exp)
{
    if(exp < 0)
    {
		return -1;
	}
    int result = 1;
    while(exp)
    {
        if (exp & 1) { result *= base; }
        exp >>= 1;
        base *= base;
    }

    return result;
}

static void testerRF(Circuit* circuit, int* array)
{
	int numInputs = circuit->numInputs;
	bool end = true;

	for(int i = 0; i < numInputs; i++)
	{
		if(array[i] == 0)
		{
			end = false;
		}
	}

	tester(circuit, array);
	if(end)
	{
		return;
	}
	int digit = 0;
	for(int i = 0; i < numInputs; i++)
	{
		if(array[i] == 1)
		{
			digit += power(2, (numInputs - 1) - i);
		}
	}
	digit++;

	int temp[numInputs];
	for(int i = 0; i < numInputs; i++)
	{
		temp[i] = 0;
	}

	for(int i = 0; digit > 0; i++)    
	{    
		temp[i] = digit % 2;    
		digit = digit / 2;    
	}
	
	int j = 0;
	for(int i = numInputs - 1; i >= 0; i--)    
	{    
		array[j] = temp[i];
		j++;
	}

	testerRF(circuit, array);
}

static void testAllPossibilities(Circuit* circuit)
{
	int* arr = (int*)calloc(circuit->numInputs, sizeof(int));

	printf("testing possible inputs...\n");
	testerRF(circuit, arr);
	free(arr);
}

int main(int argc, char **argv) {
	Circuit* circuit = and3_Circuit();
	printf("The and3 circuit (AND of three inputs):\n");
	Circuit_dump(circuit);
	printf("\n");
	printf("Testing: Some input(s) false: should be false\n");
	test3In1Out(circuit, true, true, false);
	printf("Testing: All inputs true: should be true\n");
	test3In1Out(circuit, true, true, true);
	printf("Note: Your program needs to test all possible combinations of input values,\nin order from all false to all true, using a single function.\n");
	Circuit_free(circuit);

	Circuit* circuitA = A_Circuit();
	printf("\n\nThe A circuit (part A):\n");
	Circuit_dump(circuitA);
	printf("\n");
	testAllPossibilities(circuitA);
	Circuit_free(circuitA);

	Circuit* circuitB = B_Circuit();
	printf("\n\nThe B circuit (part B):\n");
	Circuit_dump(circuitB);
	printf("\n");
	testAllPossibilities(circuitB);
	Circuit_free(circuitB);

	Circuit* circuitC = C_Circuit();
	printf("\n\nThe C circuit (part C):\n");
	Circuit_dump(circuitC);
	printf("\n");
	testAllPossibilities(circuitC);
	Circuit_free(circuitC);

	Circuit* circuitAdder = Adder_Circuit();
	printf("\n\nThe One-Bit Adder circuit (extra-credit):\n");
	Circuit_dump(circuitAdder);
	printf("\n");
	testAllPossibilities(circuitAdder);
	Circuit_free(circuitAdder);
}