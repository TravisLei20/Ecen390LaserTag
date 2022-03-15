#include "filter.h"

#define FIR_B_SIZE 81
const static double FIR_COEFFICIENTS[FIR_B_SIZE] = {
    0.00041193,   0.000241516,  2.88473E-05,  -0.00022925,  -0.000529089,
    -0.000853904, -0.001169546, -0.001423878, -0.001550858, -0.0014796,
    -0.00114744,  -0.00051579,  0.000414707,  0.001591916,  0.002906206,
    0.004193108,  0.005245894,  0.005838047,  0.00575389,   0.004824168,
    0.002961988,  0.000194039,  -0.003318251, -0.007272025, -0.011233804,
    -0.014668705, -0.016986657, -0.0176017,   -0.01599874,  -0.01179941,
    -0.00482055,  0.004883893,  0.017002824,  0.030974134,  0.046018011,
    0.061195303,  0.07548579,   0.087878608,  0.09746546,   0.103526572,
    0.1056,       0.103526572,  0.09746546,   0.087878608,  0.07548579,
    0.0611953,    0.046018011,  0.030974134,  0.017002824,  0.004883893,
    -0.00482055,  -0.011799412, -0.015998741, -0.017601744, -0.0169867,
    -0.01466871,  -0.0112338,   -0.00727203,  -0.003318251, 0.000194039,
    0.002961988,  0.004824168,  0.005753893,  0.00583805,   0.005245894,
    0.004193108,  0.002906206,  0.001591916,  0.000414707,  -0.000515793,
    -0.001147438, -0.001479572, -0.0015509,   -0.00142388,  -0.00116955,
    -0.0008539,   -0.000529089, -0.000229246, 2.88473E-05,  0.000241516,
    0.000411929};

#define IIR_A_SIZE 10
const static double IIR_A_COEFFICIENTS[FILTER_FREQUENCY_COUNT][IIR_A_SIZE] = {
    {-5.9637727070164, 19.1253393330782, -40.3414745407442, 61.5374668753688,
     -70.0197179514722, 60.2988142352389, -38.7337928625663, 17.9935332795811,
     -5.49790612248677, 0.903328285337995},
    {-4.63779471190715, 13.5022157494616, -26.1559524052698, 38.5896683307385,
     -43.0389903032528, 37.8129275995373, -25.1135980881139, 12.7031827018881,
     -4.27550833911437, 0.903328285338006},
    {-3.0591317915751, 8.64174896096376, -14.2787902538089, 21.3022682833044,
     -22.1938539720793, 20.8734997911055, -13.7097645206094, 8.13035535779319,
     -2.82016438799006, 0.903328285338003},
    {-1.40717491859968, 5.69041414706976, -5.73747182736765, 11.9580283628689,
     -8.54352805983549, 11.717345583836, -5.50882908769989, 5.35367872860778,
     -1.29725192096557, 0.903328285338003},
    {0.820109061177607, 5.16737565792686, 3.25803509092211, 10.3929037639192,
     4.81017764086693, 10.1837245070925, 3.12820007121269, 4.86159333655721,
     0.756045350831453, 0.903328285338001},
    {2.70808698561545, 7.83190712179957, 12.2016079909807, 18.6515004436816,
     18.7581575680045, 18.276088095999, 11.7153613030189, 7.36843946212535,
     2.49654182845119, 0.903328285338004},
    {4.94798352500759, 14.6916070031776, 29.0824147721011, 43.1798391088693,
     48.4407916446889, 42.3107039623943, 27.9234342477064, 13.822186510471,
     4.56146641606544, 0.903328285338},
    {6.17018933522798, 20.1272258768103, 42.9741933980717, 65.9580453212535,
     75.2304376678666, 64.6304113557399, 41.2615910792441, 18.9361287919505,
     5.68819829151803, 0.903328285337998},
    {7.40929128700724, 26.8579444602901, 61.5787878112022, 98.2582558398873,
     113.594601536963, 96.2804521430261, 59.1247420257764, 25.2685275765242,
     6.83050644807431, 0.903328285338},
    {8.57430557763477, 34.3065847531179, 84.0352904110371, 139.285108440568,
     163.051154181616, 136.481472218958, 80.6862886232997, 32.2763619038721,
     7.90451438162447, 0.903328285337996}};

