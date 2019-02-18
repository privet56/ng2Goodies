import { SaferPipe } from './safer.pipe';

describe('SaferPipe', () => {
  it('create an instance', () => {
    const pipe = new SaferPipe();
    expect(pipe).toBeTruthy();
  });
});
