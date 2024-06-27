from decimal import Decimal
import pymongo
from faker import Faker
from bson.objectid import ObjectId
import random
from datetime import datetime, timedelta
import os
from dotenv import load_dotenv 

# Initialize Faker
fake = Faker()

# loading variables from .env file
load_dotenv() 
uri = os.getenv("MONGO_URI")

# Connect to MongoDB
client = pymongo.MongoClient(uri)
db = client["teste"]
collection = db["teste"]

# Function to generate random data based on the given JSON structure
def generate_random_data():
    data = {
        "_id": str(ObjectId()),
        "user": {
            "phone": {
                "areaCode": "11",
                "number": fake.msisdn(),
                "countryCode": "55"
            },
            "_id": fake.uuid4(),
            "email": fake.email(),
            "name": fake.name(),
            "birthdate": fake.date_of_birth().isoformat(),
            "gender": random.choice(["f", "m"]),
            "active": random.choice([True, False]),
            "working": random.choice([True, False]),
            "firebaseUID": fake.uuid4(),
            "address": [
                {
                    "location": {
                        "coordinates": [fake.longitude(), fake.latitude()],
                        "type": "Point"
                    },
                    "geoPosition": [fake.longitude(), fake.latitude()],
                    "areaId": str(ObjectId()),
                    "city": "São Paulo",
                    "complement": "103a",
                    "lat": fake.latitude(),
                    "lng": fake.longitude(),
                    "neighbor": "Sítio do Mandaqui",
                    "place": "Rua Epaminondas Melo do Amaral",
                    "streetNumber": str(fake.building_number()),
                    "typeAddress": 1,
                    "uf": "SP",
                    "zipCode": fake.zipcode(),
                    "geoposition": [fake.longitude(), fake.latitude()],
                    "timeZone": "America/Sao_Paulo",
                    "_id": str(ObjectId()),
                    "landmark": [
                        {
                            "_id": str(ObjectId()),
                            "name": fake.street_address(),
                            "type": "transit_station",
                            "location": {
                                "lat": fake.latitude(),
                                "lng": fake.longitude()
                            }
                        },
                        {
                            "_id": str(ObjectId()),
                            "name": fake.city(),
                            "type": "subway_station",
                            "location": {
                                "lat": fake.latitude(),
                                "lng": fake.longitude()
                            }
                        }
                    ],
                    "createdAt": fake.date_time().isoformat()
                }
            ],
            "numberOfSchedules": random.randint(1, 100),
            "creditCards": [
                {
                    "holder": {
                        "taxDocument": {
                            "number": fake.ssn(),
                            "type": "CPF"
                        },
                        "fullname": fake.name()
                    },
                    "brand": "MASTERCARD",
                    "first6": fake.credit_card_number()[:6],
                    "id": fake.uuid4(),
                    "last4": fake.credit_card_number()[-4:]
                }
            ],
            "voucherCode": fake.uuid4(),
            "singuCredits": random.randint(0, 100),
            "preuser": random.choice([True, False]),
            "vip": random.choice([True, False]),
            "buildVersion": str(random.randint(1000000000, 9999999999)),
            "userAgent": fake.user_agent(),
            "hasSignature": random.choice([True, False]),
            "fcmToken": fake.uuid4(),
            "appForwardedFor": fake.ipv4(),
            "cpf": fake.ssn(),
            "appVersion": "6.11.4",
            "smsValidation": {
                "code": random.randint(10000, 99999),
                "expiration": (datetime.now() + timedelta(days=random.randint(1, 365))).isoformat()
            },
            "phoneValidated": random.choice([True, False]),
            "professionalPreferences": [str(ObjectId())],
            "excludedPartners": [str(ObjectId())],
            "termsAndConditions": {
                "dateAccepted": fake.date_time().isoformat(),
                "accepted": random.choice([True, False])
            }
        },
        "beginCheckout": fake.date_time().isoformat(),
        "useSinguCredits": random.choice([True, False]),
        "numberOfClients": random.randint(1, 10),
        "partner": {
            "_id": str(ObjectId()),
            "name": fake.name(),
            "phone": {
                "countryCode": "+55",
                "areaCode": "11",
                "number": fake.msisdn()
            },
            "gender": random.choice(["F", "M"]),
            "email": fake.email(),
            "firebaseUID": fake.uuid4(),
            "fcmToken": fake.uuid4(),
            "priority": {
                "vip": random.choice([True, False]),
                "completedSchedules": random.randint(0, 300),
                "ratingCountIn30Days": random.randint(0, 100),
                "averageRatingIn30Days": random.uniform(0, 5),
                "countRejected": random.randint(0, 10),
                "after21daysOnSystem": random.choice([True, False]),
                "rejectionPercent": random.uniform(0, 100),
                "ratingCount": random.randint(0, 500),
                "updatedAt": fake.date_time().isoformat()
            },
            "smartMEI": random.choice([True, False]),
            "singuPayment": random.choice([True, False]),
            "moipCredentials": {
                "accessToken": fake.uuid4(),
                "access_token": fake.uuid4(),
                "scope": "create_orders view_orders create_payments view_payments",
                "moipAccountId": fake.uuid4()
            },
            "document": {
                "documentType": "RG",
                "documentNumber": fake.ssn()
            },
            "pushTokens": None,
            "profilePicture": fake.image_url(),
            "bbnk": random.choice([True, False]),
            "journeyUID": random.randint(1000000, 9999999),
            "beginner": random.choice([True, False]),
            "novice": random.choice([True, False]),
            "code": fake.uuid4(),
            "naturaConsultant": {}
        },
        "date": fake.date_time().isoformat(),
        "area": {
            "_id": str(ObjectId()),
            "name": {
                "en-US": "São Paulo - SP",
                "pt-BR": "São Paulo - SP",
                "en-BR": "São Paulo - SP"
            },
            "country": "Brazil",
            "city": "Sao Paulo",
            "state": "Sao Paulo",
            "tz": "America/Sao_Paulo"
        },
        "services": [
            {
                "_id": fake.uuid4(),
                "minValue": random.randint(50, 100),
                "active": random.choice([True, False]),
                "duration": random.randint(60, 120),
                "name": {
                    "pt-BR": "Pés e Mãos",
                    "en-BR": "Pés e Mãos",
                    "en-US": "Pés e Mãos"
                },
                "description": {
                    "en-US": fake.text(),
                    "pt-BR": fake.text(),
                    "en-BR": fake.text()
                },
                "durationDescription": {
                    "en-US": "De 1h a 2h",
                    "pt-BR": "De 1h a 2h",
                    "en-BR": "De 1h a 2h"
                },
                "activity": "Manicure",
                "value": random.randint(50, 100),
                "mobileImageAndroid": fake.image_url(),
                "mobileImageIOS": fake.image_url(),
                "preference": {
                    "type": "P",
                    "value": random.randint(0, 10)
                },
                "minDuration": random.randint(30, 60),
                "avgDuration": random.randint(60, 90),
                "catalogValue": random.randint(50, 100),
                "icons": [
                    {
                        "image": fake.image_url(),
                        "text": "Esmaltes variados"
                    },
                    {
                        "image": fake.image_url(),
                        "text": "Materiais esterilizados"
                    },
                    {
                        "image": fake.image_url(),
                        "text": "Itens de segurança"
                    },
                    {
                        "image": fake.image_url(),
                        "text": "Artistas qualificadas"
                    }
                ],
                "dynamicPrice": {
                    "_id": str(ObjectId()),
                    "polygonId": str(ObjectId()),
                    "name": "DynamicPrice",
                    "realtime": {},
                    "multiplierPerDayOfWeek": {
                        "monday": random.uniform(0, 1),
                        "tuesday": random.uniform(0, 1),
                        "wednesday": random.uniform(0, 1),
                        "thursday": random.uniform(0, 1),
                        "friday": random.uniform(0, 1),
                        "saturday": random.uniform(0, 1),
                        "sunday": random.uniform(0, 1)
                    },
                    "multiplierPerHourOfDay": {str(i): random.uniform(0, 1) for i in range(24)}
                }
            }
        ]
    }
    return convert_decimal(data)
    
# Recursive function to convert Decimal to float in nested structures
def convert_decimal(data):
    if isinstance(data, dict):
        return {k: convert_decimal(v) for k, v in data.items()}
    elif isinstance(data, list):
        return [convert_decimal(item) for item in data]
    elif isinstance(data, Decimal):
        return float(data)
    else:
        return data
# Insert random data into MongoDB
for _ in range(100):  # Adjust the range for the number of documents you want to insert
    collection.insert_one(generate_random_data())

print("Data inserted successfully.")
