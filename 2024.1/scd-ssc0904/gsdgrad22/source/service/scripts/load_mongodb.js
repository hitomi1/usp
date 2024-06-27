db = connect('mongodb://localhost/public-health-care');

function generate_cpf() {
    return Math.floor(10000000000 + Math.random() * 90000000000).toString();
}

patient1_base_cpf = generate_cpf().toString()
patient2_base_cpf = generate_cpf().toString()
patient3_base_cpf = generate_cpf().toString()

let prescriptionPopulation = [
    {
        id: 'deb3332a-7bf5-4f35-8d6d-f967c641d766',
        crm: 123,
        doctor_name: "João",
        patient_cpf: patient1_base_cpf,
        medication_register: '8de55a57-b54b-4409-b720-0607eece846d',
        quantity: 40,
        description: "prescription daorinha pra ficar legau",
        valid: true
    },
    {
        id: '4ed3fab9-cb14-4c8f-89d6-5cdb3b7596d1',
        crm: 321,
        doctor_name: "Maria",
        patient_cpf: patient2_base_cpf,
        medication_register: 'c1ea1d42-6631-490b-b414-6c6ec7995167',
        quantity: 60,
        description: "prescription bacaninha pra ficar legau",
        valid: true
    }
];
  
let patientPopulation = [
    {
        cpf: patient1_base_cpf,
        name: "Márcio Andrade",
        data_nascimento: "15/06/2001",
        convenio: "Convenião S/A",
        region: "Centro"
    },
    {
        cpf: patient2_base_cpf,
        name: "Joana Marta",
        data_nascimento: "10/08/1990",
        convenio: "Conveniwow",
        region: "Jardim"
    }
];
  
let stockPopulation = [
    {
        id: '14a2e45f-43d2-47db-b0a7-f678083789c0',
        region: "Centro",
        medication_register: '8de55a57-b54b-4409-b720-0607eece846d',
        quantity: 100
    },
    {
        id: 'a471c56f-b3ce-4af5-b9e6-9f39082b221b',
        region: "Jardim",
        medication_register: 'c1ea1d42-6631-490b-b414-6c6ec7995167',
        quantity: 40
    },
    {
        id: 'ddddd56f-b3ce-4af5-b9e6-9f39082b221b',
        region: "Botafogo",
        medication_register: 'c1ea1d42-6631-490b-b414-6c6ec7995167',
        quantity: 30
    }
];
  
let medicationPopulation = [
    {
        register: '8de55a57-b54b-4409-b720-0607eece846d',
        name: "Remedinho",
        substance: "cloreto de sódio",
        presentation: "esse medicamento é assim assado desse jeito",
        fabricant: "fabrica mermo",
        ready: "mediante a pedido",
        degree: "Preta"
    },
    {
        register: 'c1ea1d42-6631-490b-b414-6c6ec7995167',
        name: "Remedinho",
        substance: "substancia bacana",
        presentation: "esse medicamento é desse outro jeito aqui",
        fabricant: "fabricantes inc.",
        ready: "pronto",
        degree: "Preta"
    }
];
  
let deliveryPopulation = [
    {
        id: crypto.randomUUID(),
        type: "PATIENT",
        patient_cpf: patient2_base_cpf,
        prescription_id: '4ed3fab9-cb14-4c8f-89d6-5cdb3b7596d1',
        region_origin: 'jardim luft',
        region_destiny: null,
        stock_base: '14a2e45f-43d2-47db-b0a7-f678083789c0',
        stock_destiny: null,
        quantity: 40
    }
];
  
let prescriptionIndex = {id: 1};
let patientIndex = {cpf: 1};
let stockIndex = {id: 1};
let medicationIndex = {register: 1};
let deliveryIndex = {id: 1};

let collInfoObjs = [ 
    {coll: "prescription", data: prescriptionPopulation, index: prescriptionIndex}, 
    {coll: "patient", data: patientPopulation, index: patientIndex},
    {coll: "stock", data: stockPopulation, index: stockIndex},
    {coll: "medication", data: medicationPopulation, index: medicationIndex},
    {coll: "delivery", data: deliveryPopulation, index: deliveryIndex}
];

for (obj of collInfoObjs) {
    db[obj.coll].insertMany(obj.data);
    db[obj.coll].createIndex(obj.index, {unique: true});
}
