#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_CONDITION 100
#define MAX_MEDICATIONS 5
#define MAX_MEDICATION_NAME 50

// Union for optional HL7 fields
typedef union {
    char insuranceID[20];
    char emergencyContact[20];
} HL7_Optional;

// Struct for patient information
typedef struct Patient {
    char name[MAX_NAME];
    int age;
    char condition[MAX_CONDITION];
    int priority; // Lower value = higher priority
    int prescriptionNumber;
    char medications[MAX_MEDICATIONS][MAX_MEDICATION_NAME];  // Hasta ilaçlarý
    int medicationPrescriptions[MAX_MEDICATIONS];  // Reçete numaralarý
    HL7_Optional optional;
    struct Patient* next;
} Patient;

// Queue for emergency patients
typedef struct {
    Patient* front;
    Patient* rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Generate prescription number
int generatePrescription() {
    return rand() % 10000 + 1000;  // 1000 ile 10999 arasýnda rastgele sayý üretir
}

// Enqueue patient based on priority
void enqueue(Queue* q, char* name, int age, char* condition, int priority, char medications[][MAX_MEDICATION_NAME], int medicationCount) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Memory allocation failed!\n");
        return;
    }

    strcpy(newPatient->name, name);
    newPatient->age = age;
    strcpy(newPatient->condition, condition);
    newPatient->priority = priority;
    newPatient->prescriptionNumber = generatePrescription();
    newPatient->next = NULL;

    // Ýlaç bilgilerini temizleyip güvenli kopyalama yapalým
    memset(newPatient->medications, 0, sizeof(newPatient->medications));

	int i;
    for (i = 0; i < medicationCount && i < MAX_MEDICATIONS; i++) {
        strncpy(newPatient->medications[i], medications[i], MAX_MEDICATION_NAME - 1);
        newPatient->medications[i][MAX_MEDICATION_NAME - 1] = '\0';  // Sonlandýrýcý karakter ekle
        newPatient->medicationPrescriptions[i] = generatePrescription();
    }

    // Kuyruða ekleme iþlemi (öncelik sýrasýna göre)
    if (q->front == NULL || priority < q->front->priority) {
        newPatient->next = q->front;
        q->front = newPatient;
        if (q->rear == NULL) q->rear = newPatient;
    } else {
        Patient* temp = q->front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newPatient->next = temp->next;
        temp->next = newPatient;
        if (newPatient->next == NULL) q->rear = newPatient;
    }
}

// Dequeue patient (process patient)
void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("No patients in queue!\n");
        return;
    }
    Patient* temp = q->front;
    printf("\nProcessing patient: %s, Age: %d, Condition: %s, Priority: %d, Prescription No: %d\n", 
            temp->name, temp->age, temp->condition, temp->priority, temp->prescriptionNumber);

    // Ýlaç bilgilerini yazdýr
    printf("Medications:\n");
    int i;
    for (i = 0; i < MAX_MEDICATIONS && temp->medications[i][0] != '\0'; i++) {
        printf("- %s (Prescription No: %d)\n", temp->medications[i], temp->medicationPrescriptions[i]);
    }

    q->front = q->front->next;
    free(temp);
    if (q->front == NULL) q->rear = NULL;
}

// Display queue
void displayQueue(Queue* q) {
    if (q->front == NULL) {
        printf("No patients in queue!\n");
        return;
    }
    Patient* temp = q->front;
    while (temp != NULL) {
        printf("\nPatient: %s, Age: %d, Condition: %s, Priority: %d, Prescription No: %d\n", 
                temp->name, temp->age, temp->condition, temp->priority, temp->prescriptionNumber);

        // Ýlaçlarý yazdýr
        printf("Medications:\n");
        int i;
        for (i = 0; i < MAX_MEDICATIONS && temp->medications[i][0] != '\0'; i++) {
            printf("- %s (Prescription No: %d)\n", temp->medications[i], temp->medicationPrescriptions[i]);
        }
        printf("\n");

        temp = temp->next;
    }
}

// Queue temizleme fonksiyonu (bellek sýzýntýsýný önler)
void destroyQueue(Queue* q) {
    while (q->front != NULL) {
        Patient* temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    q->rear = NULL;
}

int main() {
    Queue emergencyQueue;
    initQueue(&emergencyQueue);
    
    // Hasta ilaçlarý listesi
    char meds1[][MAX_MEDICATION_NAME] = {"Painkiller", "Antibiotic", "Vitamin"};
    char meds2[][MAX_MEDICATION_NAME] = {"Aspirin", "Cough Syrup"};
    char meds3[][MAX_MEDICATION_NAME] = {"Antidepressant", "Insulin"};

    // Hastalarý kuyruða ekleme
    enqueue(&emergencyQueue, "Alice", 30, "Fracture", 2, meds1, 3);
    enqueue(&emergencyQueue, "Bob", 45, "Heart Attack", 1, meds2, 2);
    enqueue(&emergencyQueue, "Charlie", 25, "Flu", 3, meds3, 2);

    printf("\n?? **Current Queue:**\n");
    displayQueue(&emergencyQueue);

    printf("\n?? **Processing Patients:**\n");
    dequeue(&emergencyQueue);
    dequeue(&emergencyQueue);

    printf("\n?? **Updated Queue:**\n");
    displayQueue(&emergencyQueue);

    // Kuyruðu temizleyelim
    destroyQueue(&emergencyQueue);

    return 0;
}

