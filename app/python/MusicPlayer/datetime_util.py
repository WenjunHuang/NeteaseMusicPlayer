from datetime import datetime, timezone


def utc_now_with_timezone() -> datetime:
    return datetime.now().astimezone(timezone.utc)


def local_now_with_timezone() -> datetime:
    return datetime.now().astimezone()


def to_utc(dt: datetime) -> datetime:
    assert dt.tzinfo
    utc_time = dt - dt.tzinfo.utcoffset(None)
    return utc_time.replace(tzinfo=timezone.utc)


def utc_to_local(dt: datetime) -> datetime:
    assert (dt.tzinfo and dt.tzinfo == timezone.utc)
    return dt.astimezone()


def timestamp_seconds(dt: datetime) -> int:
    assert dt.tzinfo
    return int(dt.timestamp())


def from_timestamp_to_local(timestamp: int) -> datetime:
    return utc_to_local(datetime.fromtimestamp(timestamp, tz=timezone.utc))
