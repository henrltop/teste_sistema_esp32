from django.shortcuts import render
from django.http import JsonResponse
from .models import ESPData, ESPCommand
from django.views.decorators.csrf import csrf_exempt
from django.utils import timezone
import datetime

def home(request):
    # Verifica se o ESP32 está conectado (dados recebidos nos últimos 10 segundos)
    now = timezone.now()
    ten_seconds_ago = now - datetime.timedelta(seconds=10)
    connected = ESPData.objects.filter(timestamp__gte=ten_seconds_ago).exists()

    # Obtém o último dado recebido
    data = ESPData.objects.last()

    context = {
        'connected': connected,
        'data': data.data if data else 'Nenhum dado recebido',
    }
    return render(request, 'home.html', context)

@csrf_exempt
def esp_data(request):
    if request.method == 'POST':
        received_data = request.POST.get('data')
        ESPData.objects.create(data=received_data)
        return JsonResponse({'status': 'success'})
    else:
        return JsonResponse({'status': 'invalid request'}, status=400)

@csrf_exempt
def send_command(request):
    if request.method == 'POST':
        command = request.POST.get('command')
        ESPCommand.objects.create(command=command)
        return JsonResponse({'status': 'command sent'})
    else:
        return JsonResponse({'status': 'invalid request'}, status=400)

@csrf_exempt
def get_command(request):
    # ESP32 irá solicitar este endpoint para obter o próximo comando
    last_command = ESPCommand.objects.last()
    if last_command:
        return JsonResponse({'command': last_command.command})
    else:
        return JsonResponse({'command': 'none'})
