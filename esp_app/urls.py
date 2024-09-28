from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='home'),
    path('esp_data/', views.esp_data, name='esp_data'),
    path('send_command/', views.send_command, name='send_command'),
    path('get_command/', views.get_command, name='get_command'),
]
