from django.db import models

class ESPData(models.Model):
    data = models.CharField(max_length=255)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.data} - {self.timestamp}"

class ESPCommand(models.Model):
    command = models.CharField(max_length=50)
    timestamp = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.command} - {self.timestamp}"