#define IIR_B_SIZE 11
const static double IIR_B_COEFFICIENTS[FILTER_FREQUENCY_COUNT][IIR_B_SIZE] = {
    {9.09286611481947e-10, 0, -4.54643305740974e-09, 0, 9.09286611481947e-09, 0,
     -9.09286611481947e-09, 0, 4.54643305740974e-09, 0, -9.09286611481947e-10},
    {9.09286611481752e-10, 0, -4.54643305740876e-09, 0, 9.09286611481752e-09, 0,
     -9.09286611481752e-09, 0, 4.54643305740876e-09, 0, -9.09286611481752e-10},
    {9.0928661148192e-10, 0, -4.5464330574096e-09, 0, 9.0928661148192e-09, 0,
     -9.0928661148192e-09, 0, 4.5464330574096e-09, 0, -9.0928661148192e-10},
    {9.09286611481805e-10, 0, -4.54643305740903e-09, 0, 9.09286611481805e-09, 0,
     -9.09286611481805e-09, 0, 4.54643305740903e-09, 0, -9.09286611481805e-10},
    {9.09286611482118e-10, 0, -4.54643305741059e-09, 0, 9.09286611482118e-09, 0,
     -9.09286611482118e-09, 0, 4.54643305741059e-09, 0, -9.09286611482118e-10},
    {9.09286611481798e-10, 0, -4.54643305740899e-09, 0, 9.09286611481798e-09, 0,
     -9.09286611481798e-09, 0, 4.54643305740899e-09, 0, -9.09286611481798e-10},
    {9.09286611481937e-10, 0, -4.54643305740968e-09, 0, 9.09286611481937e-09, 0,
     -9.09286611481937e-09, 0, 4.54643305740968e-09, 0, -9.09286611481937e-10},
    {9.09286611481951e-10, 0, -4.54643305740975e-09, 0, 9.09286611481951e-09, 0,
     -9.09286611481951e-09, 0, 4.54643305740975e-09, 0, -9.09286611481951e-10},
    {9.0928661148191e-10, 0, -4.54643305740955e-09, 0, 9.0928661148191e-09, 0,
     -9.0928661148191e-09, 0, 4.54643305740955e-09, 0, -9.0928661148191e-10},
    {9.09286611482061e-10, 0, -4.5464330574103e-09, 0, 9.09286611482061e-09, 0,
     -9.09286611482061e-09, 0, 4.5464330574103e-09, 0, -9.09286611482061e-10}};

#define QUEUE_INIT_VALUE 0

#define INDEX_ZERO 0

#define IIR_FILTER_COUNT 10

#define X_QUEUE_SIZE 81
#define Y_QUEUE_SIZE 11
#define Z_QUEUE_SIZE 10
#define OUTPUT_QUEUE_SIZE 2000

#define X_QUEUE_NAME "garbage1"
#define Y_QUEUE_NAME "garbage2"
#define Z_QUEUE_NAME "garbage3"
#define OUTPUT_QUEUE_NAME "garbage4"

static queue_t xQueue;
static queue_t yQueue;
static queue_t zQueue[FILTER_FREQUENCY_COUNT];
static queue_t outputQueue[FILTER_FREQUENCY_COUNT];
static double currentPowerValue[FILTER_FREQUENCY_COUNT];
static double prevPower[FILTER_FREQUENCY_COUNT];
static double oldestPower[FILTER_FREQUENCY_COUNT];
static double newestPower[FILTER_FREQUENCY_COUNT];

// Initializes the x queue.
void init_xQueue() {
  queue_init(&(xQueue), X_QUEUE_SIZE, X_QUEUE_NAME);
  // Initializes the x queue with the initial value.
  for (int32_t i = 0; i < X_QUEUE_SIZE; i++) {
    queue_overwritePush(&(xQueue), QUEUE_INIT_VALUE);
  }
}

// Initializes the y queue.
void init_yQueue() {
  queue_init(&(yQueue), Y_QUEUE_SIZE, Y_QUEUE_NAME);
  // Initializes the the y queue with the initial value.
  for (int32_t i = 0; i < Y_QUEUE_SIZE; i++) {
    queue_overwritePush(&(yQueue), QUEUE_INIT_VALUE);
  }
}

// Initializes the z queue.
void init_zQueue() {
  // This initializations the z queue
  for (uint32_t i = 0; i < IIR_FILTER_COUNT; i++) {
    queue_init(&(zQueue[i]), Z_QUEUE_SIZE, Z_QUEUE_NAME);
    // This initializations the z queue with the QUEUE_INIT_VALUE
    for (uint32_t j = 0; j < Z_QUEUE_SIZE; j++) {
      queue_overwritePush(&(zQueue[i]), QUEUE_INIT_VALUE);
    }
  }
}

