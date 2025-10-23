"""Single Board Computer (SBC) module R03"""

# pylint: disable=import-error
# pyright: reportMissingModuleSource=false
# pyright: reportMissingImports=false

from collections import namedtuple
from machine import I2C, UART, ADC
from network import LAN  # type: ignore[reportAttributeAccessIssue]

from sdk.sysinfo import __platform__, __firmware__, get_board_revision
from sdk import (
    __version__,
    DigitalIO,
    Led,
    PWM,
    AnalogIn,
    # DifferentialAnalogIn,
    UsbHub,
    Ethernet,
    Storage,
    FlashDrive,
    CANBus,
    XBeeSocket,
)
from sdk.modules.bmi08x import BMI08x, Axes
from sdk.modules.gnss import GNSSFactory, GNSS_MODULES as _GNSS_MODULES

__revision__ = get_board_revision(adc=ADC("HW_REV"))

### BOARD HARDWARE ###

LedGreen = Led(pin="LEDGREEN")
LedRed = Led(pin="LEDRED")
LedBlue = Led(pin="LEDBLUE")

DOut1 = PWM(DigitalIO(pin="DOUT1"))
DOut2 = PWM(DigitalIO(pin="DOUT2"))
DOut3 = PWM(DigitalIO(pin="DOUT3"))
DOut4 = PWM(DigitalIO(pin="DOUT4"))
DOut5 = PWM(DigitalIO(pin="DOUT5"))
DOut6 = PWM(DigitalIO(pin="DOUT6"))

DIn1 = DigitalIO(pin="DIN1", mode=DigitalIO.IN)
DIn2 = DigitalIO(pin="DIN2", mode=DigitalIO.IN)

AIn1 = AnalogIn(pin="VAIN1", voltage_divider=(47e3 + 10e3) / 10e3)
AIn2 = AnalogIn(pin="VAIN2", voltage_divider=(47e3 + 10e3) / 10e3)
# AIn3 = DifferentialAnalogIn(
#     target=AnalogIn(pin="VAIN3", voltage_divider=3),
#     ref=AnalogIn(pin="VAIN_VREF", voltage_divider=3),
# )

RS232_1 = UART(3, baudrate=115200)

power_xbee = DigitalIO(pin="PWR_XBEE")
XBEE_A = XBeeSocket(4, baudrate=115200, power=power_xbee)
XBEE_B = XBeeSocket(6, baudrate=115200, power=power_xbee)

CAN = CANBus(port=1, baudrate=250_000)

### GPS ###

power_gnss = DigitalIO(pin="PWR_GNSS") # GNSS 2 and 3 share power pin
GNSSSlots = namedtuple("Slots", ["GPS_1", "GPS_2", "GPS_3"])
_SLOTS = GNSSSlots(
    GPS_1=XBeeSocket(port=8),  # GPS 1 is always ON
    GPS_2=XBeeSocket(port=1, power=power_gnss),
    GPS_3=XBeeSocket(port=2, power=power_gnss),
)
SLOTS = GNSSSlots(GPS_1="GPS_1", GPS_2="GPS_2", GPS_3="GPS_3")

GNSSModules = namedtuple("GNSSModule", ["ZED_F9P", "UM98x"])
GNSS = GNSSModules(ZED_F9P="ZED_F9P", UM98x="UM98x")

gnss_factory = GNSSFactory(slots=_SLOTS, modules=_GNSS_MODULES)

GNSS1 = gnss_factory.create(slot=SLOTS.GPS_1, module=GNSS.ZED_F9P)
GNSS1.interruption = DigitalIO(pin="F9P_EXTI")
GNSS1.timepulse = DigitalIO(pin="F9P_PULS", mode=DigitalIO.IN)
GNSS1.geofence = DigitalIO(pin="F9P_GEO", mode=DigitalIO.IN)

### PARTS ###

SDCard = Storage("/sd")
FlashMemory = FlashDrive("/flash")

i2c = I2C(3, freq=400_000)

USB = UsbHub(
    i2c=i2c,
    power=DigitalIO(pin="PWR_USB", value=True),
    reset=DigitalIO(pin="USB_RST", value=True),
)

IMU = BMI08x(i2c=i2c, mount=Axes(x='S', y='E', z='U'))

Ethernet = Ethernet(phy_type=LAN.PHY_DP83825)
