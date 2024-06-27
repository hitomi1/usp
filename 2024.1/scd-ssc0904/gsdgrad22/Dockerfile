# Dockerfile
FROM python:3.9-slim

# Set working directory
WORKDIR /app

# Copy the application code
COPY . .

# Install git and other necessary dependencies
RUN apt-get update && apt-get install -y git && apt-get clean

# Copy install dependencies
RUN pip install --upgrade pip && \
    pip install -r requirements.txt && \
    pip install pymongo kafka-python git+https://github.com/dpkp/kafka-python.git

# Command to run the main script
CMD ["python3", "./source/routes.py"]