// Initializes the output queue.
void init_outputQueue() {
  // This initializations the output queue
  for (uint32_t i = 0; i < IIR_FILTER_COUNT; i++) {
    queue_init(&(outputQueue[i]), OUTPUT_QUEUE_SIZE, OUTPUT_QUEUE_NAME);
    // This initializations the outputQueue with the QUEUE_INIT_VALUE
    for (uint32_t j = 0; j < OUTPUT_QUEUE_SIZE; j++) {
      queue_overwritePush(&(outputQueue[i]), QUEUE_INIT_VALUE);
    }
  }
}

// Initializes the power arrays
void filter_initPowers() {
  // This initializes the power arrays
  for (uint32_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    prevPower[i] = QUEUE_INIT_VALUE;
    oldestPower[i] = QUEUE_INIT_VALUE;
    newestPower[i] = QUEUE_INIT_VALUE;
  }
}

// Must call this prior to using any filter functions.
void filter_init() {
  init_xQueue();
  init_yQueue();
  init_zQueue();
  init_outputQueue();
  filter_initPowers();

  for (uint32_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    currentPowerValue[i] = 0;
  }
}

// Use this to copy an input into the input queue of the FIR-filter (xQueue).
void filter_addNewInput(double x) { queue_overwritePush(&(xQueue), x); }

// Fills a queue with the given fillValue. For example,
// if the queue is of size 10, and the fillValue = 1.0,
// after executing this function, the queue will contain 10 values
// all of them 1.0.
void filter_fillQueue(queue_t *q, double fillValue) {
  // This fills the given queue with the given fillValue
  for (uint32_t j = 0; j < queue_size(q); j++) {
    queue_overwritePush(q, fillValue);
  }
}

// Invokes the FIR-filter. Input is contents of xQueue.
// Output is returned and is also pushed on to yQueue.
double filter_firFilter() {
  double result = 0;

  result +=
      FIR_COEFFICIENTS[FIR_B_SIZE - 1] * queue_readElementAt(&(xQueue), 0);

  // this finds the result according to the fir coefficients
  for (uint32_t i = 1; i < FIR_B_SIZE; i++) {
    result += FIR_COEFFICIENTS[FIR_B_SIZE - (i + 1)] *
              queue_readElementAt(&(xQueue), i);
  }

  queue_overwritePush(&(yQueue), result);
  return result;
}

// Use this to invoke a single iir filter. Input comes from yQueue.
// Output is returned and is also pushed onto zQueue[filterNumber].
double filter_iirFilter(uint16_t filterNumber) {
  double result1 = 0;
  double result2 = 0;

  result1 += IIR_A_COEFFICIENTS[filterNumber][IIR_A_SIZE - 1] *
             queue_readElementAt(&(zQueue[filterNumber]), 0);

  // this finds result1 with the IIR_mA_COEFFICIENTS
  for (uint32_t i = 1; i < IIR_A_SIZE; i++) {
    result1 += IIR_A_COEFFICIENTS[filterNumber][IIR_A_SIZE - (i + 1)] *
               queue_readElementAt(&(zQueue[filterNumber]), i);
  }

  result2 += IIR_B_COEFFICIENTS[filterNumber][IIR_B_SIZE - 1] *
             queue_readElementAt(&(yQueue), 0);

  // Finds result2 with IIR B coefficients.
  for (uint32_t i = 1; i < IIR_B_SIZE; i++) {
    result2 += IIR_B_COEFFICIENTS[filterNumber][IIR_B_SIZE - (i + 1)] *
               queue_readElementAt(&(yQueue), i);
  }

  double total = result2 - result1;

  queue_overwritePush(&(zQueue[filterNumber]), total);

  queue_overwritePush(&(outputQueue[filterNumber]), total);

  return total;
}

