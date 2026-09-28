void serial_task(void *param)
{
    PicoOsUart u(0, 0, 1, 115200);
    uint8_t buffer[64];
    while (true) {
        if(int count = u.read(buffer, 64, 30); count > 0) {
            u.write(buffer, count);
        }
    }
}
