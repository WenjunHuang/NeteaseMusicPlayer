from dataclasses import dataclass
from typing import Optional

from dataclasses_json import dataclass_json, LetterCase


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIError:
    code: int
    message: Optional[str] = None