// Use this to compute the power for values contained in an outputQueue.
// If force == true, then recompute power by using all values in the
// outputQueue. This option is necessary so that you can correctly compute power
// values the first time. After that, you can incrementally compute power values
// by:
// 1. Keeping track of the power computed in a previous run, call this
// prev-power.
// 2. Keeping track of the oldest outputQueue value used in a previous run, call
// this oldest-value.
// 3. Get the newest value from the power queue, call this newest-value.
// 4. Compute new power as: prev-power - (oldest-value * oldest-value) +
// (newest-value * newest-value). Note that this function will probably need an
// array to keep track of these values for each of the 10 output queues.
double filter_computePower(uint16_t filterNumber, bool forceComputeFromScratch,
                           bool debugPrint) {
  double powerResult = 0.0;
  // This checks which method will be used to compute power
  if (forceComputeFromScratch) {
    double square = 0.0;

    // This finds the powerResult the forced way
    for (uint32_t i = 0; i < OUTPUT_QUEUE_SIZE; i++) {
      square = queue_readElementAt(&(outputQueue[filterNumber]), i);
      powerResult += (square * square);
    }
  } else {
    newestPower[filterNumber] = queue_readElementAt(
        &(outputQueue[filterNumber]), OUTPUT_QUEUE_SIZE - 1);

    powerResult = prevPower[filterNumber] -
                  (oldestPower[filterNumber] * oldestPower[filterNumber]) +
                  (newestPower[filterNumber] * newestPower[filterNumber]);

    // printf("NEWEST %f, PREVIOUS %f, OLDEST %f\n", newestPower[filterNumber],
    // prevPower[filterNumber], oldestPower[filterNumber]);
  }

  prevPower[filterNumber] = powerResult;
  currentPowerValue[filterNumber] = powerResult;
  oldestPower[filterNumber] =
      queue_readElementAt(&(outputQueue[filterNumber]), INDEX_ZERO);
  return powerResult;
}

// Returns the last-computed output power value for the IIR filter
// [filterNumber].
double filter_getCurrentPowerValue(uint16_t filterNumber) {
  return currentPowerValue[filterNumber];
}

// Get a copy of the current power values.
// This function copies the already computed values into a previously-declared
// array so that they can be accessed from outside the filter software by the
// detector. Remember that when you pass an array into a C function, changes to
// the array within that function are reflected in the returned array.
void filter_getCurrentPowerValues(double powerValues[]) {
  // powerValues = currentPowerValue;
  for (uint8_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    powerValues[i] = currentPowerValue[i];
  }
}

// Using the previously-computed power values that are current stored in
// currentPowerValue[] array, Copy these values into the normalizedArray[]
// argument and then normalize them by dividing all of the values in
// normalizedArray by the maximum power value contained in currentPowerValue[].
void filter_getNormalizedPowerValues(double normalizedArray[],
                                     uint16_t *indexOfMaxValue) {
  double maxPowerValue = currentPowerValue[0];

  // This finds the maximum power value and the index of it
  for (uint32_t i = 1; i < FILTER_FREQUENCY_COUNT; i++) {
    // This determines if the current index value is larger than the
    // maxPowerValue
    if (currentPowerValue[i] > maxPowerValue) {
      maxPowerValue = currentPowerValue[i];
      *indexOfMaxValue = (currentPowerValue[i]);
    }
  }

  // this normalizes uses current power values
  for (uint32_t i = 0; i < FILTER_FREQUENCY_COUNT; i++) {
    normalizedArray[i] = currentPowerValue[i] / maxPowerValue;
  }
}

// Returns the array of FIR coefficients.
const double *filter_getFirCoefficientArray() { return FIR_COEFFICIENTS; }

// Returns the number of FIR coefficients.
uint32_t filter_getFirCoefficientCount() { return FIR_B_SIZE; }

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirACoefficientArray(uint16_t filterNumber) {
  return (IIR_A_COEFFICIENTS[filterNumber]);
}

// Returns the number of A coefficients.
uint32_t filter_getIirACoefficientCount() { return IIR_A_SIZE; }

// Returns the array of coefficients for a particular filter number.
const double *filter_getIirBCoefficientArray(uint16_t filterNumber) {
  return (IIR_B_COEFFICIENTS[filterNumber]);
}

// Returns the number of B coefficients.
uint32_t filter_getIirBCoefficientCount() { return IIR_B_SIZE; }

// Returns the size of the yQueue.
uint32_t filter_getYQueueSize() { return Y_QUEUE_SIZE; }

// Returns the decimation value.
uint16_t filter_getDecimationValue() { return FILTER_FIR_DECIMATION_FACTOR; }

// Returns the address of xQueue.
queue_t *filter_getXQueue() { return &xQueue; }

// Returns the address of yQueue.
queue_t *filter_getYQueue() { return &yQueue; }

// Returns the address of zQueue for a specific filter number.
queue_t *filter_getZQueue(uint16_t filterNumber) {
  return &(zQueue[filterNumber]);
}

// Returns the address of the IIR output-queue for a specific filter-number.
queue_t *filter_getIirOutputQueue(uint16_t filterNumber) {
  return &(outputQueue[filterNumber]);
}