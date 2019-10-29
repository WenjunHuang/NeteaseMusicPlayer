from dataclasses import dataclass, field
from typing import List, Optional

from dataclasses_json import dataclass_json, config, LetterCase


@dataclass_json
@dataclass
class APIDJCategoryItemData:
    pic56x56_id: int = field(metadata=config(field_name="pic56x56Id"))
    pic96x96_id: int = field(metadata=config(field_name="pic96x96Id"))
    pic_pc_white: int = field(metadata=config(field_name="picPCWhite"))
    pic_pc_black: int = field(metadata=config(field_name="picPCBlack"))
    pic_web: int = field(metadata=config(field_name="picWeb"))
    pic_ipad: int = field(metadata=config(field_name="picIPad"))
    pic_pc_white_str: str = field(metadata=config(field_name="picPCWhiteStr"))
    pic_pc_white_url: str = field(metadata=config(field_name="picPCWhiteUrl"))
    name: str
    id: int


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJCategoryExcludeHotData:
    data: List[APIDJCategoryItemData]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIRadioData:
    id: int
    name: str
    rcmd_text: str
    radio_fee_type: int
    fee_scope: int
    pic_url: str
    program_count: int
    play_count: Optional[int]
    alg: str
    last_program_name: str


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJCategoryRecommendItemData:
    category_id: int
    category_name: str
    radios: List[APIRadioData]


@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJCategoryRecommendData:
    data: List[APIDJCategoryRecommendItemData]



@dataclass_json(letter_case=LetterCase.CAMEL)
@dataclass
class APIDJCategoryListData:
    categories:List[APIDJCategoryItemData]