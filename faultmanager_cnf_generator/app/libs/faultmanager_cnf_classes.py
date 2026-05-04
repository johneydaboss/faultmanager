from typing import NamedTuple

"""
@brief

faultmanager_cnf_classes.py
"""

class FaultConfig(NamedTuple):
    id: str
    type : str
    severity: str
    confirmed_threshold: int
    heal_threshold: int
    on_confirmed: callable
    FaultAction: str