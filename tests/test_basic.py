# Start the tests via `make test-debug` or `make test-release`


async def test_start(service_client):
    response = await service_client.post(
        '/v1/start',
    )
    assert response.status == 200
    assert len(response.text) == 32


async def test_check(service_client):
    token_response = await service_client.post('v1/start')

    response = await service_client.post(
        '/v1/check',
        params={'token': token_response.text, 'word': 'horse'},
    )
    assert response.status == 200
